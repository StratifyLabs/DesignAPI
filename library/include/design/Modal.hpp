// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_MODAL_HPP_
#define DESIGNAPI_DESIGN_MODAL_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Modal : public lvgl::ObjectAccess<Modal> {
public:

  static constexpr auto enabled = lvgl::State::user1;

  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Modal);

  Modal & set_enabled(bool value = true);

  Modal & close(chrono::MicroTime delay);

private:
  struct Names {
    static constexpr auto content_container = "ContentContainer";
  };

};

}


#endif // DESIGNAPI_DESIGN_MODAL_HPP_
