//
// Created by Tyler Gilbert on 12/7/21.
//
#include <lvgl/Generic.hpp>
#include <lvgl/Label.hpp>

#include "design/Alert.hpp"


using namespace design;
using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Alert);

Alert::Alert(const char *name) {
  construct_object(name);
  set_width(size_from_content).add_style("alert");
}
