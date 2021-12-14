//
// Created by Tyler Gilbert on 12/13/21.
//

#include <lvgl/Button.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/Group.hpp>

#include <fs/FileSystem.hpp>
#include <fs/Path.hpp>

#include "design/Grid.hpp"
#include "design/extras/Form.hpp"

#include "design/Modal.hpp"
#include "design/extras/FileSystemWindow.hpp"

using namespace design;
using namespace lvgl;

Form::Form(const char *name) {
  construct_object(name);
  add_style(Column::get_style())
    .fill_width()
    .set_height(size_from_content)
    .add_style("form");
}

Form::LineField::LineField(const char *name) {
  construct_object(name);
  add_style(Row::get_style())
    .fill_width()
    .add_style("form_row")
    .set_height(size_from_content)
    .add(Label(Names::label)
           .add_style("form_label")
           .set_width(20_percent)
           .set_text_alignment(TextAlignment::right))
    .add(TextArea(Names::field)
           .add_style("form_field")
           .set_flex_grow()
           .set_one_line_mode()
           .add_to_default_group())
    .add(Button()
           .add_static_label(LV_SYMBOL_CLOSE)
           .add_style("btn_md btn_outline_light")
           .add_event_callback(
             EventCode::clicked,
             [](lv_event_t *e) {
               Event(e)
                 .target()
                 .get_parent()
                 .find<TextArea>(Names::field)
                 .set_text_static("");
             }))
    .add(NakedContainer().set_width(2_percent).set_height(0));
}

Form::SelectFile::SelectFile(Data &data) {
  construct_object(data.cast_as_name());
  data.set_user_data(m_object);

  add_style(Row::get_style())
    .fill_width()
    .add_style("form_row")
    .set_height(size_from_content)
    .add(Label(Names::select_file_Label)
           .add_style("form_label")
           .set_width(20_percent)
           .set_text_alignment(TextAlignment::right)
           .set_text_static("Select File"))
    .add(TextArea(Names::selected_path_label)
           .add_style("form_field")
           .set_flex_grow()
           .set_text_static(""))
    .add(
      Button(Names::select_file_button)
        .add_style("btn_md")
        .add_static_label(LV_SYMBOL_DRIVE)
        .add_event_callback(
          EventCode::clicked,
          [](lv_event_t *e) {
            const auto event = Event(e);
            auto select_file = event.target().get_parent().get<SelectFile>();
            auto *file_system_data
              = select_file.user_data<FileSystemWindow::Data>();

            printf("text is %s\n", select_file.get_path());
            const auto parent
              = fs::Path::parent_directory(select_file.get_path());
            if (
              !parent.is_empty() && fs::FileSystem().directory_exists(parent)) {
              file_system_data->path = parent;
            }

            auto *new_data = file_system_data->needs_free()
                               ? &FileSystemWindow::Data::create()
                               : file_system_data;

            if (new_data != file_system_data) {
              // if new data was created -- copy it
              *new_data = *file_system_data;
            }

            Modal(Names::select_file_modal)
              .add(
                FileSystemWindow(*new_data)
                  .add_style("modal_content")
                  .add_style("modal_content_enabled", State::user1)
                  .set_width(80_percent)
                  .set_height(80_percent)
                  .set_alignment(Alignment::top_middle)
                  .add_state(State::user1)
                  .set_opacity(Opacity::transparent)
                  .add_event_callback(EventCode::notified, [](lv_event_t *e) {
                    auto self = Event(e).target();
                    auto *fs_data = self.user_data<Data>();
                    auto select_file = SelectFile(
                      reinterpret_cast<lv_obj_t *>(fs_data->user_data));

                    if (
                      fs_data->notify_status
                      == FileSystemWindow::NotifyStatus::selected) {
                      select_file.find<TextArea>(Names::selected_path_label)
                        .set_text(fs_data->path / fs_data->selected_file);
                    }

                    self.get_parent().async_remove();

                    Event::send(
                      SelectFile(
                        reinterpret_cast<lv_obj_t *>(fs_data->user_data)),
                      EventCode::notified);
                  }));
          }))
    .add(NakedContainer().set_width(2_percent).set_height(0));
}
