// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_HORIZONTAL_LINE_HPP_
#define DESIGNAPI_DESIGN_HORIZONTAL_LINE_HPP_

#include <api/api.hpp>
#include <lvgl/Label.hpp>

namespace design {

class HorizontalLine : public lvgl::ObjectAccess<HorizontalLine> {
public:
  explicit HorizontalLine(const char *name = "");
  explicit HorizontalLine(lv_obj_t *object) { m_object = object; }
  explicit HorizontalLine(Object &object) { m_object = object.object(); }

private:
};

} // namespace design

#endif // DESIGNAPI_DESIGN_HORIZONTAL_LINE_HPP_
