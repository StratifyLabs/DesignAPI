//
// Created by Tyler Gilbert on 12/7/21.
//
#include <lvgl/Generic.hpp>
#include <lvgl/Label.hpp>

#include "design/Badge.hpp"

using namespace design;
using namespace lvgl;

Badge::Badge(const char *name) {
  construct_object(name);
  add_style("badge").clear_flag(Flags::scrollable | Flags::clickable);
}