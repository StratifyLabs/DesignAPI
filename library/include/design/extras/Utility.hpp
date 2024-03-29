//
// Created by Tyler Gilbert on 3/4/22.
//

#ifndef DESIGNLAB_UTILITY_HPP
#define DESIGNLAB_UTILITY_HPP

#if defined __link

#include <json/Json.hpp>
#include <lvgl/Style.hpp>
#include <var/StringView.hpp>
#include <var/MagicEnum.hpp>

namespace design {


class Utility {
public:
  template <typename Type> struct Converter {
    static constexpr decltype(&var::MagicEnum<Type>::to_string_view) to_string_view =
      &var::MagicEnum<Type>::to_string_view;
    static constexpr decltype(&var::MagicEnum<Type>::from_string_with_invalid)
      from_string = &var::MagicEnum<Type>::from_string_with_invalid;
    //this is only OK because magic_enum string views are always null-terminated
    static const char * to_cstring(Type type){
      return to_string_view(type).data();
    }
  };

  static constexpr auto property = Converter<lvgl::Property>{};
  static constexpr auto text_decoration = Converter<lvgl::TextDecoration>{};
  static constexpr auto text_alignment = Converter<lvgl::TextAlignment>{};
  static constexpr auto border_side = Converter<lvgl::BorderSide>{};
  static constexpr auto gradient_direction = Converter<lvgl::GradientDirection>{};
  static constexpr auto base_direction = Converter<lvgl::BaseDirection>{};
  static constexpr auto direction = Converter<lvgl::Direction>{};
  static constexpr auto alignment = Converter<lvgl::Alignment>{};
  static constexpr auto flex_flow = Converter<lvgl::FlexFlow>{};
  static constexpr auto flex_align = Converter<lvgl::FlexAlign>{};
  static constexpr auto state = Converter<lvgl::State>{};
  static constexpr auto scroll_bar_mode = Converter<lvgl::ScrollBarMode>{};
  static constexpr auto scroll_snap = Converter<lvgl::ScrollSnap>{};
  static constexpr auto is_animate = Converter<lvgl::IsAnimate>{};
  static constexpr auto part = Converter<lvgl::Part>{};
  static constexpr auto blend_mode = Converter<lvgl::BlendMode>{};
  static constexpr auto opacity = Converter<lvgl::Opacity>{};
  static constexpr auto property_group = Converter<lvgl::PropertyGroup>{};
  static constexpr auto property_type = Converter<lvgl::PropertyType>{};
  static constexpr auto load_animation = Converter<lvgl::LoadAnimation>{};


  static constexpr auto invalid_property_type_class_name = "Invalid";

  static const char *to_class_name_cstring(lvgl::PropertyType value);
  static lvgl::PropertyType property_type_from_string(var::StringView value);

  static lvgl::PropertyDescription get_property_description(lvgl::Property property);

  static constexpr auto property_group_list = std::initializer_list<lvgl::PropertyGroup>{
    lvgl::PropertyGroup::invalid,       lvgl::PropertyGroup::alignment,
    lvgl::PropertyGroup::animation,     lvgl::PropertyGroup::arc,
    lvgl::PropertyGroup::background,    lvgl::PropertyGroup::border,
    lvgl::PropertyGroup::image,         lvgl::PropertyGroup::line,
    lvgl::PropertyGroup::miscellaneous, lvgl::PropertyGroup::outline,
    lvgl::PropertyGroup::padding,       lvgl::PropertyGroup::shadow,
    lvgl::PropertyGroup::size,          lvgl::PropertyGroup::text,
    lvgl::PropertyGroup::transform,
  };

