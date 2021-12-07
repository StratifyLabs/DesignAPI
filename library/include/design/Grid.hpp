// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_GRID_HPP_
#define DESIGNAPI_DESIGN_GRID_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class NakedContainer : public lvgl::ObjectAccess<NakedContainer> {
public:
  explicit NakedContainer(const char *name = "");
  explicit NakedContainer(lv_obj_t *object) { m_object = object; }
};

class Container : public lvgl::ObjectAccess<Container> {
public:
  explicit Container(const char *name = "");
  explicit Container(lv_obj_t *object) { m_object = object; }
  explicit Container(Object &object) { m_object = object.object(); }
};


class Row : public lvgl::ObjectAccess<Row> {
public:
  static const lvgl::Style &get_style();

  explicit Row(const char *name = "");
  explicit Row(lv_obj_t *object) { m_object = object; }

  Row &justify_space_between() {
    return set_flex_align(
      lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::space_between));
  }

  Row &justify_space_around() {
    return set_flex_align(
      lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::space_around));
  }

  Row &justify_space_evenly() {
    return set_flex_align(
      lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::space_evenly));
  }

  Row &justify_start() {
    return set_flex_align(
      lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::start));
  }

  Row &justify_end() {
    return set_flex_align(lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::end));
  }
};

class Column : public lvgl::ObjectAccess<Column> {
public:
  static const lvgl::Style &get_style();

  explicit Column(const char *name = "");
  explicit Column(lv_obj_t *object) { m_object = object; }

  Column &justify_space_between() {
    return set_flex_align(
      lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::space_between));
  }

  Column &justify_space_around() {
    return set_flex_align(
      lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::space_around));
  }

  Column &justify_space_evenly() {
    return set_flex_align(
      lvgl::SetFlexAlign().set_main(lvgl::FlexAlign::space_evenly));
  }
};

} // namespace design

namespace printer {
class Printer;
// Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Column &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_GRID_HPP_
