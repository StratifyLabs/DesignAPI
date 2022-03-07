//
// Created by Tyler Gilbert on 3/4/22.
//

#include <lvgl/macros.hpp>

#include "design/extras/Utility.hpp"

using namespace lvgl;
using namespace design;
using namespace var;

const char *Utility::to_cstring(Property property) {
  switch (property) {
    LVGL_PROPERTY_CASE(Property, invalid);
    LVGL_PROPERTY_CASE(Property, width);
    LVGL_PROPERTY_CASE(Property, minimum_width);
    LVGL_PROPERTY_CASE(Property, maximum_width);
    LVGL_PROPERTY_CASE(Property, height);
    LVGL_PROPERTY_CASE(Property, minimum_height);
    LVGL_PROPERTY_CASE(Property, maximum_height);
    LVGL_PROPERTY_CASE(Property, x);
    LVGL_PROPERTY_CASE(Property, y);
    LVGL_PROPERTY_CASE(Property, alignment);
    LVGL_PROPERTY_CASE(Property, transform_width);
    LVGL_PROPERTY_CASE(Property, transform_height);
    LVGL_PROPERTY_CASE(Property, translate_x);
    LVGL_PROPERTY_CASE(Property, translate_y);
    LVGL_PROPERTY_CASE(Property, transform_zoom);
    LVGL_PROPERTY_CASE(Property, transform_angle);
    LVGL_PROPERTY_CASE(Property, top_padding);
    LVGL_PROPERTY_CASE(Property, bottom_padding);
    LVGL_PROPERTY_CASE(Property, left_padding);
    LVGL_PROPERTY_CASE(Property, right_padding);
    LVGL_PROPERTY_CASE(Property, row_padding);
    LVGL_PROPERTY_CASE(Property, column_padding);
    LVGL_PROPERTY_CASE(Property, background_color);
    LVGL_PROPERTY_CASE(Property, background_color_filtered);
    LVGL_PROPERTY_CASE(Property, background_opacity);
    LVGL_PROPERTY_CASE(Property, background_gradient_color);
    LVGL_PROPERTY_CASE(Property, background_gradient_color_filtered);
    LVGL_PROPERTY_CASE(Property, background_gradient_direction);
    LVGL_PROPERTY_CASE(Property, background_main_stop);
    LVGL_PROPERTY_CASE(Property, background_gradient_stop);
    LVGL_PROPERTY_CASE(Property, background_image_source);
    LVGL_PROPERTY_CASE(Property, background_image_opacity);
    LVGL_PROPERTY_CASE(Property, background_image_recolor);
    LVGL_PROPERTY_CASE(Property, background_image_recolor_filtered);
    LVGL_PROPERTY_CASE(Property, background_image_recolor_opacity);
    LVGL_PROPERTY_CASE(Property, background_image_tiled);
    LVGL_PROPERTY_CASE(Property, border_color);
    LVGL_PROPERTY_CASE(Property, border_color_filtered);
    LVGL_PROPERTY_CASE(Property, border_opacity);
    LVGL_PROPERTY_CASE(Property, border_width);
    LVGL_PROPERTY_CASE(Property, border_side);
    LVGL_PROPERTY_CASE(Property, border_post);
    LVGL_PROPERTY_CASE(Property, outline_width);
    LVGL_PROPERTY_CASE(Property, outline_color);
    LVGL_PROPERTY_CASE(Property, outline_color_filtered);
    LVGL_PROPERTY_CASE(Property, outline_opacity);
    LVGL_PROPERTY_CASE(Property, outline_padding);
    LVGL_PROPERTY_CASE(Property, shadow_width);
    LVGL_PROPERTY_CASE(Property, shadow_x_offset);
    LVGL_PROPERTY_CASE(Property, shadow_y_offset);
    LVGL_PROPERTY_CASE(Property, shadow_spread);
    LVGL_PROPERTY_CASE(Property, shadow_color);
    LVGL_PROPERTY_CASE(Property, shadow_color_filtered);
    LVGL_PROPERTY_CASE(Property, shadow_opacity);
    LVGL_PROPERTY_CASE(Property, image_opacity);
    LVGL_PROPERTY_CASE(Property, image_recolor);
    LVGL_PROPERTY_CASE(Property, image_recolor_filtered);
    LVGL_PROPERTY_CASE(Property, image_recolor_opacity);
    LVGL_PROPERTY_CASE(Property, line_width);
    LVGL_PROPERTY_CASE(Property, line_dash_width);
    LVGL_PROPERTY_CASE(Property, line_dash_gap);
    LVGL_PROPERTY_CASE(Property, line_rounded);
    LVGL_PROPERTY_CASE(Property, line_color);
    LVGL_PROPERTY_CASE(Property, line_color_filtered);
    LVGL_PROPERTY_CASE(Property, line_opacity);
    LVGL_PROPERTY_CASE(Property, arc_width);
    LVGL_PROPERTY_CASE(Property, arc_rounded);
    LVGL_PROPERTY_CASE(Property, arc_color);
    LVGL_PROPERTY_CASE(Property, arc_color_filtered);
    LVGL_PROPERTY_CASE(Property, arc_opacity);
    LVGL_PROPERTY_CASE(Property, arc_image_source);
    LVGL_PROPERTY_CASE(Property, text_color);
    LVGL_PROPERTY_CASE(Property, text_color_filtered);
    LVGL_PROPERTY_CASE(Property, text_opacity);
    LVGL_PROPERTY_CASE(Property, text_font);
    LVGL_PROPERTY_CASE(Property, text_letter_spacing);
    LVGL_PROPERTY_CASE(Property, text_line_spacing);
    LVGL_PROPERTY_CASE(Property, text_decoration);
    LVGL_PROPERTY_CASE(Property, text_alignment);
    LVGL_PROPERTY_CASE(Property, radius);
    LVGL_PROPERTY_CASE(Property, clip_corner);
    LVGL_PROPERTY_CASE(Property, opacity);
    LVGL_PROPERTY_CASE(Property, color_filter_descriptor);
    LVGL_PROPERTY_CASE(Property, color_filter_opacity);
    LVGL_PROPERTY_CASE(Property, animation_time);
    LVGL_PROPERTY_CASE(Property, animation_speed);
    LVGL_PROPERTY_CASE(Property, transition);
    LVGL_PROPERTY_CASE(Property, blend_mode);
    LVGL_PROPERTY_CASE(Property, layout);
    LVGL_PROPERTY_CASE(Property, base_direction);
    LVGL_PROPERTY_CASE(Property, any);
  }
  return "unknown";
}

