//
// Created by Tyler Gilbert on 4/28/22.
//

#ifndef DESIGN_API_DESIGN_PLOT_HPP
#define DESIGN_API_DESIGN_PLOT_HPP

#include <lvgl/Chart.hpp>
#include <lvgl/Label.hpp>

#include "macros.hpp"

namespace lvgl {
class Draw;
}

namespace design {


class Legend : public lvgl::ObjectAccess<Legend> {
public:

  class Series : public lvgl::ObjectAccess<Series> {
  public:
    LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Series);

    Series & set_marker_color(lvgl::Color color);
    Series & set_label(const char * value);
    Series & set_label_as_static(const char * value);

  private:
    struct Names {
      DESIGN_DECLARE_NAME(marker);
      DESIGN_DECLARE_NAME(label);
    };
  };


  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Legend);
};

class Plot : public lvgl::ObjectAccess<Plot> {
public:
  struct Data;
  using FormatLabelCallback = void (*)(Data * data, lvgl::Chart::Axis axis, lv_coord_t value, var::View text);

  struct Data : lvgl::UserDataAccess<Data> {
    Data(const char *name) : UserDataBase(name) {}

    API_PMAZ(format_label, Data, FormatLabelCallback, nullptr);
  };

  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Plot);

  Plot &set_title(const char *title);
  Plot &set_title_as_static(const char *title);
  Plot &set_primary_x_axis_label(const char *value);
  Plot &set_primary_y_axis_label(const char *value);
  Plot &set_secondary_x_axis_label(const char *value);
  Plot &set_secondary_y_axis_label(const char *value);

  Plot &set_label_margin_percentage(
    lv_coord_t value,
    lvgl::Alignment alignement = lvgl::Alignment::center);
  Plot &set_horizontal_label_margin_percentage(lv_coord_t value);
  Plot &set_vertical_label_margin_percentage(lv_coord_t value);

  lvgl::Label get_title() const { return find<lvgl::Label>(Names::title); }

  lvgl::Label get_primary_x_axis_label() const {
    return find<lvgl::Label>(Names::primary_x_axis_label);
  }

  lvgl::Label get_secondary_x_axis_label() const {
    return find<lvgl::Label>(Names::secondary_x_axis_label);
  }

  lvgl::Label get_primary_y_axis_label() const {
    return find<lvgl::Label>(Names::primary_y_axis_label);
  }

  lvgl::Label get_secondary_y_axis_label() const {
    return find<lvgl::Label>(Names::secondary_y_axis_label);
  }

  lvgl::Chart get_chart() const { return find<lvgl::Chart>(Names::plot_chart); }

private:
  struct Names {
    DESIGN_DECLARE_NAME(title);
    DESIGN_DECLARE_NAME(container);
    DESIGN_DECLARE_NAME(row_for_chart);
    DESIGN_DECLARE_NAME(plot_chart);
    DESIGN_DECLARE_NAME(primary_x_axis_label);
    DESIGN_DECLARE_NAME(secondary_x_axis_label);
    DESIGN_DECLARE_NAME(primary_y_axis_label);
    DESIGN_DECLARE_NAME(secondary_y_axis_label);
    DESIGN_DECLARE_NAME(legend);
  };

  static void handle_draw_part_begin(lv_event_t *e);

  Data *data() { return user_data<Data>(); }
  const Data *data() const { return user_data<Data>(); }
};

} // namespace design

#endif // DESIGN_API_DESIGN_PLOT_HPP
