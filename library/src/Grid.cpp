//
// Created by Tyler Gilbert on 12/4/21.
//

#include <json.hpp>
#include <lvgl.hpp>

#include "design/Grid.hpp"

using namespace design;

NakedContainer::NakedContainer(const char *name) {
  construct_object(name);
  add_style("naked");
}

#if THIS_IS_NOT_READY
Container &Container::update_view(const json::JsonObject json_object) {
  API_RETURN_VALUE_IF_ERROR(*this);

  return *this;
}

Container &Container::update_model(json::JsonObject json_object) {
  API_RETURN_VALUE_IF_ERROR(*this);
  const auto key_list = json_object.get_key_list();
  for (const auto key : key_list) {
    auto child = find<Object, IsAssertOnFail::no>(var::KeyString(key));
    if (child.is_valid()) {
    }
  }
  return *this;
}

json::JsonObject Container::get_value(lvgl::Object object) {
  if (object.is_class<Label>()) {
    return JsonObject().insert(
      "value",
      JsonString(object.get<Label>().get_text()));
  }

  if (object.is_class<Roller>()) {
    return JsonNull();
  }

  if (object.is_class<Calendar>()) {
    return JsonNull();
  }

  if (object.is_class<TextArea>()) {
    return JsonString(object.get<TextArea>().get_text());
  }

  if (object.is_class<Bar>()) {
    auto bar = object.get<Bar>();
    const auto range = bar.get_range();
    const auto value = bar.get_value();
    return JsonObject()
      .insert("value", JsonInteger(value))
      .insert("minimum", JsonInteger(range.minimum()))
      .insert("maximum", JsonInteger(range.maximum()));
  }

  if (object.is_class<Slider>()) {
    auto slider = object.get<Slider>();
    const auto range = slider.get_range();
    const auto value = slider.get_value();
    return JsonObject()
      .insert("value", JsonInteger(value))
      .insert("minimum", JsonInteger(range.minimum()))
      .insert("maximum", JsonInteger(range.maximum()));
  }

  if (object.is_class<List>()) {
    JsonArray result;
    for (auto child : object) {
    }
  }

  if (object.is_class<SpinBox>()) {
    JsonArray result;
    for (auto child : object) {
    }
  }

  if (object.is_class<Spinner>()) {
    JsonArray result;
    for (auto child : object) {
    }
  }

  if (object.is_class<Meter>()) {
    JsonArray result;
    for (auto child : object) {
    }
  }

  if (
    object.is_class<Button>() || object.is_class<Switch>()
    || object.is_class<CheckBox>()) {
    return object.get<Object>().has_state(State::checked)
             ? JsonValue(JsonTrue())
             : JsonValue(JsonFalse());
  }
}

void Container::set_value(lvgl::Object object, json::JsonObject value) {

  if (value.is_object()) {
    // check to see if object has flags
  }

  if (object.is_class<Label>()) {
    API_ASSERT(value.is_string());
    object.get<Label>().set_text(value.to_cstring());
    return;
  }

  if (object.is_class<TextArea>()) {
    API_ASSERT(value.is_string());
    object.get<Label>().set_text(value.to_cstring());
    return;
  }

  if (object.is_class<List>()) {
    JsonArray result;
    for (auto child : object) {
    }
  }

  if (object.is_class<Button>() || object.is_class<Switch>()) {
    return object.get<Object>().has_state(State::checked)
             ? JsonValue(JsonTrue())
             : JsonValue(JsonFalse());
  }
}
#endif

Container::Container(const char *name) {
  construct_object(name);
  add_style("container");
}

const lvgl::Style &Row::get_style() {
  static const auto style
    = lvgl::Style()
        .set_flex_layout()
        .set_flex_flow(lvgl::FlexFlow::row)
        .set_flex_align(lvgl::SetFlexAlign().set_align_main(lvgl::FlexAlign::start))
        .set_column_padding(0);
  return style;
}

Row::Row(const char *name) {
  construct_object(name);
  set_flex_layout()
    .set_flex_flow(lvgl::FlexFlow::row)
    .set_flex_align(SetFlexAlign().set_align_main(lvgl::FlexAlign::start))
    .add_style("row");
}

const lvgl::Style &Column::get_style() {
  static const auto style
    = lvgl::Style()
        .set_flex_layout()
        .set_flex_flow(FlexFlow::column)
        .set_flex_align(SetFlexAlign().set_align_main(FlexAlign::start))
        .set_row_padding(0);
  return style;
}

Column::Column(const char *name) {
  construct_object(name);

  set_flex_layout()
    .set_flex_flow(FlexFlow::column)
    .set_flex_align(SetFlexAlign().set_align_main(FlexAlign::start))
    .add_style("col");
}

// extract a JSON Object from the Object using names
json::JsonObject get_json_object(lvgl::Object object) {
  API_RETURN_VALUE_IF_ERROR(json::JsonObject());
  json::JsonObject result;
  for (auto child : object) {
    const var::StringView key_name = child.name();
    if (child.is_class<Label>()) {
      result.insert(child.name(), JsonString(child.get<Label>().get_text()));
      continue;
    }

    if (child.is_class<TextArea>()) {
      result.insert(child.name(), JsonString(child.get<TextArea>().get_text()));
      continue;
    }

    if (child.is_class<Button>() || child.is_class<Switch>()) {
      const auto value = child.has_state(State::checked)
                           ? JsonValue(JsonTrue())
                           : JsonValue(JsonFalse());
      result.insert(child.name(), value);
      continue;
    }
  }
  return result;
}
