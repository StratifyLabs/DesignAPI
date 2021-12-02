// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_BADGE_HPP_
#define DESIGNAPI_DESIGN_BADGE_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Badge : public lvgl::ObjectAccess<Badge> {
public:
  Badge();

private:

};

class Pill : public lvgl::ObjectAccess<Pill> {
public:
  Pill();

private:

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Badge &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_BADGE_HPP_
