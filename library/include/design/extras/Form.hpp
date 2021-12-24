//
// Created by Tyler Gilbert on 12/13/21.
//

#ifndef DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_

#include <lvgl/Dropdown.hpp>
#include <lvgl/Label.hpp>
#include <lvgl/TextArea.hpp>
#include <lvgl/Switch.hpp>

#include <json/Json.hpp>

#include "../macros.h"

#include "../Typography.hpp"
#include "FileSystemWindow.hpp"

namespace design {

class Form : public lvgl::ObjectAccess<Form> {
protected:
  static void set_hint(lvgl::Label label, const char *value);
  static void set_hint_as_static(lvgl::Label label, const char *value);

public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Form);

  using SectionHeading = Heading2;

  class SectionHeadingSchema : public json::JsonValue {
  public:
    static constexpr auto schema_type = "sectionHeading";
    SectionHeadingSchema() : json::JsonValue(json::JsonObject()) {
      set_type(schema_type);
    }
    SectionHeadingSchema(const json::JsonObject object)
      : json::JsonValue(object) {}

    JSON_ACCESS_STRING(SectionHeadingSchema, name);
    JSON_ACCESS_STRING(SectionHeadingSchema, type);
    JSON_ACCESS_STRING(SectionHeadingSchema, label);
  };

  class Switch : public lvgl::ObjectAccess<Switch> {
  public:
    LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Switch);

    Switch &set_label_as_static(const char *value) {
      get_label().set_text_as_static(value);
      return *this;
    }

    Switch &set_label(const char *value) {
      get_label().set_text(value);
      return *this;
    }

    Switch &set_value(bool value = true) {
      auto s = get_switch();
      if( value ) {
        s.add_state(lvgl::State::checked);
      } else {
        s.clear_state(lvgl::State::checked);
      }
      return *this;
    }

    lvgl::Label get_label() const {
      return find<lvgl::Label>(Names::label);
    }


    lvgl::Switch get_switch() const {
      return find<lvgl::Switch>(Names::switch_);
    }


    var::StringView get_value() const {
      return get_switch().has_state(lvgl::State::checked) ? "true" : "false";
    }

    Switch &set_hint_as_static(const char *value) {
      Form::set_hint_as_static(find<lvgl::Label>(Names::hint_label), value);
      return *this;
    }

    Switch &set_hint(const char *value) {
      Form::set_hint(find<lvgl::Label>(Names::hint_label), value);
      return *this;
    }

    class Schema : public json::JsonValue {
    public:
      static constexpr auto schema_type = "switch";
      Schema() : json::JsonValue(json::JsonObject()) { set_type(schema_type); }
      Schema(const json::JsonObject object) : json::JsonValue(object) {}

      JSON_ACCESS_STRING(Schema, name);
      JSON_ACCESS_STRING(Schema, type);
      JSON_ACCESS_STRING(Schema, label);
      JSON_ACCESS_STRING(Schema, hint);
      JSON_ACCESS_STRING(Schema, value);
    };

