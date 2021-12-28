// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_BADGE_HPP_
#define DESIGNAPI_DESIGN_BADGE_HPP_

#include <lvgl/Label.hpp>

#include "macros.h"

namespace design {

class Badge : public lvgl::ObjectAccess<Badge> {
public:
  explicit Badge(const char *name = "");
  explicit Badge(lv_obj_t *object) { m_object = object; }
  explicit Badge(Object &object) { m_object = object.object(); }

  Badge & add_label_as_static(const char * text){
    return add(lvgl::Label(Names::label).set_text_as_static(text).center());
  }

  Badge & add_label(const char * text){
    return add(lvgl::Label(Names::label).set_text(text).center());
  }

  Badge & set_text_as_static(const char * text){
    find<lvgl::Label>(Names::label).set_text_as_static(text);
  }

  Badge & set_text(const char * text){
    find<lvgl::Label>(Names::label).set_text(text);
  }

private:

  struct Names {
    DESIGN_DECLARE_NAME(label);
  };

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Badge &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_BADGE_HPP_
