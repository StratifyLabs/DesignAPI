//
// Created by Tyler Gilbert on 4/28/22.
//
#include <lvgl/Draw.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/Generic.hpp>
#include <lvgl/Slider.hpp>

#include "design/Grid.hpp"
#include "design/Plot.hpp"
#include "design/Typography.hpp"

using namespace lvgl;
using namespace design;
using namespace var;

Plot::Legend::Legend(const char *name) {
  construct_object(name);
  add_style("card");
  set_height(size_from_content);
  set_width(size_from_content);
  set_padding(15);
  set_column_padding(15);
  set_row_padding(15);
}

Plot::Legend::Series::Series(const char *name) {
  construct_object(name);
  add_style(Row::get_style());
  set_height(size_from_content);
  set_width(size_from_content);
  add(Container(Names::marker)
        .add_style("plot_legend_marker")
        .set_background_color(Color::blue())
        .set_width(10)
        .set_height(10)
        .set_right_padding(15)
        .set_radius(LV_RADIUS_CIRCLE));

  add(Label(Names::label).add_style("plot_legend_label").set_text_as_static(""));
}

Plot::Legend::Series &Plot::Legend::Series::set_marker_color(lvgl::Color color) {
  find<Container>(Names::marker).set_background_color(color);
  return *this;
}

Plot::Legend::Series &Plot::Legend::Series::set_label_as_static(const char *value) {
  find<Label>(Names::label).set_text_as_static(value);
  return *this;
}

Plot::Legend::Series &Plot::Legend::Series::set_label(const char *value) {
  find<Label>(Names::label).set_text(value);
  return *this;
}

Plot::Plot(const char *name) {
  construct_object(name);
  add(Column(Names::main_column).fill());
  auto column = find<Column>(Names::main_column);
  column.add(Heading4(Names::title, "Plot Title"));
  column.add(Row(Names::row_for_chart)
               .fill_width()
               .set_flex_grow()
               .add(Label(Names::primary_y_axis_label)
                      .set_text_as_static("Y")
                      .set_width(0)
                      .add_flag(Flags::hidden))
               .add(NakedContainer(Names::container)
                      .set_flex_grow()
                      .fill_height()
                      .add(Chart(Names::plot_chart)
                             .set_width(95_percent)
                             .set_height(80_percent)
                             .center()
                             .set_clip_corner(false)
                             .add_event_callback(
                               EventCode::draw_part_begin, handle_draw_part_begin))));

  column.add(Label(Names::primary_x_axis_label)
               .set_text_as_static("X")
               .add_style("plot_label")
               .add_flag(Flags::hidden)
               .set_height(0));
}

Plot &Plot::set_title(const char *title) {
  get_title().set_text(title);
  return *this;
}

Plot &Plot::set_title_as_static(const char *title) {
  get_title().set_text_as_static(title);
  return *this;
}

Plot &Plot::set_label_margin_percentage(lv_coord_t value, Alignment alignment) {
  get_chart().set_alignment(alignment);
  return set_horizontal_label_margin_percentage(value)
    .set_vertical_label_margin_percentage(value);
}

Plot &Plot::set_horizontal_label_margin_percentage(lv_coord_t value) {
  get_chart().set_width(lvgl::Percent(100 - value).value());
  return *this;
}

Plot &Plot::set_vertical_label_margin_percentage(lv_coord_t value) {
  get_chart().set_height(lvgl::Percent(100 - value).value());
  return *this;
}

Plot &Plot::set_primary_x_axis_label(const char *value) {
  get_primary_x_axis_label()
    .set_text(value)
    .clear_flag(Flags::hidden)
    .set_height(size_from_content);
  return *this;
}

Plot &Plot::set_primary_y_axis_label(const char *value) {
  get_primary_y_axis_label()
    .set_text(value)
    .clear_flag(Flags::hidden)
    .set_width(size_from_content);
  return *this;
}

Plot &Plot::set_secondary_x_axis_label(const char *value) {
  get_primary_y_axis_label()
    .set_text(value)
    .clear_flag(Flags::hidden)
    .set_height(size_from_content);
  return *this;
}

