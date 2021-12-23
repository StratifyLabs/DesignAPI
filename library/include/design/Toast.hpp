// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_TOAST_HPP_
#define DESIGNAPI_DESIGN_TOAST_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>
#include <lvgl/Screen.hpp>

namespace design {

class Toast : public lvgl::ObjectAccess<Toast> {
public:
  Toast();

private:

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Toast &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_TOAST_HPP_
