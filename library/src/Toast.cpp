//
// Created by Tyler Gilbert on 1/16/22.
//

#include "design/Toast.hpp"

using namespace lvgl;
using namespace design;

Toast::Toast(const char * name, chrono::MicroTime lifetime){
  construct_toast(name, lifetime);
}

Toast::Toast(chrono::MicroTime lifetime){
  construct_toast(Names::toast_name, lifetime);
}

void Toast::construct_toast(const char *name, chrono::MicroTime lifetime) {
  construct_object(name);
  add_style("toast");
  if( lifetime.milliseconds() > 0 ){
    remove_later(lifetime);
  }
}