Property Utility::property_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(Property, width)
  LVGL_PROPERTY_STRING_CASE(Property, minimum_width)
  LVGL_PROPERTY_STRING_CASE(Property, maximum_width)
  LVGL_PROPERTY_STRING_CASE(Property, height)
  LVGL_PROPERTY_STRING_CASE(Property, minimum_height)
  LVGL_PROPERTY_STRING_CASE(Property, maximum_height)
  LVGL_PROPERTY_STRING_CASE(Property, x)
  LVGL_PROPERTY_STRING_CASE(Property, y)
  LVGL_PROPERTY_STRING_CASE(Property, alignment)
  LVGL_PROPERTY_STRING_CASE(Property, transform_width)
  LVGL_PROPERTY_STRING_CASE(Property, transform_height)
  LVGL_PROPERTY_STRING_CASE(Property, translate_x)
  LVGL_PROPERTY_STRING_CASE(Property, translate_y)
  LVGL_PROPERTY_STRING_CASE(Property, transform_zoom)
  LVGL_PROPERTY_STRING_CASE(Property, transform_angle)
  LVGL_PROPERTY_STRING_CASE(Property, top_padding)
  LVGL_PROPERTY_STRING_CASE(Property, bottom_padding)
  LVGL_PROPERTY_STRING_CASE(Property, left_padding)
  LVGL_PROPERTY_STRING_CASE(Property, right_padding)
  LVGL_PROPERTY_STRING_CASE(Property, row_padding)
  LVGL_PROPERTY_STRING_CASE(Property, column_padding)
  LVGL_PROPERTY_STRING_CASE(Property, background_color)
  LVGL_PROPERTY_STRING_CASE(Property, background_color_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, background_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, background_gradient_color)
  LVGL_PROPERTY_STRING_CASE(Property, background_gradient_color_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, background_gradient_direction)
  LVGL_PROPERTY_STRING_CASE(Property, background_main_stop)
  LVGL_PROPERTY_STRING_CASE(Property, background_gradient_stop)
  LVGL_PROPERTY_STRING_CASE(Property, background_image_source)
  LVGL_PROPERTY_STRING_CASE(Property, background_image_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, background_image_recolor)
  LVGL_PROPERTY_STRING_CASE(Property, background_image_recolor_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, background_image_recolor_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, background_image_tiled)
  LVGL_PROPERTY_STRING_CASE(Property, border_color)
  LVGL_PROPERTY_STRING_CASE(Property, border_color_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, border_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, border_width)
  LVGL_PROPERTY_STRING_CASE(Property, border_side)
  LVGL_PROPERTY_STRING_CASE(Property, border_post)
  LVGL_PROPERTY_STRING_CASE(Property, outline_width)
  LVGL_PROPERTY_STRING_CASE(Property, outline_color)
  LVGL_PROPERTY_STRING_CASE(Property, outline_color_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, outline_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, outline_padding)
  LVGL_PROPERTY_STRING_CASE(Property, shadow_width)
  LVGL_PROPERTY_STRING_CASE(Property, shadow_x_offset)
  LVGL_PROPERTY_STRING_CASE(Property, shadow_y_offset)
  LVGL_PROPERTY_STRING_CASE(Property, shadow_spread)
  LVGL_PROPERTY_STRING_CASE(Property, shadow_color)
  LVGL_PROPERTY_STRING_CASE(Property, shadow_color_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, shadow_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, image_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, image_recolor)
  LVGL_PROPERTY_STRING_CASE(Property, image_recolor_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, image_recolor_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, line_width)
  LVGL_PROPERTY_STRING_CASE(Property, line_dash_width)
  LVGL_PROPERTY_STRING_CASE(Property, line_dash_gap)
  LVGL_PROPERTY_STRING_CASE(Property, line_rounded)
  LVGL_PROPERTY_STRING_CASE(Property, line_color)
  LVGL_PROPERTY_STRING_CASE(Property, line_color_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, line_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, arc_width)
  LVGL_PROPERTY_STRING_CASE(Property, arc_rounded)
  LVGL_PROPERTY_STRING_CASE(Property, arc_color)
  LVGL_PROPERTY_STRING_CASE(Property, arc_color_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, arc_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, arc_image_source)
  LVGL_PROPERTY_STRING_CASE(Property, text_color)
  LVGL_PROPERTY_STRING_CASE(Property, text_color_filtered)
  LVGL_PROPERTY_STRING_CASE(Property, text_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, text_font)
  LVGL_PROPERTY_STRING_CASE(Property, text_letter_spacing)
  LVGL_PROPERTY_STRING_CASE(Property, text_line_spacing)
  LVGL_PROPERTY_STRING_CASE(Property, text_decoration)
  LVGL_PROPERTY_STRING_CASE(Property, text_alignment)
  LVGL_PROPERTY_STRING_CASE(Property, radius)
  LVGL_PROPERTY_STRING_CASE(Property, clip_corner)
  LVGL_PROPERTY_STRING_CASE(Property, opacity)
  LVGL_PROPERTY_STRING_CASE(Property, color_filter_descriptor)
  LVGL_PROPERTY_STRING_CASE(Property, color_filter_opacity)
  LVGL_PROPERTY_STRING_CASE(Property, animation_time)
  LVGL_PROPERTY_STRING_CASE(Property, animation_speed)
  LVGL_PROPERTY_STRING_CASE(Property, transition)
  LVGL_PROPERTY_STRING_CASE(Property, blend_mode)
  LVGL_PROPERTY_STRING_CASE(Property, layout)
  LVGL_PROPERTY_STRING_CASE(Property, base_direction)
  LVGL_PROPERTY_STRING_CASE(Property, any)

  return Property::invalid;
}

