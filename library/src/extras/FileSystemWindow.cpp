//
// Created by Tyler Gilbert on 12/2/21.
//

#include <lvgl/Checkbox.hpp>
#include <lvgl/Draw.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/Image.hpp>
#include <lvgl/Line.hpp>
#include <lvgl/List.hpp>
#include <lvgl/Table.hpp>
#include <lvgl/TileView.hpp>

#include <fs/FileSystem.hpp>
#include <fs/Path.hpp>

#include "design/Grid.hpp"
#include "design/extras/FileSystemWindow.hpp"
#include "design/extras/FormList.hpp"

#ifdef __win32
#define ROOT_DRIVE "C:/"
#else
#define ROOT_DRIVE "/"
#endif

using namespace design;
using namespace lvgl;

const char *FileSystemWindow::root_drive_path() { return ROOT_DRIVE; }

FileSystemWindow::FileSystemWindow(Data &data) {
  construct_object(data.cast_as_name());
  add_style("card");

  if( data.base_path.is_empty() ){
    data.base_path = root_drive_path();
  }

  if (data.path.is_empty()) {
    data.path = data.base_path;
  }

  add(Column(Names::top_column)
        .fill()
        .add(Row(Names::header_row).fill_width().add_style("card_header"))
        .add(Row(Names::content_area).fill_width().set_flex_grow()));

  {
    auto header_row = find<Row>(Names::header_row);
    header_row
      .add(Label(Names::path_label)
             .add_style("form_label")
             .set_flex_grow()
             .set_text_static(data.path));

    if( data.is_select_file ){
      header_row.add(Button(Names::select_button)
                       .add_static_label(LV_SYMBOL_OK)
                       .add_event_callback(EventCode::clicked, select_button_pressed));
    }

    header_row.add(Button(Names::back_button)
             .add_static_label(data.path == data.base_path ? data.close_symbol : data.back_symbol)
             .add_event_callback(EventCode::clicked, back_button_pressed));



  }

  {
    auto content_row = find<Generic>(Names::content_area);
    content_row.add_style("form_filesystem");
    configure_list(content_row);
  }
}

void FileSystemWindow::select_button_pressed(lv_event_t *e) {
  auto window = get_window(Event(e).target());
  auto * fs_data = window.user_data<Data>();
  fs_data->notify_status = NotifyStatus::selected;
  Event::send(window, EventCode::notified);
}

void FileSystemWindow::back_button_pressed(lv_event_t *e) {
  const auto event = Event(e);

  auto window = get_window(event.target());
  auto * fs_data = window.user_data<Data>();
  auto &path = fs_data->path;

  if( path == fs_data->base_path ){
    fs_data->notify_status = NotifyStatus::closed;
    Event::send(get_window(Event(e).target()), EventCode::notified);
    return;
  }

  if (fs::FileSystem().exists(path)) {
    const auto parent = fs::Path::parent_directory(path);

    if (fs::FileSystem().exists(parent)) {
      const auto info = fs::FileSystem().get_info(parent);
      window.update_path(parent);
      if (info.is_directory()) {
        configure_list(window.get_content_area());
      } else {
        configure_details(window.get_content_area());
      }
    } else {
      window.update_path(root_drive_path());
      window.set_back_button_label(fs_data->close_symbol);
      configure_list(window.get_content_area());
    }
  }
}

FileSystemWindow &FileSystemWindow::set_back_button_label(const char *label) {
  find<Button>(Names::back_button).get_child(0).get<Image>().set_source(label);
  return *this;
}

FileSystemWindow &FileSystemWindow::update_path(var::StringView path) {
  auto &user_data_path = user_data<Data>()->path;
  user_data_path = path;
  find<Label>(Names::path_label).set_text_static(user_data_path);
  return *this;
}

Label FileSystemWindow::get_title_label(const Window &window) {
  return window.find<Label>(Names::window_title);
}

FileSystemWindow FileSystemWindow::get_window(lvgl::Object child) {
  return child.find_parent<Generic>(Names::top_column)
    .get_parent()
    .get<FileSystemWindow>();
}

