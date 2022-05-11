//
// Created by Tyler Gilbert on 2/23/22.
//

#include <lvgl/Label.hpp>

#include "design/Grid.hpp"

#include "design/extras/LoadingCircles.hpp"

using namespace lvgl;
using namespace design;

LVGL_OBJECT_ASSERT_SIZE(LoadingCircles);


LoadingCircles::LoadingCircles(const char *name, lv_coord_t height) {
  construct_object(name);

  set_height(height);
  const auto icon_height = height * 9 / 10;
  const auto active_size = Size(icon_height, icon_height);
  const auto inactive_size = Size(icon_height * 2 / 3, icon_height * 2 / 3);
  static const auto active_style
    = Style().set_height(icon_height).set_width(icon_height);

  add(Row(Names::circle_row)
        .center()
        .justify_space_between()
        .fill_height()
        .set_width(icon_height * 4)
        .add(NakedContainer()
               .set_size(active_size)
               .add(Label()
                      .center()
                      .add_style("loading_circle")
                      .add_style("loading_circle_active", State::user1)
                      .set_radius(LV_RADIUS_CIRCLE)
                      .set_size(inactive_size)))
        .add(NakedContainer()
               .set_size(active_size)
               .add(Label()
                      .center()
                      .add_style("loading_circle")
                      .add_style("loading_circle_active", State::user1)
                      .set_radius(LV_RADIUS_CIRCLE)
                      .set_size(inactive_size)))
        .add(NakedContainer()
               .set_size(active_size)
               .add(Label()
                      .center()
                      .add_style("loading_circle")
                      .add_style("loading_circle_active", State::user1)
                      .set_radius(LV_RADIUS_CIRCLE)
                      .set_size(inactive_size)))

  );
}

LoadingCircles &LoadingCircles::update_progress(int value) {
  int offset = value % 3;
  update_size(offset);
  return *this;
}

void LoadingCircles::update_size(int offset) {
  auto row = find<Row>(Names::circle_row);
  for (auto i : api::Index(3)) {
    auto label = row.get_child(i).get_child<Label>(0);
    if (i == offset) {
      label.add_state(State::user1);
    } else {
      label.clear_state(State::user1);
    }
  }
}