const char *Utility::to_cstring(TextDecoration value) {
  switch (value) {
    LVGL_PROPERTY_CASE(TextDecoration, invalid);
    LVGL_PROPERTY_CASE(TextDecoration, none);
    LVGL_PROPERTY_CASE(TextDecoration, underline);
    LVGL_PROPERTY_CASE(TextDecoration, strikethrough);
  }
  return "unknown";
}
TextDecoration
Utility::text_decoration_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(TextDecoration, none)
  LVGL_PROPERTY_STRING_CASE(TextDecoration, underline)
  LVGL_PROPERTY_STRING_CASE(TextDecoration, strikethrough)
  return TextDecoration::invalid;
}

const char *Utility::to_cstring(TextAlignment value) {
  switch (value) {
    LVGL_PROPERTY_CASE(TextAlignment, invalid);
    LVGL_PROPERTY_CASE(TextAlignment, auto_);
    LVGL_PROPERTY_CASE(TextAlignment, left);
    LVGL_PROPERTY_CASE(TextAlignment, right);
    LVGL_PROPERTY_CASE(TextAlignment, center);
  }
  return "unknown";
}
TextAlignment Utility::text_alignment_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(TextAlignment, auto_);
  LVGL_PROPERTY_STRING_CASE(TextAlignment, left);
  LVGL_PROPERTY_STRING_CASE(TextAlignment, right);
  LVGL_PROPERTY_STRING_CASE(TextAlignment, center);
  return TextAlignment::invalid;
}

const char *Utility::to_cstring(BorderSide value) {
  switch (value) {
    LVGL_PROPERTY_CASE(BorderSide, invalid);
    LVGL_PROPERTY_CASE(BorderSide, none);
    LVGL_PROPERTY_CASE(BorderSide, bottom);
    LVGL_PROPERTY_CASE(BorderSide, top);
    LVGL_PROPERTY_CASE(BorderSide, left);
    LVGL_PROPERTY_CASE(BorderSide, right);
    LVGL_PROPERTY_CASE(BorderSide, full);
    LVGL_PROPERTY_CASE(BorderSide, internal);
  }
  return "unknown";
}
BorderSide Utility::border_side_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(BorderSide, none);
  LVGL_PROPERTY_STRING_CASE(BorderSide, bottom);
  LVGL_PROPERTY_STRING_CASE(BorderSide, top);
  LVGL_PROPERTY_STRING_CASE(BorderSide, left);
  LVGL_PROPERTY_STRING_CASE(BorderSide, right);
  LVGL_PROPERTY_STRING_CASE(BorderSide, full);
  LVGL_PROPERTY_STRING_CASE(BorderSide, internal);
  return BorderSide::invalid;
}

