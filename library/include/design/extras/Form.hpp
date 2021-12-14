//
// Created by Tyler Gilbert on 12/13/21.
//

#ifndef DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_

#include <lvgl/Label.hpp>
#include <lvgl/TextArea.hpp>

#include "FileSystemWindow.hpp"

namespace design {

class Form : public lvgl::ObjectAccess<Form> {
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Form);

  class LineField : public lvgl::ObjectAccess<LineField> {
  public:
    LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(LineField);

    LineField &set_label_as_static(const char *value) {
      get_label().set_text_as_static(value);
      return *this;
    }

    LineField &set_value(const char *value) {
      get_text_area().set_text(value);
      return *this;
    }

    LineField &set_password_mode(bool value) {
      get_text_area().set_password_mode(value);
      return *this;
    }

    LineField &set_value_as_static(const char *value) {
      get_text_area().set_text_as_static(value);
      return *this;
    }

    lvgl::Label get_label() const { return find<lvgl::Label>(Names::label); }

    lvgl::TextArea get_text_area() const {
      return find<lvgl::TextArea>(Names::field);
    }

  private:
    struct Names {
      static constexpr auto label = "Label";
      static constexpr auto field = "Field";
    };
  };

  class SelectFile : public lvgl::ObjectAccess<SelectFile> {
  public:

    using Data = FileSystemWindow::Data;

    explicit SelectFile(Data &data);
    explicit SelectFile(lv_obj_t *object) { m_object = object; }

    const char * get_path() const {
      return find<lvgl::TextArea>(Names::selected_path_label).get_text();
    }

  private:
    struct Names {
      static constexpr auto select_file_Label = "Label";
      static constexpr auto select_file_button = "Button";
      static constexpr auto select_file_modal = "Modal";
      static constexpr auto selected_path_label = "FilePath";
    };
  };
};

} // namespace design

#endif // DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_
