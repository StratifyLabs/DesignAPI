//
// Created by Tyler Gilbert on 12/13/21.
//

#include <lvgl/Button.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/Group.hpp>

#include <fs/File.hpp>
#include <fs/FileSystem.hpp>
#include <fs/Path.hpp>

#include <printer/Printer.hpp>

#include <json/JsonDocument.hpp>

#include "design/Grid.hpp"
#include "design/extras/Form.hpp"

#include "design/Badge.hpp"
#include "design/Modal.hpp"
#include "design/extras/FileSystemCard.hpp"

using namespace design;
using namespace lvgl;
using namespace var;

LVGL_OBJECT_ASSERT_SIZE(Form);

Form Form::find_form_parent(lvgl::Object child_object) {
  auto current = child_object.get_parent();
  while (true) {
    if (current.object() == nullptr) {
      API_ASSERT(false);
    } else {
      if (
        current.get_child_count() && current.get_child(0).name() == Names::hidden_label) {
        return current.get<Form>();
      }
    }
    current = current.get_parent();
  }
}

Form Form::find_form_child(lvgl::Object parent_object) {
  return parent_object.find(Names::hidden_label).get_parent<Form>();
}

Form::LaunchKeyboardCallback Form::m_launch_keyboard_callback = nullptr;

Form::IsSoftKeyboard Form::launch_keyboard(
  const char *name,
  lvgl::TextArea text_area,
  lvgl::Keyboard::Mode mode) {
  if (m_launch_keyboard_callback) {
    m_launch_keyboard_callback(name, text_area, mode);
    return IsSoftKeyboard::yes;
  }
  return IsSoftKeyboard::no;
}

Form::Form(const char *name) {
  construct_object(name);
  add_style(Column::get_style())
    .set_flex_align(SetFlexAlign()
                      .set_align_main(FlexAlign::start)
                      .set_cross(FlexAlign::start)
                      .set_track_cross(FlexAlign::start))
    .fill_width()
    .add_flag(Flags::event_bubble)
    .set_height(size_from_content)
    .add_style("form")
    .add(Label(Names::hidden_label).add_flag(Flags::hidden));
}

json::JsonObject Form::get_json_object() const {
  API_RETURN_VALUE_IF_ERROR(json::JsonObject());
  json::JsonObject result;
  for (const auto &child : *this) {
    const var::StringView key_name = child.name();
    const var::StringView value = get_value(child);

    if (value != Form::not_a_value) {
      result.insert(key_name, json::JsonString(value));
    }
  }
  return result;
}

Form &Form::set_values(const json::JsonObject object) {
  for (const auto &child : *this) {
    const auto value = object.at(child.name());
    if (value.is_string()) {
      set_value(child, value.to_cstring());
    }
  }
  return *this;
}

Form &Form::set_value(lvgl::Object child, const char *value) {
  {
    auto input = check_type<LineField>(child);
    if (input.is_valid()) {
      input.set_value(value);
      return *this;
    }
  }

  {
    auto input = check_type<SelectFile>(child);
    if (input.is_valid()) {
      input.set_value(value);
      return *this;
    }
  }

  {
    auto input = check_type<Select>(child);
    if (input.is_valid()) {
      input.set_value(value);
      return *this;
    }
  }

  {
    auto input = check_type<Form::Switch>(child);
    if (input.is_valid()) {
      input.set_value(var::StringView(value) == "true");
      return *this;
    }
  }

  return *this;
}

var::StringView Form::get_value(lvgl::Object child) const {

  {
    auto input = check_type<LineField>(child);
    if (input.is_valid()) {
      return input.get_value();
    }
  }

  {
    auto input = check_type<SelectFile>(child);
    if (input.is_valid()) {
      return input.get_value();
    }
  }

  {
    auto input = check_type<Select>(child);
    if (input.is_valid()) {
      return input.get_value();
    }
  }

  {
    auto input = check_type<Form::Switch>(child);
    if (input.is_valid()) {
      return input.get_value();
    }
  }

  // section headings, decoration, etc
  return not_a_value;
}