Plot &Plot::set_secondary_y_axis_label(const char *value) {
  get_secondary_y_axis_label()
    .set_text(value)
    .clear_flag(Flags::hidden)
    .set_width(size_from_content);
  return *this;
}

Plot &Plot::add_control(const Object &object) {
  find<Column>(Names::main_column).add(lvgl::Generic(object.object()));
  return *this;
}

Plot &Plot::add_legend_below(const Legend &legend) {
  find<Column>(Names::main_column).add(Legend(legend.object()));
  return *this;
}

Plot &Plot::add_legend_right(const Plot::Legend &legend) {
  find<Row>(Names::row_for_chart).add(Legend(legend.object()));
  return *this;
}


void Plot::handle_draw_part_begin(lv_event_t *e) {
  auto event = Event(e);
  auto chart = event.target<Chart>();
  auto plot = chart.find_parent<Object>(Names::row_for_chart).get_parent<Plot>();

  auto *data = plot.user_data<Data>();
  if (!data) {
    return;
  }

  if (chart.object() == event.current_target().object()) {
    const auto draw_descriptor = Draw(event.parameter<lv_obj_draw_part_dsc_t *>());
    if (
      draw_descriptor.id() == u16(Chart::Axis::primary_x)
      || draw_descriptor.id() == u16(Chart::Axis::primary_y)
      || draw_descriptor.id() == u16(Chart::Axis::secondary_x)
      || draw_descriptor.id() == u16(Chart::Axis::secondary_y)) {
      // update x labels
      if (data->format_label) {
        data->format_label(
          data, Chart::Axis(draw_descriptor.id()), draw_descriptor.value(),
          draw_descriptor.text_view());
      }
    }
  }
}
Plot Plot::get_plot_from_child_event(lv_event_t *e) {
  return Event(e).target().find_parent<Object>(Names::main_column).get_parent<Plot>();
}

size_t Plot::get_maximum_point_count(size_t offset) {
  size_t result = SIZE_T_MAX;
  size_t series_index = 0;

  auto update_result = [&](Chart::Axis axis) {
    if (const auto count = data()->get_data(this, axis, series_index, get_data_count);
        count < result) {
      result = count;
    }
  };

  auto series = get_chart().get_series();
  while (series.is_valid()) {
    update_result(Chart::Axis::primary_x);
    update_result(Chart::Axis::primary_y);
    update_result(Chart::Axis::secondary_x);
    update_result(Chart::Axis::secondary_y);
    ++series_index;
    series = series.get_next_series();
  }

  if (result > offset) {
    return result - offset;
  }
  return 0;
}

Plot &Plot::set_window(size_t offset, size_t count, size_t total) {
  load_data(offset, count);
  // synchronize the window slider with these values
  auto slider =
    find<Slider, IsAssertOnFail::no>(WindowSlider::Names::plot_control_window_slider);

  if (slider.is_valid()) {
    slider.get_parent<WindowSlider>().set_value(data()->offset, data()->count, total);
  }

  return *this;
}

