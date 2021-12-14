//
// Created by Tyler Gilbert on 12/4/21.
//

#include "design/Typography.hpp"

using namespace lvgl;
using namespace design;

Heading1::Heading1(const char *name, const char *title) {
  construct_label(name);
  api()->label_set_text_static(m_object, title);
  add_style("h1");
}

Heading1::Heading1(const char *title) {
  construct_label(title);
  api()->label_set_text_static(m_object, title);
  add_style("h1");
}

Heading2::Heading2(const char *name, const char *title) {
  construct_label(name);
  api()->label_set_text_static(m_object, title);
  add_style("h2");
}

Heading2::Heading2(const char *title) {
  construct_label(title);
  api()->label_set_text_static(m_object, title);
  add_style("h2");
}


Heading3::Heading3(const char *name, const char *title) {
  construct_label(name);
  api()->label_set_text_static(m_object, title);
  add_style("h3");
}

Heading3::Heading3(const char *title) {
  construct_label(title);
  api()->label_set_text_static(m_object, title);
  add_style("h3");
}


Heading4::Heading4(const char *name, const char *title) {
  construct_label(name);
  api()->label_set_text_static(m_object, title);
  add_style("h4");
}

Heading4::Heading4(const char *title) {
  construct_label(title);
  api()->label_set_text_static(m_object, title);
  add_style("h4");
}

Paragraph::Paragraph(const char *name) {
  construct_label(name);
  api()->label_set_text_static(m_object, "");
  add_style("paragraph");
}