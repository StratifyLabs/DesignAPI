// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_ICONS_HPP_
#define DESIGNAPI_DESIGN_ICONS_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Icons {


};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Icons &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_ICONS_HPP_