const char *Utility::to_cstring(GradientDirection value) {
  switch (value) {
    LVGL_PROPERTY_CASE(GradientDirection, invalid);
    LVGL_PROPERTY_CASE(GradientDirection, none);
    LVGL_PROPERTY_CASE(GradientDirection, horizontal);
    LVGL_PROPERTY_CASE(GradientDirection, vertical);
  }
  return "unknown";
}
GradientDirection
Utility::gradient_direction_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(GradientDirection, none);
  LVGL_PROPERTY_STRING_CASE(GradientDirection, horizontal);
  LVGL_PROPERTY_STRING_CASE(GradientDirection, vertical);
  return GradientDirection::invalid;
}

const char *Utility::to_cstring(BaseDirection value) {
  switch (value) {
    LVGL_PROPERTY_CASE(BaseDirection, invalid);
    LVGL_PROPERTY_CASE(BaseDirection, auto_);
    LVGL_PROPERTY_CASE(BaseDirection, left_to_right);
    LVGL_PROPERTY_CASE(BaseDirection, right_to_left);
    LVGL_PROPERTY_CASE(BaseDirection, neutral);
    LVGL_PROPERTY_CASE(BaseDirection, weak);
  }
  return "unknown";
}
BaseDirection Utility::base_direction_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(BaseDirection, auto_);
  LVGL_PROPERTY_STRING_CASE(BaseDirection, left_to_right);
  LVGL_PROPERTY_STRING_CASE(BaseDirection, right_to_left);
  LVGL_PROPERTY_STRING_CASE(BaseDirection, neutral);
  LVGL_PROPERTY_STRING_CASE(BaseDirection, weak);
  return BaseDirection::invalid;
}

const char *Utility::to_cstring(Direction value) {
  switch (value) {
    LVGL_PROPERTY_CASE(Direction, invalid);
    LVGL_PROPERTY_CASE(Direction, none);
    LVGL_PROPERTY_CASE(Direction, left);
    LVGL_PROPERTY_CASE(Direction, right);
    LVGL_PROPERTY_CASE(Direction, top);
    LVGL_PROPERTY_CASE(Direction, bottom);
    LVGL_PROPERTY_CASE(Direction, horizontal);
    LVGL_PROPERTY_CASE(Direction, vertical);
    LVGL_PROPERTY_CASE(Direction, all);
  }
  return "unknown";
}
Direction Utility::direction_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(Direction, none);
  LVGL_PROPERTY_STRING_CASE(Direction, left);
  LVGL_PROPERTY_STRING_CASE(Direction, right);
  LVGL_PROPERTY_STRING_CASE(Direction, top);
  LVGL_PROPERTY_STRING_CASE(Direction, bottom);
  LVGL_PROPERTY_STRING_CASE(Direction, horizontal);
  LVGL_PROPERTY_STRING_CASE(Direction, vertical);
  LVGL_PROPERTY_STRING_CASE(Direction, all);
  return Direction::invalid;
}

const char *Utility::to_cstring(Alignment value) {
  switch (value) {
    LVGL_PROPERTY_CASE(Alignment, invalid);
    LVGL_PROPERTY_CASE(Alignment, default_);
    LVGL_PROPERTY_CASE(Alignment, top_left);
    LVGL_PROPERTY_CASE(Alignment, top_middle);
    LVGL_PROPERTY_CASE(Alignment, top_right);
    LVGL_PROPERTY_CASE(Alignment, bottom_left);
    LVGL_PROPERTY_CASE(Alignment, bottom_middle);
    LVGL_PROPERTY_CASE(Alignment, bottom_right);
    LVGL_PROPERTY_CASE(Alignment, left_middle);
    LVGL_PROPERTY_CASE(Alignment, right_middle);
    LVGL_PROPERTY_CASE(Alignment, center);
    LVGL_PROPERTY_CASE(Alignment, out_top_left);
    LVGL_PROPERTY_CASE(Alignment, out_top_middle);
    LVGL_PROPERTY_CASE(Alignment, out_top_right);
    LVGL_PROPERTY_CASE(Alignment, out_bottom_left);
    LVGL_PROPERTY_CASE(Alignment, out_bottom_middle);
    LVGL_PROPERTY_CASE(Alignment, out_bottom_right);
    LVGL_PROPERTY_CASE(Alignment, out_left_top);
    LVGL_PROPERTY_CASE(Alignment, out_left_middle);
    LVGL_PROPERTY_CASE(Alignment, out_left_bottom);
    LVGL_PROPERTY_CASE(Alignment, out_right_top);
    LVGL_PROPERTY_CASE(Alignment, out_right_middle);
    LVGL_PROPERTY_CASE(Alignment, out_right_bottom);
  }
  return "unknown";
}
Alignment Utility::alignment_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(Alignment, default_);
  LVGL_PROPERTY_STRING_CASE(Alignment, top_left);
  LVGL_PROPERTY_STRING_CASE(Alignment, top_middle);
  LVGL_PROPERTY_STRING_CASE(Alignment, top_right);
  LVGL_PROPERTY_STRING_CASE(Alignment, bottom_left);
  LVGL_PROPERTY_STRING_CASE(Alignment, bottom_middle);
  LVGL_PROPERTY_STRING_CASE(Alignment, bottom_right);
  LVGL_PROPERTY_STRING_CASE(Alignment, left_middle);
  LVGL_PROPERTY_STRING_CASE(Alignment, right_middle);
  LVGL_PROPERTY_STRING_CASE(Alignment, center);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_top_left);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_top_middle);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_top_right);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_bottom_left);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_bottom_middle);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_bottom_right);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_left_top);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_left_middle);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_left_bottom);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_right_top);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_right_middle);
  LVGL_PROPERTY_STRING_CASE(Alignment, out_right_bottom);
  return Alignment::invalid;
}