  private:
    friend Form;
    struct Names {
      static constexpr auto label = "label";
      static constexpr auto switch_ = "switch";
      static constexpr auto hint_label = "SwitchFieldHint";
    };
  };

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

    var::StringView get_value() const { return get_text_area().get_text(); }

    LineField &set_hint_as_static(const char *value) {
      Form::set_hint_as_static(find<lvgl::Label>(Names::hint_label), value);
      return *this;
    }

    LineField &set_hint(const char *value) {
      Form::set_hint(find<lvgl::Label>(Names::hint_label), value);
      return *this;
    }

    class Schema : public json::JsonValue {
    public:
      static constexpr auto schema_type = "lineField";
      Schema() : json::JsonValue(json::JsonObject()) { set_type(schema_type); }
      Schema(const json::JsonObject object) : json::JsonValue(object) {}

      JSON_ACCESS_STRING(Schema, name);
      JSON_ACCESS_STRING(Schema, type);
      JSON_ACCESS_STRING(Schema, label);
      JSON_ACCESS_STRING(Schema, hint);
      JSON_ACCESS_STRING(Schema, value);
    };

  private:
    friend Form;
    struct Names {
      static constexpr auto label = "label";
      static constexpr auto field = "field";
      static constexpr auto hint_label = "LineFieldHint";
    };
  };

  class SelectFile : public lvgl::ObjectAccess<SelectFile> {
  public:
    using Data = FileSystemWindow::Data;

    explicit SelectFile(Data &data);
    explicit SelectFile(lv_obj_t *object) { m_object = object; }

    lvgl::Label get_label() const {
      return find<lvgl::Label>(Names::select_file_label);
    }

    SelectFile &set_label_as_static(const char *value) {
      get_label().set_text_as_static(value);
      return *this;
    }

    SelectFile &set_label(const char *value) {
      get_label().set_text(value);
      return *this;
    }

    var::StringView get_value() const {
      return find<lvgl::TextArea>(Names::selected_path_label).get_text();
    }

    SelectFile &set_value(const char *value) {
      find<lvgl::TextArea>(Names::selected_path_label).set_text(value);
      return *this;
    }

    SelectFile &set_value_as_static(const char *value) {
      find<lvgl::TextArea>(Names::selected_path_label)
        .set_text_as_static(value);
      return *this;
    }

    SelectFile &set_hint_as_static(const char *value) {
      Form::set_hint_as_static(find<lvgl::Label>(Names::hint_label), value);
      return *this;
    }

    SelectFile &set_hint(const char *value) {
      Form::set_hint(find<lvgl::Label>(Names::hint_label), value);
      return *this;
    }

    class Schema : public json::JsonValue {
    public:
      static constexpr auto schema_type = "selectFile";
      Schema() : json::JsonValue(json::JsonObject()) { set_type(schema_type); }
      Schema(const json::JsonObject object) : json::JsonValue(object) {}

      JSON_ACCESS_STRING(Schema, type);
      JSON_ACCESS_STRING(Schema, name);
      JSON_ACCESS_STRING(Schema, label);
      JSON_ACCESS_STRING(Schema, hint);
      JSON_ACCESS_STRING(Schema, value);
      JSON_ACCESS_STRING(Schema, suffix);
      JSON_ACCESS_STRING_WITH_KEY(Schema, basePath, base_path);
    };

  private:
    friend Form;
    struct Names {
      static constexpr auto hint_label = "SelectFileHint";

      DESIGN_DECLARE_NAME(select_file_label);
      DESIGN_DECLARE_NAME(selected_path_label);
      DESIGN_DECLARE_NAME(select_file_modal);
      DESIGN_DECLARE_NAME(select_file_button);
      DESIGN_DECLARE_NAME(form_row);

    };

    static void handle_clicked(lv_event_t *e);
    static void handle_notified(lv_event_t *e);
    static void handle_text_focused(lv_event_t *e);
  };

  class Select : public lvgl::ObjectAccess<Select> {
  public:
    LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Select);

    Select &set_label_as_static(const char *value) {
      get_label().set_text_as_static(value);
      return *this;
    }

    var::StringView get_value() const;

    lvgl::Label get_label() const { return find<lvgl::Label>(Names::label); }

    lvgl::Dropdown get_dropdown() const {
      return find<lvgl::Dropdown>(Names::dropdown);
    }

    Select &set_hint_as_static(const char *value) {
      Form::set_hint_as_static(find<lvgl::Label>(Names::hint_label), value);
      return *this;
    }

    Select &set_hint(const char *value) {
      Form::set_hint(find<lvgl::Label>(Names::hint_label), value);
      return *this;
    }

    Select &set_value(const char *value);

    class Schema : public json::JsonValue {
    public:
      static constexpr auto schema_type = "select";
      Schema() : json::JsonValue(json::JsonObject()) { set_type(schema_type); }

      Schema(const json::JsonObject object) : json::JsonValue(object) {}

      JSON_ACCESS_STRING(Schema, name);
      JSON_ACCESS_STRING(Schema, type);
      JSON_ACCESS_STRING(Schema, label);
      JSON_ACCESS_STRING(Schema, hint);
      JSON_ACCESS_STRING(Schema, value);
      JSON_ACCESS_STRING(Schema, options);
    };

  private:
    friend Form;
    struct Names {
      static constexpr auto label = "Label";
      static constexpr auto dropdown = "Select";
      static constexpr auto hint_label = "SelectHint";
    };
  };

  class Schema : public json::JsonValue {
  public:
    static constexpr auto schema_type = "form";
    JSON_ACCESS_CONSTRUCT_OBJECT(Schema);

    using IsOverwrite = fs::FileObject::IsOverwrite;

    Schema(
      var::StringView file_path,
      IsOverwrite is_overwrite = IsOverwrite::no);
    ~Schema();

    JSON_ACCESS_STRING(Schema, type);
    JSON_ACCESS_STRING(Schema, name);
    JSON_ACCESS_ARRAY(Schema, json::JsonObject, input);

  private:
    API_AC(Schema, var::PathString, path);
    IsOverwrite m_is_overwrite;
  };

  Form(const char *name, Schema schema);

  json::JsonObject get_json_object() const;
  Form& set_values(json::JsonObject object);

  var::StringView get_value(lvgl::Object child) const;
  Form& set_value(lvgl::Object child, const char * value);

  static constexpr auto not_a_value = "$$$notAFormValue";

private:
  template <class InputClass> InputClass check_type(lvgl::Object object) const {
    if (object
          .find<InputClass, lvgl::IsAssertOnFail::no>(
            InputClass::Names::hint_label)
          .is_valid()) {
      return object.get<InputClass>();
    }
    return InputClass((lv_obj_t *)nullptr);
  }
};

} // namespace design

#endif // DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_
