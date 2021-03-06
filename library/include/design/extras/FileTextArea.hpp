//
// Created by Tyler Gilbert on 12/20/21.
//

#ifndef DESIGNAPI_DESIGN_EXTRAS_FILE_TEXT_AREA_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_FILE_TEXT_AREA_HPP_

#include <lvgl/TextArea.hpp>

#include "../macros.hpp"

namespace design {

class FileTextArea : public lvgl::ObjectAccess<FileTextArea> {
public:
  class Data : public lvgl::UserDataAccess<Data> {
  public:
    Data(const char *name, var::View buffer)
      : UserDataBase(name), m_buffer(buffer.data(), buffer.size()) {}

  private:
    API_AF(Data, fs::FileObject *, file, nullptr);
    API_AF(Data, u16, progress_start, 0);
    API_AF(Data, u16, progress_size, 0);

    friend FileTextArea;
    var::View m_buffer;

    size_t m_file_size{};
    int m_file_read_location{};

    API_NO_DISCARD size_t get_location_advance_size() const {
      return m_buffer.size() * 3 / 4;
    }
  };

  static constexpr auto progress_bar_name = "FileTextAreaProgressBar";

  explicit FileTextArea(Data &data);
  explicit FileTextArea(lv_obj_t *obj) { m_object = obj; }

  static const lv_obj_class_t *get_class() { return api()->textarea_class; }

  FileTextArea &set_password_mode(bool value = true) {
    api()->textarea_set_password_mode(object(), value);
    return *this;
  }

  FileTextArea &set_one_line_mode(bool value = true) {
    api()->textarea_set_one_line(object(), value);
    return *this;
  }

  FileTextArea &add_character(u32 c) {
    api()->textarea_add_char(object(), c);
    return *this;
  }

  FileTextArea &add_text(const char *text) {
    api()->textarea_add_text(object(), text);
    return *this;
  }

  FileTextArea &delete_character() {
    api()->textarea_del_char(object());
    return *this;
  }

  FileTextArea &delete_forward_character() {
    api()->textarea_del_char_forward(object());
    return *this;
  }

  FileTextArea &set_placeholder_text(const char *value) {
    api()->textarea_set_placeholder_text(object(), value);
    return *this;
  }

  FileTextArea &set_cursor_position(int value) {
    api()->textarea_set_cursor_pos(object(), value);
    return *this;
  }

  FileTextArea &set_cursor_click_position(bool value) {
    api()->textarea_set_cursor_click_pos(object(), value);
    return *this;
  }

  FileTextArea &set_accepted_characters(const char *value) {
    api()->textarea_set_accepted_chars(object(), value);
    return *this;
  }

  FileTextArea &set_max_length(size_t value) {
    api()->textarea_set_max_length(object(), value);
    return *this;
  }

  FileTextArea &set_insert_replace_text(const char *value) {
    api()->textarea_set_insert_replace(object(), value);
    return *this;
  }

  FileTextArea &set_text_selection(bool value) {
    api()->textarea_set_text_selection(object(), value);
    return *this;
  }

  FileTextArea &set_password_show_time(const chrono::MicroTime duration) {
    api()->textarea_set_password_show_time(object(), duration.milliseconds());
    return *this;
  }

  FileTextArea &set_text_alignment(lvgl::TextAlignment value) {
    api()->textarea_set_align(object(), lv_text_align_t(value));
    return *this;
  }

  FileTextArea &set_text(const char *value) {
    api()->textarea_set_text(object(), value);
    return *this;
  }

  FileTextArea &set_text_as_static(const char *value) {
    lvgl::Label(reinterpret_cast<lv_textarea_t *>(object())->label)
      .set_text_as_static(value);
    return *this;
  }

  API_NO_DISCARD const char *get_text() const {
    return api()->textarea_get_text(object());
  }

  API_NO_DISCARD const char *get_placeholder_text() const {
    return api()->textarea_get_placeholder_text(m_object);
  }

  API_NO_DISCARD lvgl::Label get_label() const {
    return lvgl::Label(api()->textarea_get_label(m_object));
  }

  API_NO_DISCARD int get_cursor_position() const {
    return api()->textarea_get_cursor_pos(m_object);
  }

  API_NO_DISCARD bool get_password_mode() const {
    return api()->textarea_get_password_mode(m_object);
  }

  API_NO_DISCARD bool get_one_line() const {
    return api()->textarea_get_one_line(m_object);
  }

  API_NO_DISCARD const char *get_accepted_characters() const {
    return api()->textarea_get_accepted_chars(m_object);
  }

  API_NO_DISCARD size_t get_max_length() const {
    return api()->textarea_get_max_length(m_object);
  }

  API_NO_DISCARD bool get_text_selection() const {
    return api()->textarea_get_text_selection(m_object);
  }

  API_NO_DISCARD chrono::MicroTime get_password_show_time() const {
    return api()->textarea_get_password_show_time(m_object) * 1_milliseconds;
  }

  FileTextArea &clear_selection() {
    api()->textarea_clear_selection(object());
    return *this;
  }

  FileTextArea &move_cursor_right() {
    api()->textarea_cursor_right(object());
    return *this;
  }

  FileTextArea &move_cursor_left() {
    api()->textarea_cursor_left(object());
    return *this;
  }

  FileTextArea &move_cursor_up() {
    api()->textarea_cursor_up(object());
    return *this;
  }

  FileTextArea &move_cursor_down() {
    api()->textarea_cursor_down(object());
    return *this;
  }

private:
  struct Names {
    DESIGN_DECLARE_NAME(progress_bar);
  };
};

}

#endif // DESIGNAPI_DESIGN_EXTRAS_FILE_TEXT_AREA_HPP_
