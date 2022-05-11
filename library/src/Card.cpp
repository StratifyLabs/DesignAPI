// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <printer/Printer.hpp>

#include <lvgl/Generic.hpp>
#include <lvgl/Label.hpp>

#include "design/Card.hpp"

printer::Printer &printer::operator<<(Printer &printer, const design::Card &a) {
  return printer;
}

using namespace design;
using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Card);

Card::Card(const char *name) {
  construct_object(name);
  ObjectAccess<Card>::add_style("card");
  set_width(size_from_content);
}

Card & Card::add_style(var::StringView value){
  ObjectAccess<Card>::add_style(value | "_card");

  static constexpr auto name_list = { Names::header, Names::footer, Names::body };

  for(const auto name : name_list){
    auto generic = find<lvgl::Generic, IsAssertOnFail::no>(name);
    if( generic.is_valid() ){
      generic.add_style(value | "_" | name);
    }
  }

  return *this;
}

Card::Header::Header(const char *title) {
  m_object = api()->label_create(screen_object());
  Label(m_object).set_text_as_static(title);
  set_user_data(m_object, Names::header);

  add_style("card_header");
}

Card::Footer::Footer(const char * title){
  m_object = api()->label_create(screen_object());
  Label(m_object).set_text_as_static(title);
  set_user_data(m_object, Names::footer);

  fill_width()
    .set_height(size_from_content);
  add_style("card_footer");
}


Card::Body::Body(const char * text){
  m_object = api()->label_create(screen_object());
  api()->label_set_text_static(m_object, text);
  set_user_data(m_object, Names::body);

  add_style("card_body");
}


