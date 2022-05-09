//
// Created by Tyler Gilbert on 1/15/22.
//

#include <lvgl/Event.hpp>
#include <lvgl/Generic.hpp>

#include "design/Drawer.hpp"

using namespace lvgl;
using namespace design;

Drawer::Drawer(Data &data) {
  construct_object(data.cast_as_name());
  add_style("drawer_ease_out")
    .add_style(data.close_style)
    .add_style("drawer_ease_out", lvgl::State::user1)
    .add_style(data.open_style, lvgl::State::user1)
    .add_style("drawer_ease_out", lvgl::State::user2)
    .add_style(data.partial_style, lvgl::State::user2);
}

Drawer &Drawer::add_content(const lvgl::Object & object) {
  add(object.get<lvgl::Generic>());
  return *this;
}

Drawer &Drawer::open() {
  add_state(lvgl::State::user1).clear_state(lvgl::State::user2);
  return notify_content(EventCode::entered);
}

Drawer &Drawer::open_partial() {
  clear_state(lvgl::State::user1).add_state(lvgl::State::user2);
  return notify_content(EventCode::entered);
}

Drawer &Drawer::close() {
  clear_state(lvgl::State::user1).clear_state(lvgl::State::user2);
  printf("close drawer %s\n", get_child(0).name());
  return notify_content(EventCode::exited);
}

Drawer &Drawer::set_open_from_right() {
  auto *data = user_data<Data>();
  data->open_style.set_translate_x(0_percent).set_translate_y(0);
  data->close_style.set_translate_x(105_percent).set_translate_y(0);
  return cycle();
}

Drawer &Drawer::set_open_from_bottom() {
  auto *data = user_data<Data>();
  data->open_style.set_translate_y(0_percent).set_translate_x(0);
  data->close_style.set_translate_y(105_percent).set_translate_x(0);
  return cycle();
}

Drawer &Drawer::set_open_from_left() {
  auto *data = user_data<Data>();
  data->open_style.set_translate_x(0).set_translate_y(0);
  data->close_style.set_translate_x(-1 * update_layout().get_width())
    .set_translate_y(0);
  return cycle();
}

Drawer &Drawer::set_open_from_top() {
  auto *data = user_data<Data>();
  data->open_style.set_translate_y(0).set_translate_x(0);
  data->close_style.set_translate_y(-1 * update_layout().get_height())
    .set_translate_x(0);
  return cycle();
}

bool Drawer::is_opened() const { return has_state(State::user1); }

bool Drawer::is_opened_partial() const { return has_state(State::user2); }

bool Drawer::is_closed() const { return !is_opened() && !is_opened_partial(); }

Drawer &Drawer::cycle() {
  if (is_opened()) {
    close().open();
  } else if (is_opened_partial()) {
    close().open_partial();
  } else {
    open().close();
  }
  return *this;
}

Drawer &Drawer::notify_content(EventCode event_code) {
  auto content = get_child(0);
  if (content.is_valid()) {
    Event::send(content, event_code);
  }
  return *this;
}
