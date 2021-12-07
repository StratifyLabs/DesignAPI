// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_CARD_HPP_
#define DESIGNAPI_DESIGN_CARD_HPP_

#include <api/api.hpp>

#include <lvgl/Label.hpp>

namespace design {

class Card : public lvgl::ObjectAccess<Card> {
public:
  explicit Card(const char *name = "");
  explicit Card(lv_obj_t *object) { m_object = object; }
  explicit Card(Object &object) { m_object = object.object(); }

  class Header : public lvgl::ObjectAccess<Header>{
  public:
    explicit Header(const char * title);
    explicit Header(lv_obj_t *object) { m_object = object; }
    explicit Header(Object &object) { m_object = object.object(); }
  };

  class Body : public lvgl::ObjectAccess<Body>{
  public:
    explicit Body(const char * text);
    explicit Body(lv_obj_t *object) { m_object = object; }
    explicit Body(Object &object) { m_object = object.object(); }
  };

  class Footer : public lvgl::ObjectAccess<Footer>{
  public:
    explicit Footer(const char * title);
    explicit Footer(lv_obj_t *object) { m_object = object; }
    explicit Footer(Object &object) { m_object = object.object(); }
  };

  class Names {
  public:
    static constexpr auto header = "card_header";
    static constexpr auto body = "card_body";
    static constexpr auto footer = "card_footer";
  };

  Card & add_style(const lv_style_t * style){
    return lvgl::ObjectAccess<Card>::add_style(style);
  }

  Card & add_style(const lvgl::Style & style){
    return lvgl::ObjectAccess<Card>::add_style(style);
  }

  Card & add_style(var::StringView value);

  lvgl::Label get_header() const {
    return find<lvgl::Label>(Names::header);
  }

  lvgl::Label get_footer() const {
    return find<lvgl::Label>(Names::header);
  }

  lvgl::Label get_body() const {
    return find<lvgl::Label>(Names::header);
  }

private:

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Card &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_CARD_HPP_
