//
// Created by Tyler Gilbert on 12/13/21.
//

#include <lvgl/Event.hpp>
#include <lvgl/Generic.hpp>

#include "design/Modal.hpp"

using namespace lvgl;
using namespace design;

Modal::Modal(const char *name) {
  construct_object(name);
  add_style("modal");
  add_style("modal_enabled", Selector(enabled));
  add_state(enabled);
}

Modal &Modal::set_enabled(bool value) {
  if (value) {
    add_state(enabled);
  } else {
    clear_state(enabled);
  }
  return *this;
}

Modal &Modal::close(chrono::MicroTime delay) {
  auto child = get_child(0);
  if (child.is_valid()) {
    child.get<lvgl::Generic>().clear_state(enabled);
  }
  clear_state(enabled);
  remove_later(delay);
  return *this;
}

Modal &Modal::add_content(lv_obj_t *object) {
  return add(Generic(object)
               .set_alignment(lvgl::Alignment::top_middle)
               .add_style("modal_content")
               .add_style("modal_content_enabled", Modal::enabled)
               .add_state(Modal::enabled)
               .set_opacity(lvgl::Opacity::transparent));
}