Form::Schema::Schema(var::StringView file_path, IsOverwrite is_overwrite)
  : m_path(file_path), m_is_overwrite(is_overwrite) {
  API_RETURN_IF_ERROR();
  if (!fs::FileSystem().exists(file_path)) {
    return;
  }
  to_object() = json::JsonDocument().load(fs::File(file_path)).to_object();
}

Form::Schema::~Schema() {
  if (bool(m_is_overwrite) && !m_path.is_empty()) {
    json::JsonDocument().save(
      is_valid() ? to_object() : json::JsonObject(), fs::File(m_is_overwrite, m_path));
  }
}

Form::Form(const char *name, const Schema schema) {
  construct_object(name);
  add_style(Column::get_style())
    .set_flex_align(SetFlexAlign()
                      .set_align_main(FlexAlign::start)
                      .set_cross(FlexAlign::start)
                      .set_track_cross(FlexAlign::start))
    .fill_width()
    .set_height(size_from_content)
    .add_style("form");

  const auto input_list = schema.input_to_array();
  for (const auto &input : input_list) {
    const auto type = input.to_object().at("type").to_string_view();
    if (type == LineField::Schema::schema_type) {
      LineField::Schema input_schema(input);
      add(LineField(input_schema.get_name_cstring())
            .set_label_as_static(input_schema.get_label_cstring())
            .set_hint_as_static(input_schema.get_hint_cstring())
            .set_value_as_static(input_schema.get_value_cstring()));
      continue;
    }

    if (type == LineField::Schema::schema_type) {
      SubmitButton::Schema input_schema(input);
      add(SubmitButton().set_label_as_static(input_schema.get_label_cstring()));
      continue;
    }

    if (type == LineField::Schema::schema_type) {
      CancelButton::Schema input_schema(input);
      add(CancelButton().set_label_as_static(input_schema.get_label_cstring()));
      continue;
    }

    if (type == Select::Schema::schema_type) {
      Select::Schema input_schema(input);
      const auto name = input_schema.get_name_cstring();
      add(Select(name)
            .set_label_as_static(input_schema.get_label_cstring())
            .set_hint_as_static(input_schema.get_hint_cstring()));

      auto select = find<Select>(name);
      select.get_dropdown().set_options_as_static(input_schema.get_options_cstring());

      const auto option_list = input_schema.get_options().split("\n");
      const auto current_value = input_schema.get_value();
      size_t selected = 0;
      for (const auto &option : option_list) {
        if (option == current_value) {
          select.get_dropdown().set_selected(selected);
          break;
        }
        ++selected;
      }

      continue;
    }

    if (type == SelectFile::Schema::schema_type) {
      SelectFile::Schema input_schema(input);
      const auto name = input_schema.get_name_cstring();
      add(SelectFile(SelectFile::Data::create(name)
                       .set_select_file(true)
                       .set_suffix_filter(input_schema.get_suffix_cstring())
                       .set_base_path(input_schema.get_base_path_cstring()))
            .set_hint_as_static(input_schema.get_hint_cstring())
            .set_value_as_static(input_schema.get_value_cstring())
            .set_label_as_static(input_schema.get_label_cstring()));
      continue;
    }

    if (type == Form::Switch::Schema::schema_type) {
      Form::Switch::Schema input_schema(input);
      add(Form::Switch(input_schema.get_name_cstring())
            .set_label_as_static(input_schema.get_label_cstring())
            .set_hint_as_static(input_schema.get_hint_cstring())
            .set_value(input_schema.get_value() == "true"));
      continue;
    }

    if (type == SectionHeadingSchema::schema_type) {
      SectionHeadingSchema input_schema(input);
      const auto name = input_schema.get_name_cstring();
      add(SectionHeading(name, input_schema.get_label_cstring()));
      continue;
    }
  }
}

