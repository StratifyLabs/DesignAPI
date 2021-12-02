//
// Created by Tyler Gilbert on 12/2/21.
//

#include <lvgl/Checkbox.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/List.hpp>

#include "design/CheckList.hpp"


using namespace design;
using namespace lvgl;


CheckList::CheckList(const Data &user_data) {
  m_object = api()->list_create(screen_object());
  set_user_data(m_object,user_data.cast_as_name());
  get<CheckList>().add_event_callback(EventCode::clicked, [](lv_event_t *e) {
    const Event event(e);
    if (event.target().name() == event.current_target().name()) {
      return;
    }

    const char *button_name = event.target().name();
    auto checklist = event.current_target<CheckList>();
    auto *c = checklist.user_data<Data>();
    if (c->is_allow_multiple() == false) {
      checklist.clear_all();
      checklist.set_checked(button_name);
    } else {
      // toggle the item that was pressed
      const auto is_checked = checklist.is_checked(button_name);
      checklist.set_checked(button_name, !is_checked);
    }
  });
}