const char *Utility::to_cstring(FlexFlow value) {
  switch (value) {
    LVGL_PROPERTY_CASE(FlexFlow, invalid);
    LVGL_PROPERTY_CASE(FlexFlow, row);
    LVGL_PROPERTY_CASE(FlexFlow, column);
    LVGL_PROPERTY_CASE(FlexFlow, row_wrap);
    LVGL_PROPERTY_CASE(FlexFlow, row_reverse);
    LVGL_PROPERTY_CASE(FlexFlow, row_wrap_reverse);
    LVGL_PROPERTY_CASE(FlexFlow, column_wrap);
    LVGL_PROPERTY_CASE(FlexFlow, column_reverse);
    LVGL_PROPERTY_CASE(FlexFlow, column_wrap_reverse);
  }
  return "unknown";
}
FlexFlow Utility::flex_flow_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(FlexFlow, row);
  LVGL_PROPERTY_STRING_CASE(FlexFlow, column);
  LVGL_PROPERTY_STRING_CASE(FlexFlow, row_wrap);
  LVGL_PROPERTY_STRING_CASE(FlexFlow, row_reverse);
  LVGL_PROPERTY_STRING_CASE(FlexFlow, row_wrap_reverse);
  LVGL_PROPERTY_STRING_CASE(FlexFlow, column_wrap);
  LVGL_PROPERTY_STRING_CASE(FlexFlow, column_reverse);
  LVGL_PROPERTY_STRING_CASE(FlexFlow, column_wrap_reverse);
  return FlexFlow::invalid;
}

const char *Utility::to_cstring(FlexAlign value) {
  switch (value) {
    LVGL_PROPERTY_CASE(FlexAlign, invalid);
    LVGL_PROPERTY_CASE(FlexAlign, start);
    LVGL_PROPERTY_CASE(FlexAlign, end);
    LVGL_PROPERTY_CASE(FlexAlign, center);
    LVGL_PROPERTY_CASE(FlexAlign, space_evenly);
    LVGL_PROPERTY_CASE(FlexAlign, space_around);
    LVGL_PROPERTY_CASE(FlexAlign, space_between);
  }
  return "unknown";
}
FlexAlign Utility::flex_align_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(FlexAlign, start);
  LVGL_PROPERTY_STRING_CASE(FlexAlign, end);
  LVGL_PROPERTY_STRING_CASE(FlexAlign, center);
  LVGL_PROPERTY_STRING_CASE(FlexAlign, space_evenly);
  LVGL_PROPERTY_STRING_CASE(FlexAlign, space_around);
  LVGL_PROPERTY_STRING_CASE(FlexAlign, space_between);
  return FlexAlign::invalid;
}

const char *Utility::to_cstring(State value) {
  switch (value) {
    LVGL_PROPERTY_CASE(State, invalid);
    LVGL_PROPERTY_CASE(State, default_);
    LVGL_PROPERTY_CASE(State, checked);
    LVGL_PROPERTY_CASE(State, focused);
    LVGL_PROPERTY_CASE(State, focus_key);
    LVGL_PROPERTY_CASE(State, edited);
    LVGL_PROPERTY_CASE(State, hovered);
    LVGL_PROPERTY_CASE(State, pressed);
    LVGL_PROPERTY_CASE(State, scrolled);
    LVGL_PROPERTY_CASE(State, disabled);
    LVGL_PROPERTY_CASE(State, user1);
    LVGL_PROPERTY_CASE(State, user2);
    LVGL_PROPERTY_CASE(State, user3);
    LVGL_PROPERTY_CASE(State, user4);
    LVGL_PROPERTY_CASE(State, any);
  }
  return "unknown";
}
State Utility::state_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(State, checked);
  LVGL_PROPERTY_STRING_CASE(State, focused);
  LVGL_PROPERTY_STRING_CASE(State, focus_key);
  LVGL_PROPERTY_STRING_CASE(State, edited);
  LVGL_PROPERTY_STRING_CASE(State, hovered);
  LVGL_PROPERTY_STRING_CASE(State, pressed);
  LVGL_PROPERTY_STRING_CASE(State, scrolled);
  LVGL_PROPERTY_STRING_CASE(State, disabled);
  LVGL_PROPERTY_STRING_CASE(State, user1);
  LVGL_PROPERTY_STRING_CASE(State, user2);
  LVGL_PROPERTY_STRING_CASE(State, user3);
  LVGL_PROPERTY_STRING_CASE(State, user4);
  LVGL_PROPERTY_STRING_CASE(State, any);
  return State::default_;
}

