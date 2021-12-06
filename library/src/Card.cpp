// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <printer/Printer.hpp>

#include <lvgl/Label.hpp>

#include "design/Card.hpp"

printer::Printer &printer::operator<<(Printer &printer, const design::Card &a) {
  return printer;
}

using namespace design;
using namespace lvgl;

Card::Card(const char *name) {
  m_object = api()->obj_create(screen_object());
  set_user_data(m_object, name);
  add_style("card");
  set_width(size_from_content);
}

Card::Header::Header(const char *name, const char *title) {
  m_object = api()->label_create(screen_object());
  Label(m_object).set_text_static(name);
  set_user_data(m_object, title);

  add_style("card_header");
}

Card::Header::Header(const char *title) {
  m_object = api()->label_create(screen_object());
  Label(m_object).set_text_static(title);
  set_user_data(m_object, title);

  add_style("card_header");
}

Card::Footer::Footer(const char *name, const char * title){
  m_object = api()->label_create(screen_object());
  Label(m_object).set_text_static(title);
  set_user_data(m_object, name);

  add_style("card_footer");
}

Card::Footer::Footer(const char * title){
  m_object = api()->label_create(screen_object());
  Label(m_object).set_text_static(title);
  set_user_data(m_object, "");

  fill_width()
    .set_height(size_from_content);
  add_style("card_footer");
}

Card::Body::Body(const char *name, const char * text){
  m_object = api()->label_create(screen_object());
  api()->label_set_text_static(m_object, text);
  set_user_data(m_object, name);

  add_style("card_body");
}

Card::Body::Body(const char * text){
  m_object = api()->label_create(screen_object());
  api()->label_set_text_static(m_object, text);
  set_user_data(m_object, "");

  add_style("card_body");
}


