//
// Created by Tyler Gilbert on 3/4/22.
//

#if defined __link

#include <lvgl/macros.hpp>
#include <var/MagicEnum.hpp>

#include "design/extras/Utility.hpp"

using namespace lvgl;
using namespace design;
using namespace var;

const char *Utility::to_class_name_cstring(lvgl::PropertyType value) {
  switch (value) {
  case PropertyType::invalid:
    return invalid_property_type_class_name;
  case PropertyType::alignment:
    return "Alignment";
  case PropertyType::base_direction:
    return "BaseDirection";
  case PropertyType::blend_mode:
    return "BlendMode";
  case PropertyType::boolean:
    return "Boolean";
  case PropertyType::border_side:
    return "BorderSide";
  case PropertyType::color:
    return "Color";
  case PropertyType::color_filter_descriptor:
  case PropertyType::coordinate:
  case PropertyType::font:
  case PropertyType::image_source:
  case PropertyType::layout:
  case PropertyType::milliseconds:
  case PropertyType::number:
  case PropertyType::opacity:
  case PropertyType::transition_descriptor:
    return "Invalid";
  case PropertyType::direction:
    return "Direction";
  case PropertyType::flex_align:
    return "FlexAlign";
  case PropertyType::flex_flow:
    return "FlexFlow";
  case PropertyType::gradient_direction:
    return "GradientDirection";
  case PropertyType::text_alignment:
    return "TextAlignment";
  case PropertyType::text_decoration:
    return "TextDecoration";
  }
  return invalid_property_type_class_name;
}

PropertyDescription Utility::get_property_description(Property property) {
  for (const auto &description : property_list) {
    if (property == description.property) {
      return description;
    }
  }
  return {};
}

lvgl::PropertyValue
Utility::get_property_value(json::JsonValue value, lvgl::PropertyType type) {

  switch (type) {
  case PropertyType::opacity:
  case PropertyType::coordinate:
  case PropertyType::number:
  case PropertyType::milliseconds: {
    if (value.to_string_view().is_empty()) {
      break;
    }
    const auto value_string = value.to_string_view();

    if (value_string.back() == '%') {
      return Percent(value.to_integer()).value();
    }

    return lvgl::PropertyValue(s32(value.to_integer()));
  }

  case PropertyType::color:
    return Color::from_hex(
      value.to_string_view().to_unsigned_long(StringView::Base::auto_));
  case PropertyType::boolean:
    return value.to_bool();
  case PropertyType::border_side:
    return s32(border_side.from_string(value.to_string_view(), BorderSide::invalid));
  case PropertyType::direction:
    return s32(direction.from_string(value.to_string_view(), Direction::invalid));
  case PropertyType::alignment:
    return s32(alignment.from_string(value.to_string_view(), Alignment::invalid));
  case PropertyType::base_direction:
    return s32(
      base_direction.from_string(value.to_string_view(), BaseDirection::invalid));
  case PropertyType::blend_mode:
    return s32(blend_mode.from_string(value.to_string_view(), BlendMode::invalid));
  case PropertyType::flex_align:
    return s32(flex_align.from_string(value.to_string_view(), FlexAlign::invalid));
  case PropertyType::flex_flow:
    return s32(flex_flow.from_string(value.to_string_view(), FlexFlow::invalid));
  case PropertyType::gradient_direction:
    return s32(
      gradient_direction.from_string(value.to_string_view(), GradientDirection::invalid));
  case PropertyType::text_alignment:
    return s32(
      text_alignment.from_string(value.to_string_view(), TextAlignment::invalid));
  case PropertyType::text_decoration:
    return s32(
      text_decoration.from_string(value.to_string_view(), TextDecoration::invalid));
  case PropertyType::invalid:
  case PropertyType::font:
  case PropertyType::layout:
  case PropertyType::color_filter_descriptor:
  case PropertyType::transition_descriptor:
  case PropertyType::image_source:
    break;
  }
  return lvgl::PropertyValue(s32(0));
}

var::StringView
Utility::property_value_to_string_view(PropertyValue value, PropertyType type) {
  switch (type) {
  case PropertyType::opacity:
  case PropertyType::coordinate:
  case PropertyType::number:
  case PropertyType::milliseconds:
  case PropertyType::color:
  case PropertyType::boolean:
  case PropertyType::invalid:
  case PropertyType::font:
  case PropertyType::layout:
  case PropertyType::color_filter_descriptor:
  case PropertyType::transition_descriptor:
  case PropertyType::image_source:
    break;

  case PropertyType::border_side:
    return border_side.to_string_view(BorderSide(value.number()));
  case PropertyType::direction:
    return direction.to_string_view(Direction(value.number()));
  case PropertyType::alignment:
    return alignment.to_string_view(Alignment(value.number()));
  case PropertyType::base_direction:
    return base_direction.to_string_view(BaseDirection(value.number()));
  case PropertyType::blend_mode:
    return blend_mode.to_string_view(BlendMode(value.number()));
  case PropertyType::flex_align:
    return flex_align.to_string_view(FlexAlign(value.number()));
  case PropertyType::flex_flow:
    return flex_flow.to_string_view(FlexFlow(value.number()));
  case PropertyType::gradient_direction:
    return gradient_direction.to_string_view(GradientDirection(value.number()));
  case PropertyType::text_alignment:
    return text_alignment.to_string_view(TextAlignment(value.number()));
  case PropertyType::text_decoration:
    return text_decoration.to_string_view(TextDecoration(value.number()));
  }
  return "invalid";
}

#endif
