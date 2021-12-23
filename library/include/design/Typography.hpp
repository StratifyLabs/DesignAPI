// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_TYPOGRAPHY_HPP_
#define DESIGNAPI_DESIGN_TYPOGRAPHY_HPP_

#include <api/api.hpp>

#include <json/Json.hpp>
#include <lvgl/ObjectAccess.hpp>

namespace design {

class Heading1 : public lvgl::ObjectAccess<Heading1> {
public:
  Heading1(const char * name, const char * title);
  Heading1(const char * title);
};

class Heading2 : public lvgl::ObjectAccess<Heading2> {
public:
  Heading2(const char * name, const char * title);
  Heading2(const char * title);
};

class Heading3 : public lvgl::ObjectAccess<Heading3> {
public:
  Heading3(const char * name, const char * title);
  Heading3(const char * title);
};

class Heading4 : public lvgl::ObjectAccess<Heading4> {
public:
  Heading4(const char * name, const char * title);
  Heading4(const char * title);
};

class Span : public lvgl::ObjectAccess<Span> {
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Span);
  Span(const char * name, const char * content);

};

class Paragraph : public lvgl::ObjectAccess<Paragraph> {
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Paragraph);
  Paragraph(const char * name, const char * content);

};

}


#endif // DESIGNAPI_DESIGN_TYPOGRAPHY_HPP_
