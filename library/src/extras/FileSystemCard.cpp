//
// Created by Tyler Gilbert on 12/2/21.
//

#include <lvgl/Draw.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/Image.hpp>
#include <lvgl/List.hpp>
#include <lvgl/Table.hpp>
#include <lvgl/TileView.hpp>

#include <fs/FileSystem.hpp>
#include <fs/Path.hpp>

#include "design/Grid.hpp"
#include "design/extras/FileSystemCard.hpp"

#if defined __link
#include "design/Modal.hpp"
#endif

#ifdef __win32
#define ROOT_DRIVE "C:/"
#else
#define ROOT_DRIVE "/"
#endif

using namespace design;
using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(FileSystemCard);

const char *FileSystemCard::root_drive_path() { return ROOT_DRIVE; }

var::PathString
FileSystemCard::Data::get_path_with_entry(var::StringView entry) const {
  if (full_path == root_drive_path()) {
    return full_path & entry;
  }
  return full_path / entry;
}

void FileSystemCard::Data::enter_directory(var::StringView name) {

  if (relative_path.is_empty()) {
    relative_path = name;
  } else if (!name.is_empty()) {
    relative_path = relative_path / name;
  }

  update_full_path();
}

void FileSystemCard::Data::update_full_path() {
  selected_file = "";
  if (!relative_path.is_empty()) {
    if (base_path == root_drive_path()) {
      full_path = base_path & relative_path;
    } else {
      full_path = base_path / relative_path;
    }
  } else {
    full_path = base_path;
  }
}

void FileSystemCard::Data::exit_directory() {
  if (relative_path.is_empty()) {
    return;
  }

  relative_path = fs::Path::parent_directory(relative_path);
  update_full_path();
}

bool FileSystemCard::Data::is_base_path() const {
  return relative_path.is_empty();
}

FileSystemCard &FileSystemCard::update_back_button() {
  auto back_button = find<Button>(Names::back_button);
  auto *data = user_data<Data>();
  back_button.set_state(State::disabled, data->is_base_path());
  return *this;
}

FileSystemCard::FileSystemCard(Data &data) {
  construct_object(data.cast_as_name());
  add_style("card");

  if (data.base_path.is_empty()) {
    data.base_path = root_drive_path();
  }

  data.update_full_path();

  add(Column(Names::top_column)
        .fill()
        .add(Row(Names::header_row).fill_width().add_style("card_header"))
#if defined __link
        .add(Button(Names::drop_zone)
               .set_width(98_percent)
               .set_height(20_percent)
               .add_style("btn_success")
               .add_label_as_static(data.drop_symbol)
               .add_flag(Flags::hidden)
               .add_event_callback(EventCode::drop_file, drop_file)
               .add_event_callback(EventCode::drop_text, drop_text))
#endif
        .add(Row(Names::content_area).fill_width().set_flex_grow()));

  {
    auto header_row = find<Row>(Names::header_row);
    header_row.add(Label(Names::path_label)
                     .add_style("form_label")
                     .set_flex_grow()
                     .set_text_as_static(data.full_path));

    header_row.add(
      Button(Names::back_button)
        .add_style("btn_outline_primary")
        .add_state(State::disabled)
        .add_label_as_static(data.back_symbol)
        .add_event_callback(EventCode::clicked, back_button_pressed));

#if defined __link
    if (data.drop_symbol != nullptr) {
      header_row.add(
        Button(Names::drop_button)
          .add_style("btn_outline_primary")
          .add_label_as_static(data.drop_symbol)
          .add_event_callback(EventCode::clicked, drop_button_pressed));
    }
#endif

    if (data.relative_path.is_empty() == false) {
      header_row.find<Button>(Names::back_button).clear_state(State::disabled);
    }

    header_row.add(
      Button(Names::select_button)
        .add_label_as_static(LV_SYMBOL_OK)
        .add_event_callback(EventCode::clicked, select_button_pressed));

    header_row.add(
      Button(Names::cancel_button)
        .add_style("btn_danger")
        .add_label_as_static(data.close_symbol)
        .add_event_callback(EventCode::clicked, cancel_button_pressed));
  }

  auto content_row = find<Generic>(Names::content_area);
  content_row.add_style("form_filesystem");

  load_content();
}

FileSystemCard &FileSystemCard::load_content() {
  auto *data = user_data<Data>();
  auto content_row = find<Generic>(Names::content_area);

  if (fs::FileSystem().directory_exists(data->full_path)) {
    configure_list(content_row);
  } else if (fs::FileSystem().exists(data->full_path)) {
    configure_details(content_row);
  } else {
    data->relative_path = "";
    data->update_full_path();
    configure_list(content_row);
  }
  return *this;
}

void FileSystemCard::select_button_pressed(lv_event_t *e) {
  auto window = get_fs_card(Event(e).target());
  auto *fs_data = window.user_data<Data>();
  fs_data->enter_directory(fs_data->selected_file);
  fs_data->notify_status = NotifyStatus::selected;
  Event::send(window, EventCode::notified);
}

void FileSystemCard::cancel_button_pressed(lv_event_t *e) {
  auto window = get_fs_card(Event(e).target());
  auto *fs_data = window.user_data<Data>();
  fs_data->notify_status = NotifyStatus::cancelled;
  Event::send(window, EventCode::notified);
}

void FileSystemCard::back_button_pressed(lv_event_t *e) {
  const auto event = Event(e);

  auto window = get_fs_card(event.target());
  auto *fs_data = window.user_data<Data>();
  auto &path = fs_data->full_path;

  fs_data->exit_directory();
  window.update_back_button();
  window.update_path(fs_data->full_path);
  const auto info = fs::FileSystem().get_info(fs_data->full_path);
  if (info.is_directory()) {
    configure_list(window.get_content());
  } else {
    configure_details(window.get_content());
  }
}