void FileSystemWindow::configure_details(Generic container) {

  container.clear_flag(Flags::scrollable)
    .clean()
    .add(Table(Names::file_details_table).setup([](Table table) {
      auto *fs_data = get_window(table).user_data<Data>();
      const auto width = lvgl::screen().get_width();
      const auto info = fs::FileSystem().get_info(fs_data->path);
      const auto file_type = info.is_file() ? "File" : "Device";

      table.set_width(100_percent)
        .set_height(100_percent)
        .set_column_count(2)
        .set_row_count(4)
        .set_column_width(0, width / 2)
        .set_column_width(1, width / 2)
        .set_cell_value(Table::Cell().set_column(0).set_row(0), "Type")
        .set_cell_value(Table::Cell().set_column(0).set_row(1), "Size")
        .set_cell_value(Table::Cell().set_column(0).set_row(2), "Mode")
        .set_cell_value(Table::Cell().set_column(0).set_row(3), "Owner")
        .set_cell_value(Table::Cell().set_column(1).set_row(0), file_type)
        .set_cell_value(
          Table::Cell().set_column(1).set_row(1),
          var::NumberString(info.size()))
        .set_cell_value(
          Table::Cell().set_column(1).set_row(2),
          var::NumberString(info.permissions().permissions(), "0%o"))
        .set_cell_value(
          Table::Cell().set_column(1).set_row(3),
          info.owner() ? "user" : "root")
        .add_event_callback(EventCode::draw_part_begin, [](lv_event_t *e) {
          const Event event(e);
          Draw draw(event.parameter<lv_obj_draw_part_dsc_t *>());

          /*If the cells are drawn...*/
          if (draw.part() == Part::items) {
            uint32_t row = draw.id() / 2;

            /*Make every 2nd row grayish*/
            if ((row % 2) == 0) {
              auto rect = draw.get_rectangle();
              const auto background_color = rect.background_color();
              const auto mix_color = Color::get_palette(Palette::grey)
                                       .mix(background_color, MixRatio::x10);
              rect.set_background_color(mix_color).set_background_opacity(
                Opacity::cover);
            }
          }
        });
    }));
}

var::PathString FileSystemWindow::get_next_path(
  const var::PathString &path,
  const char *entry) {
  if (path == ROOT_DRIVE) {
    return var::PathString(path).append(entry);
  }
  return path / entry;
}

void FileSystemWindow::configure_list(Generic container) {
  // load the path

  container.add_flag(Flags::scrollable).clean().add(List().setup([](List list) {
    auto *file_system_data = get_window(list).user_data<Data>();
    API_ASSERT(file_system_data);

    // add items in the director to the list
    const auto &path = file_system_data->path;
    auto is_exclude = [](const var::StringView name, void *data) {
      auto *file_system_data = reinterpret_cast<Data *>(data);
      if (file_system_data->is_show_hidden == false) {
        if (name.length() && name.at(0) == '.') {
          return fs::FileSystem::IsExclude::yes;
        }
      }

      if (file_system_data->is_select_folder) {
        const auto info
          = fs::FileSystem().get_info(file_system_data->path / name);
        if (info.is_directory() == false) {
          return fs::FileSystem::IsExclude::yes;
        }
      }

      return fs::FileSystem::IsExclude::no;
    };

    const auto file_list = [&]() {
      api::ErrorScope error_scope;
      return fs::FileSystem()
        .read_directory(
          path,
          fs::FileSystem::IsRecursive::no,
          is_exclude,
          file_system_data)
        .sort(fs::PathList::ascending);
    }();

    if (file_list.count() < 0) {
      // show a message saying there are no files

      return;
    }

    if (file_list.count() > 0) {
      list.set_top_padding(0)
        .add_style("list_group_flush")
        .set_scroll_mode(ScrollBarMode::active)
        .set_border_width(0)
        .set_radius(0)
        .set_bottom_padding(0)
        .fill()
        .add_event_callback(EventCode::clicked, [](lv_event_t *e) {
          const Event event(e);
          auto list = event.current_target<List>();
          const auto *entry_name = list.get_button_text(event.target());
          auto button = event.target<Button>();

          auto window = get_window(event.target());
          auto *fs_data = window.user_data<Data>();

          const auto is_checked = button.has_state(State::checked);
          if (!is_checked) {
            for(auto child: list){
              child.get<Generic>().clear_state(State::checked);
            }
            fs_data->selected_file = entry_name;
            button.add_state(State::checked);
            return;
          }

          if (entry_name != Names::entry_list) {

            printf("get info on selected\n");
            const auto next_path = get_next_path(fs_data->path, entry_name);
            const auto info = fs::FileSystem().get_info(next_path);

            window.set_back_button_label(fs_data->back_symbol);

            // clicked a directory or a file?
            if (info.is_directory()) {
              // configure this list with the content area
              configure_list(window.update_path(next_path).get_content_area());
            } else {

              if (fs_data->is_select_file) {
                fs_data->notify_status = NotifyStatus::selected;
                Event::send(window, EventCode::notified);
              } else {
                window.update_path(next_path);
                configure_details(window.get_content_area());
              }
            }
          }
        });

      int count = 0;
      for (const auto &item : file_list) {
        const auto full_path = get_next_path(path, item);
        {
          api::ErrorScope es;
          const auto info = fs::FileSystem().get_info(full_path);
          const auto *symbol = info.is_directory()
                                 ? file_system_data->directory_symbol
                                 : file_system_data->file_symbol;

          list.add_button("", symbol, item.cstring(), [](Button button) {
            button.add_flag(Flags::checkable);
          });

          if (count % 2 == 0) {
            // auto entry = list.find<Generic>(item.cstring());
            // entry.add_style("darker");
          }

          ++count;
        }
      }
    }
  }));
}