void Form::set_hint(lvgl::Label label, const char *value) {
  label.set_text(value);
  if (value == nullptr || value[0] == 0) {
    label.add_flag(Flags::hidden);
  } else {
    label.clear_flag(Flags::hidden);
  }
}

void Form::set_hint_as_static(lvgl::Label label, const char *value) {
  label.set_text_as_static(value);
  if (value == nullptr || value[0] == 0) {
    label.add_flag(Flags::hidden);
  } else {
    label.clear_flag(Flags::hidden);
  }
}

Form::Switch::Switch(const char *name) {
  construct_object(name);

  add_style(Column::get_style())
    .add_style("form_col")
    .fill_width()
    .set_height(size_from_content)
    .add(Row()
           .add_style("form_row")
           .fill_width()
           .add(Label(Names::label)
                  .add_style("form_label")
                  .set_text_alignment(TextAlignment::left))
           .add(lvgl::Switch(Names::switch_).add_style("form_switch")))
    .add(Label(Names::hint_label)
           .add_style("form_hint")
           .fill_width()
           .add_flag(Flags::hidden)
           .set_text_alignment(TextAlignment::left)
           .set_text_as_static(""));
}

Form::SubmitButton::SubmitButton() {
  construct_button(Form::Names::submit_button);
  add_style("form_submit_btn");
  add(Label(Names::label).set_text_as_static("Submit").center());
  add_flag(Flags::event_bubble);
}

Form::CancelButton::CancelButton() {
  construct_button(Form::Names::submit_button);
  add_style("form_cancel_btn");
  add(Label(Names::label).set_text_as_static("Cancel").center());
  add_flag(Flags::event_bubble);
}

Form::LineField::LineField(const char *name) {
  construct_object(name);
  add_style(Column::get_style())
    .add_style("form_col")
    .fill_width()
    .set_height(size_from_content)
    .add(Row()
           .fill_width()
           .justify_space_between()
           .add(Label(Names::label)
                  .add_style("form_label")
                  .fill_width()
                  .set_text_alignment(TextAlignment::left)
                  .set_text_as_static(""))
           .add(Badge(Form::Names::error_badge)
                  .add_label("")
                  .add_style("form_error_badge")
                  .add_flag(Flags::hidden)))
    .add(Row()
           .add_style("form_row")
           .fill_width()
           .add(TextArea(Names::field)
                  .add_style("form_field")
                  .set_flex_grow()
                  .set_one_line_mode()
                  .add_event_callback(EventCode::focused, handle_text_focused)
                  .add_to_default_group())
           .add(Button()
                  .add_label_as_static(LV_SYMBOL_CLOSE)
                  .add_style("btn_md btn_outline_light")
                  .add_event_callback(
                    EventCode::clicked,
                    [](lv_event_t *e) {
                      Event(e)
                        .target()
                        .get_parent()
                        .find<TextArea>(Names::field)
                        .set_text_as_static("");
                    })))
    .add(Label(Names::keyboard_mode_label)
           .clear_flag(Flags::hidden)
           .set_padding(0)
           .set_height(0)
           .set_text_as_static(Keyboard::to_cstring(Keyboard::Mode::text_lower)))
    .add(Label(Names::hint_label)
           .add_style("form_hint")
           .fill_width()
           .add_flag(Flags::hidden)
           .set_text_alignment(TextAlignment::left)
           .set_text_as_static(""));
}

void Form::LineField::handle_text_focused(lv_event_t *e) {
  auto target_text_area = Event(e).target<TextArea>();
  // pass the name of the line field
  auto line_field = target_text_area.get_parent().get_parent<LineField>();
  launch_keyboard(line_field.name(), target_text_area, line_field.get_keyboard_mode());
}

