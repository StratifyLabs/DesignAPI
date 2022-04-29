//
// Created by Tyler Gilbert on 4/28/22.
//
#include <lvgl/Draw.hpp>
#include <lvgl/Event.hpp>

#include "design/Grid.hpp"
#include "design/Plot.hpp"
#include "design/Typography.hpp"

using namespace lvgl;
using namespace design;

Legend::Legend(const char *name) {
  construct_object(name);
  add_style("card");
  set_height(size_from_content);
  set_width(size_from_content);
  set_padding(15);
  set_column_padding(15);
  set_row_padding(15);
}

Legend::Series::Series(const char *name) {
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

Legend::Series &Legend::Series::set_marker_color(lvgl::Color color) {
  find<Container>(Names::marker).set_background_color(color);
  return *this;
}

Legend::Series &Legend::Series::set_label_as_static(const char *value) {
  find<Label>(Names::label).set_text_as_static(value);
  return *this;
}

Legend::Series &Legend::Series::set_label(const char *value) {
  find<Label>(Names::label).set_text(value);
  return *this;
}

Plot::Plot(const char *name) {
  construct_object(name);

  add_style(Column::get_style()).add_style("col");
  add(Heading4(Names::title, "Plot Title"));
  add(Row(Names::row_for_chart)
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

  add(Label(Names::primary_x_axis_label)
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

static void draw_event_cb(lv_event_t *e) {
  lv_obj_draw_part_dsc_t *dsc = lv_event_get_draw_part_dsc(e);
  if (!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL))
    return;

  if (dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {
    const char *month[] = {"Jan",  "Febr", "March", "Apr", "May", "Jun",
                           "July", "Aug",  "Sept",  "Oct", "Nov", "Dec"};
    lv_snprintf(dsc->text, dsc->text_length, "%s", month[dsc->value]);
  }
}