  static constexpr auto property_list = std::initializer_list<lvgl::PropertyDescription>{
    {lvgl::Property::invalid, lvgl::PropertyType::invalid, lvgl::PropertyGroup::invalid},
    {lvgl::Property::alignment, lvgl::PropertyType::alignment,
     lvgl::PropertyGroup::alignment},
    {lvgl::Property::animation_speed, lvgl::PropertyType::invalid,
     lvgl::PropertyGroup::animation},
    {lvgl::Property::animation_time, lvgl::PropertyType::milliseconds,
     lvgl::PropertyGroup::animation},
    {lvgl::Property::arc_color, lvgl::PropertyType::color, lvgl::PropertyGroup::arc},
    {lvgl::Property::arc_image_source, lvgl::PropertyType::image_source,
     lvgl::PropertyGroup::arc},
    {lvgl::Property::arc_opacity, lvgl::PropertyType::opacity, lvgl::PropertyGroup::arc},
    {lvgl::Property::arc_rounded, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::arc},
    {lvgl::Property::arc_width, lvgl::PropertyType::coordinate, lvgl::PropertyGroup::arc},
    {lvgl::Property::background_color, lvgl::PropertyType::color,
     lvgl::PropertyGroup::background},
    {lvgl::Property::background_gradient_color, lvgl::PropertyType::color,
     lvgl::PropertyGroup::background},
    {lvgl::Property::background_gradient_direction,
     lvgl::PropertyType::gradient_direction, lvgl::PropertyGroup::background},
    {lvgl::Property::background_gradient_stop, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::background},
    {lvgl::Property::background_image_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::background},
    {lvgl::Property::background_image_recolor, lvgl::PropertyType::color,
     lvgl::PropertyGroup::background},
    {lvgl::Property::background_image_recolor_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::invalid},
    {lvgl::Property::background_image_source, lvgl::PropertyType::image_source,
     lvgl::PropertyGroup::background},
    {lvgl::Property::background_image_tiled, lvgl::PropertyType::boolean,
     lvgl::PropertyGroup::background},
    {lvgl::Property::background_main_stop, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::background},
    {lvgl::Property::background_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::background},
    {lvgl::Property::base_direction, lvgl::PropertyType::base_direction,
     lvgl::PropertyGroup::miscellaneous},
    {lvgl::Property::blend_mode, lvgl::PropertyType::blend_mode,
     lvgl::PropertyGroup::invalid},
    {lvgl::Property::border_color, lvgl::PropertyType::color,
     lvgl::PropertyGroup::border},
    {lvgl::Property::border_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::border},
    {lvgl::Property::border_post, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::border},
    {lvgl::Property::border_side, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::border},
    {lvgl::Property::border_width, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::border},
    {lvgl::Property::bottom_padding, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::border},
    {lvgl::Property::clip_corner, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::border},
    {lvgl::Property::color_filter_descriptor, lvgl::PropertyType::color_filter_descriptor,
     lvgl::PropertyGroup::invalid},
    {lvgl::Property::color_filter_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::invalid},
    {lvgl::Property::column_padding, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::padding},
    {lvgl::Property::height, lvgl::PropertyType::coordinate, lvgl::PropertyGroup::size},
    {lvgl::Property::image_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::image},
    {lvgl::Property::image_recolor, lvgl::PropertyType::color,
     lvgl::PropertyGroup::image},
    {lvgl::Property::image_recolor_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::image},
    {lvgl::Property::layout, lvgl::PropertyType::layout, lvgl::PropertyGroup::alignment},
    {lvgl::Property::left_padding, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::padding},
    {lvgl::Property::line_color, lvgl::PropertyType::color, lvgl::PropertyGroup::line},
    {lvgl::Property::line_dash_gap, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::line},
    {lvgl::Property::line_dash_width, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::line},
    {lvgl::Property::line_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::line},
    {lvgl::Property::line_rounded, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::line},
    {lvgl::Property::line_width, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::line},
    {lvgl::Property::maximum_height, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::size},
    {lvgl::Property::maximum_width, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::size},
    {lvgl::Property::minimum_height, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::size},
    {lvgl::Property::minimum_width, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::size},
    {lvgl::Property::opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::miscellaneous},
    {lvgl::Property::outline_color, lvgl::PropertyType::color,
     lvgl::PropertyGroup::outline},
    {lvgl::Property::outline_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::outline},
    {lvgl::Property::outline_padding, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::outline},
    {lvgl::Property::outline_width, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::outline},
    {lvgl::Property::radius, lvgl::PropertyType::coordinate, lvgl::PropertyGroup::border},
    {lvgl::Property::right_padding, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::padding},
    {lvgl::Property::row_padding, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::padding},
    {lvgl::Property::shadow_color, lvgl::PropertyType::color,
     lvgl::PropertyGroup::shadow},
    {lvgl::Property::shadow_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::shadow},
    {lvgl::Property::shadow_spread, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::shadow},
    {lvgl::Property::shadow_width, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::shadow},
    {lvgl::Property::shadow_x_offset, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::shadow},
    {lvgl::Property::shadow_y_offset, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::shadow},
    {lvgl::Property::text_alignment, lvgl::PropertyType::text_alignment,
     lvgl::PropertyGroup::text},
    {lvgl::Property::text_color, lvgl::PropertyType::color, lvgl::PropertyGroup::text},
    {lvgl::Property::text_decoration, lvgl::PropertyType::text_decoration,
     lvgl::PropertyGroup::text},
    {lvgl::Property::text_font, lvgl::PropertyType::font, lvgl::PropertyGroup::text},
    {lvgl::Property::text_letter_spacing, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::text},
    {lvgl::Property::text_line_spacing, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::text},
    {lvgl::Property::text_opacity, lvgl::PropertyType::opacity,
     lvgl::PropertyGroup::text},
    {lvgl::Property::top_padding, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::padding},
    {lvgl::Property::transform_angle, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::transform},
    {lvgl::Property::transform_height, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::transform},
    {lvgl::Property::transform_width, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::transform},
    {lvgl::Property::transform_zoom, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::transform},
    {lvgl::Property::transition, lvgl::PropertyType::invalid,
     lvgl::PropertyGroup::transform},
    {lvgl::Property::translate_x, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::transform},
    {lvgl::Property::translate_y, lvgl::PropertyType::coordinate,
     lvgl::PropertyGroup::transform},
    {lvgl::Property::width, lvgl::PropertyType::coordinate, lvgl::PropertyGroup::size},
    {lvgl::Property::x, lvgl::PropertyType::coordinate, lvgl::PropertyGroup::alignment},
    {lvgl::Property::y, lvgl::PropertyType::coordinate, lvgl::PropertyGroup::alignment},
    {lvgl::Property::any, lvgl::PropertyType::invalid, lvgl::PropertyGroup::invalid}};

