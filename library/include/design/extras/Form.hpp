//
// Created by Tyler Gilbert on 12/13/21.
//

#ifndef DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_

#include <lvgl/Dropdown.hpp>
#include <lvgl/Label.hpp>
#include <lvgl/TextArea.hpp>

#include <json/Json.hpp>

#include "FileSystemWindow.hpp"
#include "../Typography.hpp"

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
    SectionHeadingSchema() : json::JsonValue(json::JsonObject()) { set_type(schema_type); }
    SectionHeadingSchema(const json::JsonObject object) : json::JsonValue(object) {}

    JSON_ACCESS_STRING(SectionHeadingSchema, name);
    JSON_ACCESS_STRING(SectionHeadingSchema, type);
    JSON_ACCESS_STRING(SectionHeadingSchema, label);
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

    const char *get_value() const { return get_text_area().get_text(); }

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
    struct Names {
      static constexpr auto label = "Label";
      static constexpr auto field = "Field";
      static constexpr auto hint_label = "HintLabel";
    };
  };

  class SelectFile : public lvgl::ObjectAccess<SelectFile> {
  public:
    using Data = FileSystemWindow::Data;

    explicit SelectFile(Data &data);
    explicit SelectFile(lv_obj_t *object) { m_object = object; }

    lvgl::Label get_label() const { return find<lvgl::Label>(Names::select_file_label); }

    SelectFile &set_label_as_static(const char *value) {
      get_label().set_text_as_static(value);
      return *this;
    }

    SelectFile &set_label(const char *value) {
      get_label().set_text(value);
      return *this;
    }

    const char *get_value() const {
      return find<lvgl::TextArea>(Names::selected_path_label).get_text();
    }

    SelectFile &set_value(const char *value) {
      find<lvgl::TextArea>(Names::selected_path_label).set_text(value);
      return *this;
    }

    SelectFile &set_value_as_static(const char *value) {
      find<lvgl::TextArea>(Names::selected_path_label).set_text_as_static(value);
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
      JSON_ACCESS_STRING_WITH_KEY(Schema, basePath, base_path);
    };

  private:
    struct Names {
      static constexpr auto select_file_label = "Label";
      static constexpr auto hint_label = "HintLabel";
      static constexpr auto select_file_button = "Button";
      static constexpr auto select_file_modal = "Modal";
      static constexpr auto selected_path_label = "FilePath";
    };

    static void handle_clicked(lv_event_t *e);
    static void handle_notified(lv_event_t *e);
  };

  class Select : public lvgl::ObjectAccess<Select> {
  public:
    LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Select);

    Select &set_label_as_static(const char *value) {
      get_label().set_text_as_static(value);
      return *this;
    }

    const char *get_value() const { return get_dropdown().get_text(); }

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

    Select &set_value(const char *value) {
      get_dropdown().set_text(value);
      return *this;
    }

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
    struct Names {
      static constexpr auto label = "Label";
      static constexpr auto dropdown = "Select";
      static constexpr auto hint_label = "HintLabel";
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
};

} // namespace design

#endif // DESIGNAPI_DESIGN_EXTRAS_FORM_HPP_
