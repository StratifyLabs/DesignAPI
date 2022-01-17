//
// Created by Tyler Gilbert on 1/15/22.
//

#include "design/extras/DrawerStack.hpp"
#include "design/Drawer.hpp"

using namespace design;

DrawerStack::DrawerStack(Data &data) {
  construct_object(data.cast_as_name());
  set_scroll_direction(lvgl::Direction::vertical);
}

DrawerStack &DrawerStack::add_drawer(lvgl::Object object) {
  auto *data = user_data<Data>();
  ObjectAccess<DrawerStack>::add(
    Drawer(data->drawer_data).fill().add_content(object));
  return *this;
}

Drawer DrawerStack::get_parent_drawer(lvgl::Object object) {
  return object.find_parent<Drawer>(Names::drawer_stack_drawer);
}

DrawerStack &DrawerStack::open_drawer(size_t index) {
  API_ASSERT(index < get_child_count());
  auto target_drawer = get_child<Drawer>(index);
  return open_drawer(target_drawer);
}

DrawerStack &
DrawerStack::open_drawer_containing(const char *name_of_item_in_drawer) {
  // current drawer is parent of object
  auto item_in_drawer = find(name_of_item_in_drawer);
  return open_drawer_containing(item_in_drawer);
}

DrawerStack &DrawerStack::open_drawer_containing(lvgl::Object object) {
  // current drawer is parent of object
  auto target_drawer = get_parent_drawer(object);
  return open_drawer(target_drawer);
}

DrawerStack &DrawerStack::open_drawer_containing(
  const char *name_of_item_in_drawer,
  void * context,
  lvgl::Object (*add_if_not_available)(void*)) {
  auto item_in_drawer
    = find<lvgl::Object, lvgl::IsAssertOnFail::no>(name_of_item_in_drawer);
  if (item_in_drawer.is_valid()) {
    return open_drawer_containing(item_in_drawer);
  }

  // add the drawer then open it
  auto object = add_if_not_available(context);
  return add_drawer(object).open_drawer_containing(object);
}


DrawerStack &DrawerStack::open_drawer(Drawer target_drawer) {
  auto *data = user_data<Data>();
  auto current_drawer = data->active_drawer != nullptr
                          ? Drawer(data->active_drawer)
                          : Drawer(nullptr);

  if (current_drawer.is_valid()) {
    current_drawer.open();
  }

  target_drawer.open_partial();
  data->active_drawer = target_drawer.object();
  return *this;
}

DrawerStack &DrawerStack::close_drawer_containing(lvgl::Object object) {
  return close_drawer(get_parent_drawer(object));
}

DrawerStack &DrawerStack::close_drawer(Drawer current_drawer) {
  current_drawer.close();

  // what is the index of the current drawer
  auto current_index = current_drawer.get_index();
  if (current_index == 0) {
    return *this;
  }

  auto *data = user_data<Data>();
  for (int idx = current_index - 1; idx >= 0; --idx) {
    auto parent_drawer = get_child<Drawer>(idx);
    if (parent_drawer.is_opened()) {
      data->active_drawer = parent_drawer.object();
      parent_drawer.open_partial();
      return *this;
    }
  }

  data->active_drawer = nullptr;
  return *this;
}

DrawerStack DrawerStack::find_drawer_stack_parent(lvgl::Object object) {
  auto result = object.find_parent<DrawerStack>(Names::drawer_stack_object);
  API_ASSERT(result.is_valid());
  return result;
}

DrawerStack DrawerStack::find_drawer_stack_child(lvgl::Object object) {
  return object.find<DrawerStack>(Names::drawer_stack_object);
}

DrawerStack &DrawerStack::remove_drawer(size_t index) {
  API_ASSERT(index < get_child_count());
  get_child(index).remove();
  return *this;
}

DrawerStack &DrawerStack::remove_drawer_containing(lvgl::Object object) {
  get_parent_drawer(object).remove();
  return *this;
}

Drawer DrawerStack::find_drawer(const char *name) const {
  auto item = find<lvgl::Object, lvgl::IsAssertOnFail::no>(name);
  if (item.is_valid()) {
    return get_parent_drawer(item);
  }
  return Drawer(nullptr);
}