FileSystemCard &FileSystemCard::update_path(var::StringView path) {
  auto *fs_data = user_data<Data>();
  auto &user_data_path = fs_data->full_path;
  user_data_path = path;

  find<Label>(Names::path_label).set_text_as_static(user_data_path);
  return *this;
}

FileSystemCard FileSystemCard::get_fs_card(lvgl::Object child) {
  return child.find_parent<Generic>(Names::top_column)
    .get_parent()
    .get<FileSystemCard>();
}

void FileSystemCard::configure_details(Generic container) {

  container.clear_flag(Flags::scrollable)
    .clean()
    .add(Table(Names::file_details_table).setup([](Table table) {
      auto *fs_data = get_fs_card(table).user_data<Data>();
      const auto half_width = lv_coord_t(lvgl::screen().get_width() / 2);
      const auto info = fs::FileSystem().get_info(fs_data->full_path);
      const auto file_type = info.is_file() ? "File" : "Device";

      table.fill()
        .set_radius(0)
        .set_border_width(0)
        .set_column_count(2)
        .set_row_count(4)
        .add_style("list_flush")
        .set_column_width(0, half_width)
        .set_column_width(1, half_width)
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
              rect.set_background_color(mix_color)
                //.set_background_opacity(Opacity::cover)
                ;
            }
          }
        });
    }));
}

void FileSystemCard::configure_list(Generic container) {
  // load the path

  container.add_flag(Flags::scrollable).clean().add(List().setup([](List list) {
    auto *file_system_data = get_fs_card(list).user_data<Data>();
    API_ASSERT(file_system_data);

    // add items in the director to the list
    const auto &path = file_system_data->full_path;
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
        .add_event_callback(EventCode::clicked, item_clicked);

      int count = 0;
      for (const auto &item : file_list) {
        const auto full_path = file_system_data->get_path_with_entry(item);
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

fs::FileSystem::IsExclude
FileSystemCard::is_exclude(const var::StringView name, void *data) {
  auto *file_system_data = reinterpret_cast<Data *>(data);
  if (!file_system_data->is_show_hidden) {
    if (name.length() && name.at(0) == '.') {
      return fs::FileSystem::IsExclude::yes;
    }
  }

  const var::StringView suffix_filter = file_system_data->suffix_filter;
  if (file_system_data->is_select_folder || !suffix_filter.is_empty()) {
    const auto info
      = fs::FileSystem().get_info(file_system_data->get_path_with_entry(name));

    if (!info.is_directory()) {

      if (file_system_data->is_select_folder) {
        return fs::FileSystem::IsExclude::yes;
      }

      if (!suffix_filter.is_empty()) {
        const auto suffix_list
          = var::StringView(file_system_data->suffix_filter).split(",");
        const auto name_suffix = fs::Path::suffix(name);
        for (const auto &suffix : suffix_list) {
          if (name_suffix == suffix) {
            return fs::FileSystem::IsExclude::no;
          }
        }
        return fs::FileSystem::IsExclude::yes;
      }
    }
  }

  return fs::FileSystem::IsExclude::no;
}

void FileSystemCard::item_clicked(lv_event_t *e) {
  const Event event(e);
  auto list = event.current_target<List>();
  const auto *entry_name = list.get_button_text(event.target());
  auto button = event.target<Button>();

  auto window = get_fs_card(event.target());
  auto *fs_data = window.user_data<Data>();

  const auto is_checked = button.has_state(State::checked);
  if (!is_checked) {
    for (auto child : list) {
      child.get<Generic>().clear_state(State::checked);
    }
    fs_data->selected_file = entry_name;
    button.add_state(State::checked);
    return;
  }

  if (entry_name != Names::entry_list) {

    fs_data->enter_directory(entry_name);
    const auto info = fs::FileSystem().get_info(fs_data->full_path);

    // clicked a directory or a file?
    window.update_back_button();

    if (info.is_directory()) {
      // configure this list with the content area
      configure_list(window.update_path(fs_data->full_path).get_content());
    } else {
      if (fs_data->is_select_file) {
        fs_data->notify_status = NotifyStatus::selected;
        Event::send(window, EventCode::notified);
      } else {
        fs_data->exit_directory();
        window.update_path(fs_data->full_path);
        configure_details(window.get_content());
      }
    }
  }
}

#if defined __link

void FileSystemCard::drop_file(lv_event_t *e) {
  auto *path = Event(e).parameter<var::PathString *>();
  auto fs_card = get_fs_card(Event(e).target());
  auto *fs_data = fs_card.user_data<Data>();
  if (path->string_view().find(fs_data->base_path) == 0) {
    auto relative_path
      = path->string_view().pop_front(fs_data->base_path.length());
    if (relative_path.length() && relative_path.front() == '/') {
      relative_path.pop_front();
    }
    fs_data->relative_path = relative_path;
    fs_data->update_full_path();
    fs_card.update_path(path->string_view())
      .load_content()
      .update_back_button();

    fs_card.find<Button>(Names::drop_zone).add_flag(Flags::hidden);

  } else {
    // this is an error
    fs_card.find<Button>(Names::drop_button)
      .get_child(0)
      .get<Label>()
      .set_text_as_static(LV_SYMBOL_CLOSE " Invalid path");
  }

  delete path;
}

void FileSystemCard::drop_text(lv_event_t *) {}
void FileSystemCard::drop_button_pressed(lv_event_t *e) {
  auto fs_card = get_fs_card(Event(e).target());
  auto drop_zone = fs_card.find<Button>(Names::drop_zone);
  drop_zone.toggle_flag(Flags::hidden);
}

#endif
