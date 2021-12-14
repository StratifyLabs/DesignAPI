// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_MODAL_HPP_
#define DESIGNAPI_DESIGN_MODAL_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Modal : public lvgl::ObjectAccess<Modal> {
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Modal);

private:

};

}


#endif // DESIGNAPI_DESIGN_MODAL_HPP_