const char *Utility::to_cstring(ScrollBarMode value) {
  switch (value) {
    LVGL_PROPERTY_CASE(ScrollBarMode, invalid);
    LVGL_PROPERTY_CASE(ScrollBarMode, off);
    LVGL_PROPERTY_CASE(ScrollBarMode, on);
    LVGL_PROPERTY_CASE(ScrollBarMode, active);
    LVGL_PROPERTY_CASE(ScrollBarMode, auto_);
  }
  return "unknown";
}
ScrollBarMode
Utility::scroll_bar_mode_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(ScrollBarMode, off);
  LVGL_PROPERTY_STRING_CASE(ScrollBarMode, on);
  LVGL_PROPERTY_STRING_CASE(ScrollBarMode, active);
  LVGL_PROPERTY_STRING_CASE(ScrollBarMode, auto_);
  return ScrollBarMode::invalid;
}

const char *Utility::to_cstring(ScrollSnap value) {
  switch (value) {
    LVGL_PROPERTY_CASE(ScrollSnap, invalid);
    LVGL_PROPERTY_CASE(ScrollSnap, off);
    LVGL_PROPERTY_CASE(ScrollSnap, start);
    LVGL_PROPERTY_CASE(ScrollSnap, end);
    LVGL_PROPERTY_CASE(ScrollSnap, center);
  }
  return "unknown";
}
ScrollSnap Utility::scroll_snap_mode_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(ScrollSnap, off);
  LVGL_PROPERTY_STRING_CASE(ScrollSnap, start);
  LVGL_PROPERTY_STRING_CASE(ScrollSnap, end);
  LVGL_PROPERTY_STRING_CASE(ScrollSnap, center);
  return ScrollSnap::invalid;
}

const char *Utility::to_cstring(IsAnimate value) {
  switch (value) {
    LVGL_PROPERTY_CASE(IsAnimate, invalid);
    LVGL_PROPERTY_CASE(IsAnimate, no);
    LVGL_PROPERTY_CASE(IsAnimate, yes);
    LVGL_PROPERTY_CASE(IsAnimate, repeat_infinite);
  }
  return "unknown";
}
IsAnimate Utility::is_animate_mode_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(IsAnimate, no);
  LVGL_PROPERTY_STRING_CASE(IsAnimate, yes);
  LVGL_PROPERTY_STRING_CASE(IsAnimate, repeat_infinite);
  return IsAnimate::invalid;
}

const char *Utility::to_cstring(Part value) {
  switch (value) {
    LVGL_PROPERTY_CASE(Part, main);
    LVGL_PROPERTY_CASE(Part, scrollbar);
    LVGL_PROPERTY_CASE(Part, indicator);
    LVGL_PROPERTY_CASE(Part, knob);
    LVGL_PROPERTY_CASE(Part, selected);
    LVGL_PROPERTY_CASE(Part, items);
    LVGL_PROPERTY_CASE(Part, ticks);
    LVGL_PROPERTY_CASE(Part, cursor);
    LVGL_PROPERTY_CASE(Part, any);
  }
  return "unknown";
}
Part Utility::part_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(Part, scrollbar);
  LVGL_PROPERTY_STRING_CASE(Part, indicator);
  LVGL_PROPERTY_STRING_CASE(Part, knob);
  LVGL_PROPERTY_STRING_CASE(Part, selected);
  LVGL_PROPERTY_STRING_CASE(Part, items);
  LVGL_PROPERTY_STRING_CASE(Part, ticks);
  LVGL_PROPERTY_STRING_CASE(Part, cursor);
  LVGL_PROPERTY_STRING_CASE(Part, any);
  return Part::main;
}

const char *Utility::to_cstring(BlendMode value) {
  switch (value) {
    LVGL_PROPERTY_CASE(BlendMode, invalid);
    LVGL_PROPERTY_CASE(BlendMode, normal);
    LVGL_PROPERTY_CASE(BlendMode, additive);
    LVGL_PROPERTY_CASE(BlendMode, subtractive);
  }
  return "unknown";
}
BlendMode Utility::blend_mode_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(BlendMode, normal);
  LVGL_PROPERTY_STRING_CASE(BlendMode, additive);
  LVGL_PROPERTY_STRING_CASE(BlendMode, subtractive);
  return BlendMode::invalid;
}