Form::SelectFile::SelectFile(Data &data) {
  construct_object(data.cast_as_name());

  // FS user data points to the SelectFile Object
  // the associated object value will point to the FileSystemCard in the modal
  // it can't be set to this object
  data.set_user_data(m_object);

  fill_width();
  add_style(Column::get_style())
    .add_style("form_col")
    .set_height(size_from_content)
    .add(Row()
           .fill_width()
           .justify_space_between()
           .add(Label(Names::select_file_label)
                  .add_style("form_label")
                  .fill_width()
                  .set_text_alignment(TextAlignment::left)
                  .set_text_as_static(""))
           .add(Badge(Form::Names::error_badge)
                  .add_label("")
                  .add_style("form_error_badge")
                  .add_flag(Flags::hidden)))
    .add(Row(Names::form_row)
           .add_style("form_row")
           .add(TextArea(Names::selected_path_text_area)
                  .add_style("form_field")
                  .set_flex_grow()
                  .set_text_as_static("")
                  .add_event_callback(EventCode::focused, handle_text_focused))
           .add(Button(Names::select_file_button)
                  .add_style("btn_md btn_outline_primary")
                  .add_label_as_static(LV_SYMBOL_DIRECTORY)
                  .add_event_callback(EventCode::clicked, handle_clicked)))
    .add(Label(Names::hint_label)
           .add_style("form_hint")
           .fill_width()
           .add_flag(Flags::hidden)
           .set_text_alignment(TextAlignment::left)
           .set_text_as_static(""));
}

void Form::SelectFile::handle_text_focused(lv_event_t *e) {
  // change the button to an OK check box
  auto event_target_parent = Event(e).target().get_parent();
  auto label =
    event_target_parent.find<Button>(Names::select_file_button).get_child(0).get<Label>();

  auto text_area = event_target_parent.find<TextArea>(Names::selected_path_text_area);

  // is there a function available to launch a keyboard
  if (const auto parent_name = event_target_parent.get_parent().name();
      launch_keyboard(parent_name, text_area, Keyboard::Mode::text_lower)
      == IsSoftKeyboard::no) {

    // if no keyboard, then change the symbol to allow direct editing of the text area
    label.set_text_as_static(LV_SYMBOL_OK);
  }
}

void Form::SelectFile::handle_clicked(lv_event_t *e) {
  const auto event = Event(e);

  auto select_file = event.target().get_parent().get_parent().get<SelectFile>();
  auto *file_system_data = select_file.user_data<FileSystemCard::Data>();

  auto label = event.target().get_child(0).get<Label>();

  if (var::StringView(label.get_text()) == LV_SYMBOL_OK) {
    label.set_text_as_static(LV_SYMBOL_DIRECTORY);
    select_file.validate_value(file_system_data);
    Event::send(select_file, EventCode::notified);
    return;
  }

  //if incoming FileSystemCard data is dynamically allocated
  //it can't be passed to another object recursively
  auto *new_data =
    file_system_data->needs_free() ? &FileSystemCard::Data::create() : file_system_data;

  if (new_data != file_system_data) {
    // if new data was created -- copy it
    new_data->copy(*file_system_data);
  }

  // create the modal
  Modal(Names::select_file_modal)
    .add_content(FileSystemCard(*new_data)
                   .add_style("form_select_file_modal")
                   .add_event_callback(EventCode::notified, handle_notified));
}

void Form::SelectFile::handle_notified(lv_event_t *e) {
  auto self = Event(e).target();
  auto *fs_data = self.user_data<Data>();
  auto select_file = SelectFile(static_cast<lv_obj_t *>(fs_data->user_data));

  if (fs_data->notify_status == FileSystemCard::NotifyStatus::selected) {
    select_file.find<TextArea>(Names::selected_path_text_area)
      .set_text(fs_data->is_absolute_path ? fs_data->full_path : fs_data->relative_path);
  }

  auto modal = Event(e).find_parent<Modal>(Names::select_file_modal);
  modal.close(300_milliseconds);

  select_file.validate_value(fs_data);
  Event::send(select_file, EventCode::notified);
}

