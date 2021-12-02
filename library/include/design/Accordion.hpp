// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_ACCORDION_CARD_HPP_
#define DESIGNAPI_ACCORDION_CARD_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Accordion : public lvgl::ObjectAccess<Accordion> {
public:
  Accordion();

private:

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Accordion &a);
} // namespace printer

#endif // DESIGNAPI_ACCORDION_CARD_HPP_
