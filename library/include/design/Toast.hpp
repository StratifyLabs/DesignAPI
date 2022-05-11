// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_TOAST_HPP_
#define DESIGNAPI_DESIGN_TOAST_HPP_

#include <lvgl/ObjectAccess.hpp>
#include <chrono/MicroTime.hpp>

#include "macros.hpp"

namespace design {

class Toast : public lvgl::ObjectAccess<Toast> {
public:

  enum class Position {
    top_left,
    top,
    top_right,
    bottom_left,
    bottom,
    bottom_right,
    left,
    right
  };

  Toast(const char * name, chrono::MicroTime lifetime = 0_milliseconds);
  Toast(chrono::MicroTime lifetime);
  LVGL_OBJECT_ACCESS_CONSTRUCT_FROM_OBJECT(Toast);

private:

  struct Names {
    DESIGN_DECLARE_NAME_VALUE(toast_name, __toast_default_name);
  };

  void construct_toast(const char * name, chrono::MicroTime lifetime);


};

}


#endif // DESIGNAPI_DESIGN_TOAST_HPP_