Form::IsValid Form::SelectFile::validate_value(Data *data) {
  const auto full_path =
    data->is_absolute_path ? var::PathString(get_value()) : data->base_path / get_value();
  if (!fs::FileSystem().exists(full_path)) {
    // set the error
    set_error_message("path does not exist");
    return IsValid::no;
  }

  // check if the item must be a file or directory
  const auto info = fs::FileSystem().get_info(full_path);
  if (data->is_select_file && !info.is_file()) {
    set_error_message("Selection is not a file");
    return IsValid::no;
  }

  if (data->is_select_folder && !info.is_directory()) {
    set_error_message("Selection is not a folder");
    return IsValid::no;
  }

  const var::StringView suffix_filter = data->suffix_filter;
  if (!suffix_filter.is_empty()) {
    // make sure the suffix is in the list
    const auto suffix_list = suffix_filter.split(",");
    bool is_suffix_ok = false;
    const auto value_suffix = fs::Path::suffix(full_path);
    for (const auto &suffix : suffix_list) {
      if (value_suffix == suffix) {
        is_suffix_ok = true;
        break;
      }
    }

    if (is_suffix_ok == false) {
      set_error_message("File type is not allowed");
      return IsValid::no;
    }
  }

  data->relative_path = get_value();
  hide_error_message();
  return IsValid::yes;
}

Form::SelectFile &Form::SelectFile::set_value(const char *value) {
  auto *data = user_data<Data>();
  const auto value_string = StringView(value);
  auto text_area = find<lvgl::TextArea>(Names::selected_path_text_area);
  if (!data->is_absolute_path && data->base_path.string_view()) {
    if (value_string.starts_with(data->base_path)) {
      // strip the base path
      data->relative_path =
        value_string.get_substring_at_position(data->base_path.length());
    } else {
      data->relative_path = value;
    }
  } else {
    data->relative_path = value;
  }

  text_area.set_text(data->relative_path);
  return *this;
}

void Form::set_error_message(Object form_object, const char *message) {
  form_object.find<Badge>(Names::error_badge).clear_flag(Flags::hidden).set_text(message);
}

void Form::set_error_message_as_static(Object form_object, const char *message) {
  form_object.find<Badge>(Names::error_badge)
    .clear_flag(Flags::hidden)
    .set_text_as_static(message);
}

void Form::hide_error_message(Object form_object) {
  form_object.find<Badge>(Names::error_badge).add_flag(Flags::hidden);
}

Form::Select::Select(const char *name) {
  construct_object(name);
  add_style(Column::get_style())
    .add_style("form_col")
    .fill_width()
    .set_height(size_from_content)
    .add(Row()
           .fill_width()
           .justify_space_between()
           .add(Label(Names::label)
                  .add_style("form_label")
                  .fill_width()
                  .set_flex_grow()
                  .set_text_alignment(TextAlignment::left)
                  .set_text_as_static(""))
           .add(Badge(Form::Names::error_badge)
                  .add_label("")
                  .add_style("form_error_badge")
                  .add_flag(Flags::hidden)))
    .add(Row()
           .add_style("form_row")
           .fill_width()
           .add(lvgl::Dropdown(Names::dropdown)
                  .add_style("form_dropdown")
                  .set_flex_grow()
                  .add_to_default_group()))
    .add(Label(Names::hint_label)
           .add_style("form_hint")
           .fill_width()
           .add_flag(Flags::hidden)
           .set_text_alignment(TextAlignment::left)
           .set_text_as_static(""));
}

var::StringView Form::Select::get_value() const {
  const auto dropdown = get_dropdown();
  const auto option_list = var::StringView(dropdown.get_options()).split("\n");
  const auto selected = dropdown.get_selected();
  if (selected < option_list.count()) {
    return option_list.at(selected);
  }

  return var::StringView();
}

Form::Select &Form::Select::set_value(const char *value) {
  auto dropdown = get_dropdown();
  const auto option_list = var::StringView(dropdown.get_options()).split("\n");

  u32 selected = 0;
  for (const auto &option : option_list) {
    if (option == value) {
      dropdown.set_selected(selected);
      return *this;
    }
    ++selected;
  }

  return *this;
}