void Plot::load_data(size_t point_offset, size_t point_count) {

  auto chart = get_chart();
  const auto effective_point_count = [&]() {
    const auto maximum_point_count = get_maximum_point_count(point_offset);
    return point_count > maximum_point_count ? maximum_point_count : point_count;
  }();

  chart.set_point_count(effective_point_count);

  data()->offset = point_offset;
  data()->count = effective_point_count;

  auto primary_x = Range().set_maximum(-INT16_MAX).set_minimum(INT16_MAX);
  auto primary_y = primary_x;
  auto secondary_x = primary_x;
  auto secondary_y = primary_x;

  const auto is_scatter = chart.get_type() == Chart::Type::scatter;

  auto series = chart.get_series();
  size_t series_index = 0;
  while (series.is_valid()) {
    for (auto i : api::Index(effective_point_count)) {
      const auto point_index = i ? get_next_data : point_offset;
      const auto x_value = [&]() {
        if (is_scatter) {
          const auto x_axis = series.is_x_axis_secondary() ? Chart::Axis::secondary_x
                                                           : Chart::Axis::primary_x;

          return data()->get_data(this, x_axis, series_index, point_index);
        }
        return lv_coord_t{};
      }();

      if (series.is_x_axis_secondary()) {
        secondary_x.expand_to_include(x_value);
      } else {
        primary_x.expand_to_include(x_value);
      }

      const auto y_axis =
        series.is_y_axis_secondary() ? Chart::Axis::secondary_y : Chart::Axis::primary_y;

      auto y_value = data()->get_data(this, y_axis, series_index, point_index);

      if (series.is_y_axis_secondary()) {
        secondary_y.expand_to_include(y_value);
      } else {
        primary_y.expand_to_include(y_value);
      }

      if (is_scatter) {
        series.set_value_by_id(i, Point{x_value, y_value});

      } else {
        series.set_value_by_id(i, y_value);
      }
    }
    series = series.get_next_series();
    ++series_index;
  }

  if (effective_point_count > 0) {
    if (is_scatter) {
      chart.set_range(Chart::Axis::primary_x, primary_x)
        .set_range(Chart::Axis::secondary_x, secondary_x);
    }

    if( data()->is_auto_range_primary_y ) {
      chart.set_range(Chart::Axis::primary_y, primary_y);
    }
    if( data()->is_auto_range_secondary_y ) {
      chart.set_range(Chart::Axis::secondary_y, secondary_y);
    }
  }
}

bool Plot::is_right_justified() const {
  auto slider =
    find<Slider, IsAssertOnFail::no>(WindowSlider::Names::plot_control_window_slider);
  if (slider.is_valid()) {
    return slider.get_value() == slider.get_range().maximum();
  }
  return false;
}

bool Plot::is_left_justified() const {
  auto slider =
    find<Slider, IsAssertOnFail::no>(WindowSlider::Names::plot_control_window_slider);
  if (slider.is_valid()) {
    return slider.get_left_value() == 0;
  }
  return false;
}

Plot &Plot::update_point_count(size_t total) {
  if( is_right_justified() && is_left_justified() ){
    set_window(0, count() + 1, total);
  } else if( is_right_justified() ){
    set_window(offset() + 1, count(), total);
  }
  return *this;
}

Plot::WindowSlider::WindowSlider(const char *name) {
  construct_object(name);
  set_background_opacity(Opacity::transparent);
  add(Slider(Names::plot_control_window_slider)
        .center()
        .set_mode(Slider::Mode::range)
        .set_range(Range())
        .set_left_value(0)
        .set_value(100)
        .set_width(90_percent)
        .add_event_callback(EventCode::value_changed, value_changed));
}

void Plot::WindowSlider::value_changed(lv_event_t *e) {
  // all slider events
  auto plot = get_plot_from_child_event(e);
  if (plot.data()->get_data) {
    auto slider = Event(e).target<Slider>();
    const auto total_count = plot.get_maximum_point_count(0);
    const auto left_value = slider.get_left_value();
    const auto right_value = slider.get_value();
    const auto offset = left_value * total_count / slider.get_range().maximum();
    const auto count = right_value * total_count / slider.get_range().maximum() - offset;
    plot.load_data(offset, count);
  }
}

Plot::WindowSlider &
Plot::WindowSlider::set_value(size_t offset, size_t count, size_t total) {
  auto slider = find<Slider>(Names::plot_control_window_slider);
  const auto range_maximum = slider.get_range().maximum();
  const auto left_value = offset * range_maximum / total;
  const auto right_value = left_value + count * range_maximum / total;
  const auto effective_right_value =
    offset + count == total ? range_maximum : right_value;

  slider.set_value(effective_right_value).set_left_value(left_value);
  return *this;
}

Plot::WindowSlider::OffsetCount
Plot::WindowSlider::get_offset_and_count(size_t total) const {
  auto slider = find<Slider>(Names::plot_control_window_slider);
  const auto left_value = slider.get_left_value();
  const auto right_value = slider.get_value();
  const auto offset_value = left_value * total / slider.get_range().maximum();
  return {
    .offset = offset_value,
    .count = right_value * total / slider.get_range().maximum() - offset_value};
}
