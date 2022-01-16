//
// Created by Tyler Gilbert on 1/15/22.
//

#ifndef DESIGNAPI_DESIGN_EXTRAS_DRAWER_STACK_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_DRAWER_STACK_HPP_

#include <lvgl/ObjectAccess.hpp>

#include "../Drawer.hpp"

#include "../macros.hpp"

namespace design {

class DrawerStack : public lvgl::ObjectAccess<DrawerStack> {
public:

  struct Data : public lvgl::UserDataAccess<Data> {
    Data() : lvgl::UserDataAccess<Data>(Names::drawer_stack_object){}
    Drawer::Data drawer_data = Drawer::Data(Names::drawer_stack_drawer);

  private:
    friend class DrawerStack;
    lv_obj_t * active_drawer = nullptr;
  };

  explicit DrawerStack(Data & data);
  LVGL_OBJECT_ACCESS_CONSTRUCT_FROM_OBJECT(DrawerStack);


  //finds the parent drawer stack
  static DrawerStack find_drawer_stack_parent(lvgl::Object child_object);
  static DrawerStack find_drawer_stack_child(lvgl::Object child_object);

  DrawerStack & add_drawer(lvgl::Object object);
  DrawerStack& add(lvgl::Object object){
    return add_drawer(object);
  }

  DrawerStack & open_drawer(size_t index);
  DrawerStack& open_drawer(Drawer target_drawer);
  DrawerStack & open_drawer_containing(lvgl::Object object);
  DrawerStack & open_drawer_containing(const char * name_of_item_in_drawer);
  DrawerStack & remove_drawer(size_t index);
  DrawerStack & remove_drawer_containing(lvgl::Object object);

  DrawerStack & close_drawer_containing(lvgl::Object object);
  DrawerStack & close_drawer(Drawer target_drawer);

  Drawer find_drawer(const char * name) const;
  static Drawer get_parent_drawer(lvgl::Object object);

private:

  struct Names {
    DESIGN_DECLARE_NAME_VALUE(drawer_stack_object, __drawer_stack_object);
    DESIGN_DECLARE_NAME_VALUE(drawer_stack_drawer, __drawer_stack_drawer);
  };


};

}

#endif // DESIGNAPI_DESIGN_EXTRAS_DRAWER_STACK_HPP_
