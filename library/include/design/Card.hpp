// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_CARD_HPP_
#define DESIGNAPI_DESIGN_CARD_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Card : public lvgl::ObjectAccess<Card> {
public:
  explicit Card(const char *name = "");
  explicit Card(lv_obj_t *object) { m_object = object; }
  explicit Card(Object &object) { m_object = object.object(); }

  class Header : public lvgl::ObjectAccess<Header>{
  public:
    Header(const char *name, const char * title);
    explicit Header(const char * title);
    explicit Header(lv_obj_t *object) { m_object = object; }
    explicit Header(Object &object) { m_object = object.object(); }
  };

  class Body : public lvgl::ObjectAccess<Body>{
  public:
    Body(const char *name, const char * text);
    explicit Body(const char * text);
    explicit Body(lv_obj_t *object) { m_object = object; }
    explicit Body(Object &object) { m_object = object.object(); }
  };

  class Footer : public lvgl::ObjectAccess<Footer>{
  public:
    Footer(const char *name, const char * title);
    explicit Footer(const char * title);
    explicit Footer(lv_obj_t *object) { m_object = object; }
    explicit Footer(Object &object) { m_object = object.object(); }
  };

private:

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Card &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_CARD_HPP_
