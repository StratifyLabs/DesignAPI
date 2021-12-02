//
// Created by Tyler Gilbert on 12/2/21.
//

#include <lvgl/Checkbox.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/List.hpp>

#include "design/FormList.hpp"


using namespace design;
using namespace lvgl;

FormList::FormList(Data& data) {
  m_object = api()->list_create(screen_object());
  set_user_data(m_object,data.cast_as_name());
}

FormList &FormList::add_item(const ItemData &item_data) {
  auto object = api()->list_add_btn(m_object, item_data.symbol, item_data.name());
  set_user_data(object, item_data.cast_as_name());
  auto button = Container(object).get<Button>();

  button.add_flag(Flags::event_bubble)
    .add_event_callback(
      EventCode::clicked,
      [](lv_event_t *e) {
        const Event event(e);
        auto *c = event.target().user_data<ItemData>();
        auto button = event.target<Button>();
        auto label = button.find<Label>(value_name);
        if (c->type == ItemType::boolean) {
          if (var::StringView(label.get_text()).is_empty()) {
            label.set_text_static(LV_SYMBOL_OK);
          } else {
            label.set_text_static("");
          }
        } else {
          if (c->clicked_callback) {
            c->clicked_callback(e);
          }
          if (c->type != ItemType::navigation) {
            label.set_text_static(c->value);
          }
        }
      })
    .add(Label(value_name)
           .set_width(size_from_content)
           .set_alignment(Alignment::right_middle));

  auto *c = button.user_data<ItemData>();
  button.find<Label>(value_name)
    .set_text_static(
      (c->type == ItemType::navigation) ? LV_SYMBOL_RIGHT : c->value.cstring());
  return *this;
}

FormList& FormList::update_item_value(const char * item_name, const char * item_value){
  auto button = find<Button>(item_name);
  auto *c = button.user_data<ItemData>();
  c->value = item_value;
  button.find<Label>(value_name)
    .set_text_static(c->value.cstring());
  return *this;
}