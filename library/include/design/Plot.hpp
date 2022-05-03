//
// Created by Tyler Gilbert on 4/28/22.
//

#ifndef DESIGN_API_DESIGN_PLOT_HPP
#define DESIGN_API_DESIGN_PLOT_HPP

#include <fs/FileObject.hpp>
#include <lvgl/Chart.hpp>
#include <lvgl/Label.hpp>

#include "macros.hpp"

namespace lvgl {
class Draw;
}

namespace design {

class Plot : public lvgl::ObjectAccess<Plot> {
public:
  struct Data;

  class Legend : public lvgl::ObjectAccess<Legend> {
  public:
    class Series : public lvgl::ObjectAccess<Series> {
    public:
      LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Series);

      Series &set_marker_color(lvgl::Color color);
      Series &set_label(const char *value);
      Series &set_label_as_static(const char *value);

    private:
      struct Names {
        DESIGN_DECLARE_NAME(marker);
        DESIGN_DECLARE_NAME(label);
      };
    };

    LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Legend);
  };

  using FormatLabelCallback =
    void (*)(Data *data, lvgl::Chart::Axis axis, lv_coord_t value, var::View text);


  static constexpr ssize_t get_next_data = -1;
  static constexpr ssize_t get_data_count = -2;

  using GetDataCallback = lv_coord_t (
      *)(Plot * plot, lvgl::Chart::Axis axis, size_t series_number, ssize_t point);

  struct Data : lvgl::UserDataAccess<Data> {
    explicit Data(const char *name) : UserDataBase(name) {}

    API_PMAZ(associated_object, Data, lv_obj_t *, nullptr);
    API_PMAZ(count, Data, size_t, {});
    API_PMAZ(format_label, Data, FormatLabelCallback, nullptr);
    API_PMAZ(get_data, Data, GetDataCallback, nullptr);
    API_PMAZ(offset, Data, size_t, {});

  };

  class WindowSlider : public lvgl::ObjectAccess<WindowSlider> {
  public:
    LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(WindowSlider);

  private:
    friend Plot;
    struct Names {
      DESIGN_DECLARE_NAME(plot_control_window_slider);
    };

    struct OffsetCount {
      size_t offset;
      size_t count;
    };


    WindowSlider& set_value(size_t offset, size_t count, size_t total);
    OffsetCount get_offset_and_count(size_t total) const;

    static void value_changed(lv_event_t *e);
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

  Plot &add_control(const lvgl::Object &object);
  Plot &add_legend(const Legend &legend);
  Plot &set_window(size_t offset, size_t count, size_t total);

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

  template<class Associated> Associated get_associated() const {
    return Associated(data()->associated_object);
  }

  size_t offset() const {
    return data()->offset;
  }

  size_t count() const {
    return data()->count;
  }

  bool is_right_justified() const;
  bool is_left_justified() const;

private:
  struct Names {
    DESIGN_DECLARE_NAME(title);
    DESIGN_DECLARE_NAME(container);
    DESIGN_DECLARE_NAME(main_column);
    DESIGN_DECLARE_NAME(row_for_chart);
    DESIGN_DECLARE_NAME(plot_chart);
    DESIGN_DECLARE_NAME(primary_x_axis_label);
    DESIGN_DECLARE_NAME(secondary_x_axis_label);
    DESIGN_DECLARE_NAME(primary_y_axis_label);
    DESIGN_DECLARE_NAME(secondary_y_axis_label);
    DESIGN_DECLARE_NAME(legend);
  };

  static void handle_draw_part_begin(lv_event_t *e);

  void load_data(size_t point_offset, size_t point_count);
  size_t get_maximum_point_count(size_t offset);

  Data *data() { return user_data<Data>(); }
  const Data *data() const { return user_data<Data>(); }

  static Plot get_plot_from_child_event(lv_event_t *e);
};

} // namespace design

#endif // DESIGN_API_DESIGN_PLOT_HPP
