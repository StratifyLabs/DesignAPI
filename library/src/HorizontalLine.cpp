//
// Created by Tyler Gilbert on 12/11/21.
//

#include "design/HorizontalLine.hpp"


using namespace design;
using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(HorizontalLine);

HorizontalLine::HorizontalLine(const char *name){
  construct_object(name);
  add_style("hline");
}

