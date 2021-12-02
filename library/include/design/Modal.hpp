// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_MODAL_HPP_
#define DESIGNAPI_DESIGN_MODAL_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Modal : public lvgl::ObjectAccess<Modal> {
public:
  Modal();

private:

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Modal &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_MODAL_HPP_
