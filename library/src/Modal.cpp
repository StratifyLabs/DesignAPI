//
// Created by Tyler Gilbert on 12/13/21.
//

#include "design/Modal.hpp"

using namespace lvgl;
using namespace design;


Modal::Modal(const char * name){
  construct_object(name);
  add_style("modal");
  add_style("modal_enabled", Selector(State::user1));
  add_state(State::user1);
}