const char *Utility::to_cstring(Opacity value) {
  switch (value) {
    LVGL_PROPERTY_CASE(Opacity, invalid);
    LVGL_PROPERTY_CASE(Opacity, transparent);
    LVGL_PROPERTY_CASE(Opacity, x10);
    LVGL_PROPERTY_CASE(Opacity, x20);
    LVGL_PROPERTY_CASE(Opacity, x30);
    LVGL_PROPERTY_CASE(Opacity, x40);
    LVGL_PROPERTY_CASE(Opacity, x50);
    LVGL_PROPERTY_CASE(Opacity, x60);
    LVGL_PROPERTY_CASE(Opacity, x70);
    LVGL_PROPERTY_CASE(Opacity, x80);
    LVGL_PROPERTY_CASE(Opacity, x90);
    LVGL_PROPERTY_CASE(Opacity, opaque);
  }
  return "unknown";
}
Opacity Utility::opacity_from_string(const var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(Opacity, transparent);
  LVGL_PROPERTY_STRING_CASE(Opacity, x0);
  LVGL_PROPERTY_STRING_CASE(Opacity, x10);
  LVGL_PROPERTY_STRING_CASE(Opacity, x20);
  LVGL_PROPERTY_STRING_CASE(Opacity, x30);
  LVGL_PROPERTY_STRING_CASE(Opacity, x40);
  LVGL_PROPERTY_STRING_CASE(Opacity, x50);
  LVGL_PROPERTY_STRING_CASE(Opacity, x60);
  LVGL_PROPERTY_STRING_CASE(Opacity, x70);
  LVGL_PROPERTY_STRING_CASE(Opacity, x80);
  LVGL_PROPERTY_STRING_CASE(Opacity, x90);
  LVGL_PROPERTY_STRING_CASE(Opacity, opaque);
  LVGL_PROPERTY_STRING_CASE(Opacity, cover);
  LVGL_PROPERTY_STRING_CASE(Opacity, x100);
  return Opacity::invalid;
}

const char *Utility::to_cstring(PropertyGroup value) {
  switch (value) {
    LVGL_PROPERTY_CASE(PropertyGroup, invalid);
    LVGL_PROPERTY_CASE(PropertyGroup, alignment);
    LVGL_PROPERTY_CASE(PropertyGroup, animation);
    LVGL_PROPERTY_CASE(PropertyGroup, arc);
    LVGL_PROPERTY_CASE(PropertyGroup, background);
    LVGL_PROPERTY_CASE(PropertyGroup, border);
    LVGL_PROPERTY_CASE(PropertyGroup, image);
    LVGL_PROPERTY_CASE(PropertyGroup, line);
    LVGL_PROPERTY_CASE(PropertyGroup, miscellaneous);
    LVGL_PROPERTY_CASE(PropertyGroup, outline);
    LVGL_PROPERTY_CASE(PropertyGroup, padding);
    LVGL_PROPERTY_CASE(PropertyGroup, shadow);
    LVGL_PROPERTY_CASE(PropertyGroup, size);
    LVGL_PROPERTY_CASE(PropertyGroup, text);
    LVGL_PROPERTY_CASE(PropertyGroup, transform);
  }
  return "unknown";
}

PropertyGroup Utility::property_group_from_string(var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, alignment);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, animation);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, arc);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, background);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, border);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, image);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, line);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, miscellaneous);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, outline);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, padding);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, shadow);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, size);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, text);
  LVGL_PROPERTY_STRING_CASE(PropertyGroup, transform);
  return PropertyGroup::invalid;
}

