// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_TYPOGRAPHY_HPP_
#define DESIGNAPI_DESIGN_TYPOGRAPHY_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Header : public lvgl::ObjectAccess<Card> {
public:
  Header();

private:

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Header &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_TYPOGRAPHY_HPP_
