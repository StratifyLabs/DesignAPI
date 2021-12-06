//
// Created by Tyler Gilbert on 12/4/21.
//

#include "design/Grid.hpp"

using namespace design;
using namespace lvgl;

NakedContainer::NakedContainer(const char *name) {
  m_object = api()->obj_create(screen_object());
  set_user_data(m_object, name);
  add_style("naked");
}

Container::Container(const char *name) {
  m_object = api()->obj_create(screen_object());
  set_user_data(m_object, name);
  add_style("container");
}

const lvgl::Style &Row::get_style() {
  static const auto style
    = lvgl::Style()
        .set_flex_layout()
        .set_flex_flow(lvgl::FlexFlow::row)
        .set_flex_align(lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::start))
        .set_column_padding(0);
  return style;
}

Row::Row(const char *name) {
  m_object = api()->label_create(screen_object());
  api()->label_set_text_static(m_object, "");
  set_user_data(m_object, name);
  set_flex_layout()
    .set_flex_flow(lvgl::FlexFlow::row)
    .set_flex_align(SetFlexAlign().set_main(lvgl::FlexAlign::start))
    .add_style("row");
}

const lvgl::Style &Column::get_style() {
  static const auto style
    = lvgl::Style()
        .set_flex_layout()
        .set_flex_flow(FlexFlow::column)
        .set_flex_align(SetFlexAlign().set_main(FlexAlign::start))
        .set_row_padding(0);
  return style;
}

Column::Column(const char *name) {
  m_object = api()->label_create(screen_object());
  api()->label_set_text_static(m_object, "");
  set_user_data(m_object, name);

  set_flex_layout()
    .set_flex_flow(FlexFlow::column)
    .set_flex_align(SetFlexAlign().set_main(FlexAlign::start))
    .add_style("col");
}