const char *Utility::to_cstring(lvgl::PropertyType value) {
  switch (value) {
    LVGL_PROPERTY_CASE(PropertyType, invalid);
    LVGL_PROPERTY_CASE(PropertyType, alignment);
    LVGL_PROPERTY_CASE(PropertyType, base_direction);
    LVGL_PROPERTY_CASE(PropertyType, blend_mode);
    LVGL_PROPERTY_CASE(PropertyType, boolean);
    LVGL_PROPERTY_CASE(PropertyType, border_side);
    LVGL_PROPERTY_CASE(PropertyType, color);
    LVGL_PROPERTY_CASE(PropertyType, color_filter_descriptor);
    LVGL_PROPERTY_CASE(PropertyType, coordinate);
    LVGL_PROPERTY_CASE(PropertyType, direction);
    LVGL_PROPERTY_CASE(PropertyType, flex_align);
    LVGL_PROPERTY_CASE(PropertyType, flex_flow);
    LVGL_PROPERTY_CASE(PropertyType, font);
    LVGL_PROPERTY_CASE(PropertyType, gradient_direction);
    LVGL_PROPERTY_CASE(PropertyType, image_source);
    LVGL_PROPERTY_CASE(PropertyType, layout);
    LVGL_PROPERTY_CASE(PropertyType, milliseconds);
    LVGL_PROPERTY_CASE(PropertyType, number);
    LVGL_PROPERTY_CASE(PropertyType, opacity);
    LVGL_PROPERTY_CASE(PropertyType, text_alignment);
    LVGL_PROPERTY_CASE(PropertyType, text_decoration);
    LVGL_PROPERTY_CASE(PropertyType, transition_descriptor);
  }
  return "invalid";
}

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
    return "Invalid";
  case PropertyType::coordinate:
    return "Invalid";
  case PropertyType::direction:
    return "Direction";
  case PropertyType::flex_align:
    return "FlexAlign";
  case PropertyType::flex_flow:
    return "FlexFlow";
  case PropertyType::font:
    return "Invalid";
  case PropertyType::gradient_direction:
    return "GradientDirection";
  case PropertyType::image_source:
    return "Invalid";
  case PropertyType::layout:
    return "Invalid";
  case PropertyType::milliseconds:
    return "Invalid";
  case PropertyType::number:
    return "Invalid";
  case PropertyType::opacity:
    return "Invalid";
  case PropertyType::text_alignment:
    return "TextAlignment";
  case PropertyType::text_decoration:
    return "TextDecoration";
  case PropertyType::transition_descriptor:
    return "Invalid";
  }
  return invalid_property_type_class_name;
}
lvgl::PropertyType Utility::property_type_from_string(var::StringView value) {
  LVGL_PROPERTY_STRING_CASE(PropertyType, invalid);
  LVGL_PROPERTY_STRING_CASE(PropertyType, alignment);
  LVGL_PROPERTY_STRING_CASE(PropertyType, base_direction);
  LVGL_PROPERTY_STRING_CASE(PropertyType, blend_mode);
  LVGL_PROPERTY_STRING_CASE(PropertyType, boolean);
  LVGL_PROPERTY_STRING_CASE(PropertyType, border_side);
  LVGL_PROPERTY_STRING_CASE(PropertyType, color);
  LVGL_PROPERTY_STRING_CASE(PropertyType, color_filter_descriptor);
  LVGL_PROPERTY_STRING_CASE(PropertyType, coordinate);
  LVGL_PROPERTY_STRING_CASE(PropertyType, direction);
  LVGL_PROPERTY_STRING_CASE(PropertyType, flex_align);
  LVGL_PROPERTY_STRING_CASE(PropertyType, flex_flow);
  LVGL_PROPERTY_STRING_CASE(PropertyType, font);
  LVGL_PROPERTY_STRING_CASE(PropertyType, gradient_direction);
  LVGL_PROPERTY_STRING_CASE(PropertyType, image_source);
  LVGL_PROPERTY_STRING_CASE(PropertyType, layout);
  LVGL_PROPERTY_STRING_CASE(PropertyType, milliseconds);
  LVGL_PROPERTY_STRING_CASE(PropertyType, number);
  LVGL_PROPERTY_STRING_CASE(PropertyType, opacity);
  LVGL_PROPERTY_STRING_CASE(PropertyType, text_alignment);
  LVGL_PROPERTY_STRING_CASE(PropertyType, text_decoration);
  LVGL_PROPERTY_STRING_CASE(PropertyType, transition_descriptor);
  return PropertyType::invalid;
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

    return value.to_integer();
  }

  case PropertyType::color:
    return Color::from_hex(
      value.to_string_view().to_unsigned_long(StringView::Base::auto_));
  case PropertyType::boolean:
    return value.to_bool();
  case PropertyType::border_side:
    return s32(Utility::border_side_from_string(value.to_string_view()));
  case PropertyType::direction:
    return s32(Utility::direction_from_string(value.to_string_view()));
  case PropertyType::alignment:
    return s32(Utility::alignment_from_string(value.to_string_view()));
  case PropertyType::base_direction:
    return s32(Utility::base_direction_from_string(value.to_string_view()));
  case PropertyType::blend_mode:
    return s32(Utility::blend_mode_from_string(value.to_string_view()));
  case PropertyType::flex_align:
    return s32(Utility::flex_align_from_string(value.to_string_view()));
  case PropertyType::flex_flow:
    return s32(Utility::flex_flow_from_string(value.to_string_view()));
  case PropertyType::gradient_direction:
    return s32(Utility::gradient_direction_from_string(value.to_string_view()));
  case PropertyType::text_alignment:
    return s32(Utility::text_alignment_from_string(value.to_string_view()));
  case PropertyType::text_decoration:
    return s32(Utility::text_decoration_from_string(value.to_string_view()));
  case PropertyType::invalid:
  case PropertyType::font:
  case PropertyType::layout:
  case PropertyType::color_filter_descriptor:
  case PropertyType::transition_descriptor:
  case PropertyType::image_source:
    break;
  }
  return 0;
}

const char *
Utility::property_value_to_cstring(PropertyValue value, PropertyType type) {
  switch (type) {
  case PropertyType::opacity:
    break;
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
    return to_cstring(BorderSide(value.number()));
  case PropertyType::direction:
    return to_cstring(Direction(value.number()));
  case PropertyType::alignment:
    return to_cstring(Alignment(value.number()));
  case PropertyType::base_direction:
    return to_cstring(BaseDirection(value.number()));
  case PropertyType::blend_mode:
    return to_cstring(BlendMode(value.number()));
  case PropertyType::flex_align:
    return to_cstring(FlexAlign(value.number()));
  case PropertyType::flex_flow:
    return to_cstring(FlexFlow(value.number()));
  case PropertyType::gradient_direction:
    return to_cstring(GradientDirection(value.number()));
  case PropertyType::text_alignment:
    return to_cstring(TextAlignment(value.number()));
  case PropertyType::text_decoration:
    return to_cstring(TextDecoration(value.number()));
  }
  return "invalid";
}
