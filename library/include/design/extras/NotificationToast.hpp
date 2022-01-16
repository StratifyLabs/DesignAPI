// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_EXTRAS_NAVIGATION_TOAST_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_NAVIGATION_TOAST_HPP_

#include <lvgl/ObjectAccess.hpp>
#include <chrono/MicroTime.hpp>

#include "../macros.hpp"

namespace design {

class NotificationToast : public lvgl::ObjectAccess<NotificationToast> {
public:

  NotificationToast(chrono::MicroTime lifetime);
  LVGL_OBJECT_ACCESS_CONSTRUCT_FROM_OBJECT(NotificationToast);

  NotificationToast& set_title_as_static(const char * value);

  NotificationToast& set_title(const char * value);

  NotificationToast& set_message_as_static(const char * value);

  NotificationToast& set_message(const char * value);

private:

  struct Names {
    DESIGN_DECLARE_NAME_VALUE(toast_name, __toast_default_name);
    DESIGN_DECLARE_NAME(title_label);
    DESIGN_DECLARE_NAME(message_label);
    DESIGN_DECLARE_NAME(close_button);
  };

};

}


#endif // DESIGNAPI_DESIGN_EXTRAS_NAVIGATION_TOAST_HPP_