  static constexpr auto alignment_list = {
    lvgl::Alignment::default_,          lvgl::Alignment::top_left,
    lvgl::Alignment::top_middle,        lvgl::Alignment::top_right,
    lvgl::Alignment::bottom_left,       lvgl::Alignment::bottom_middle,
    lvgl::Alignment::bottom_right,      lvgl::Alignment::left_middle,
    lvgl::Alignment::right_middle,      lvgl::Alignment::center,
    lvgl::Alignment::out_top_left,      lvgl::Alignment::out_top_middle,
    lvgl::Alignment::out_top_right,     lvgl::Alignment::out_bottom_left,
    lvgl::Alignment::out_bottom_middle, lvgl::Alignment::out_bottom_right,
    lvgl::Alignment::out_left_top,      lvgl::Alignment::out_left_middle,
    lvgl::Alignment::out_left_bottom,   lvgl::Alignment::out_right_top,
    lvgl::Alignment::out_right_middle,  lvgl::Alignment::out_right_bottom};

  static constexpr auto base_direction_list = {
    lvgl::BaseDirection::auto_, lvgl::BaseDirection::left_to_right,
    lvgl::BaseDirection::right_to_left, lvgl::BaseDirection::neutral,
    lvgl::BaseDirection::weak};

  static constexpr auto blend_mode_list = {
    lvgl::BlendMode::normal, lvgl::BlendMode::additive, lvgl::BlendMode::subtractive};

  static constexpr auto border_side_list = {
    lvgl::BorderSide::none,    lvgl::BorderSide::bottom, lvgl::BorderSide::top,
    lvgl::BorderSide::left,    lvgl::BorderSide::right,  lvgl::BorderSide::full,
    lvgl::BorderSide::internal};

  static constexpr auto direction_list = {
    lvgl::Direction::none,     lvgl::Direction::left,   lvgl::Direction::right,
    lvgl::Direction::top,      lvgl::Direction::bottom, lvgl::Direction::horizontal,
    lvgl::Direction::vertical, lvgl::Direction::all};

  static constexpr auto flex_flow_list = {
    lvgl::FlexFlow::row,
    lvgl::FlexFlow::column,
    lvgl::FlexFlow::row_wrap,
    lvgl::FlexFlow::row_reverse,
    lvgl::FlexFlow::row_wrap_reverse,
    lvgl::FlexFlow::column_wrap,
    lvgl::FlexFlow::column_reverse,
    lvgl::FlexFlow::column_wrap_reverse};

  static constexpr auto flex_align_list = {
    lvgl::FlexAlign::start,        lvgl::FlexAlign::end,
    lvgl::FlexAlign::center,       lvgl::FlexAlign::space_evenly,
    lvgl::FlexAlign::space_around, lvgl::FlexAlign::space_between};

  static constexpr auto gradient_direction_list = {
    lvgl::GradientDirection::none, lvgl::GradientDirection::vertical,
    lvgl::GradientDirection::horizontal};

  static constexpr auto text_alignment_list = {
    lvgl::TextAlignment::auto_, lvgl::TextAlignment::left, lvgl::TextAlignment::center,
    lvgl::TextAlignment::right};

  static constexpr auto text_decoration_list = {
    lvgl::TextDecoration::none, lvgl::TextDecoration::underline,
    lvgl::TextDecoration::strikethrough};

  // static lvgl::PropertyValue get_property_value(var::StringView name);
  static lvgl::PropertyValue
  get_property_value(json::JsonValue value, lvgl::PropertyType type);

  static var::StringView
  property_value_to_string_view(lvgl::PropertyValue value, lvgl::PropertyType type);
};

} // namespace design

#endif

#endif // DESIGNLAB_UTILITY_HPP
