//
// Created by Tyler Gilbert on 12/2/21.
//

#include <lvgl/CheckBox.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/List.hpp>

#include "design/extras/CheckList.hpp"

using namespace design;
using namespace lvgl;

CheckList::CheckList(const Data &user_data) {
  construct_list(user_data.cast_as_name());
  get<CheckList>().add_event_callback(EventCode::clicked, [](lv_event_t *e) {
    const Event event(e);
    if (event.target().name() == event.current_target().name()) {
      return;
    }

    const char *button_name = event.target().name();
    auto checklist = event.current_target<CheckList>();
    auto *c = checklist.user_data<Data>();
    if (c->is_allow_multiple == false) {
      checklist.clear_all();
      checklist.set_checked(button_name);
    } else {
      // toggle the item that was pressed
      const auto is_checked = checklist.is_checked(button_name);
      checklist.set_checked(button_name, !is_checked);
    }
  });
}

CheckList &CheckList::add_item(const char *name, const char *text) {
  auto object = api()->list_add_btn(m_object, "", text);
  set_user_data(object, name);
  auto button = lvgl::Button(object);

  update_border_side();

  button.add_flag(Flags::event_bubble)
    .set_border_side(BorderSide::none)
    .add(lvgl::Label(Names::check_symbol_name)
           .set_width(size_from_content)
           .set_alignment(lvgl::Alignment::right_middle)
           .set_text_as_static(""));



  return *this;
}

CheckList &CheckList::clear_all() {
  for (u32 i = 0; i < get_child_count(); i++) {
    auto label = get_child(i).find<lvgl::Label, lvgl::IsAssertOnFail::no>(
      Names::check_symbol_name);
    if (label.object()) {
      label.set_text_as_static("");
    }
  }
  return *this;
}

void CheckList::update_border_side(){
  for (u32 i = 0; i < get_child_count(); i++) {
    get_child(i).get<Button>().set_border_side(BorderSide::bottom);
  }
}


CheckList &CheckList::set_checked(const char *name, bool value) {
  auto label = find_within<lvgl::Label, lvgl::IsAssertOnFail::no>(
    name,
    Names::check_symbol_name);
  if (label.is_valid()) {
    auto *c = user_data<Data>();
    label.set_text_as_static(value ? c->checked_symbol : c->not_checked_symbol);
  }
  return *this;
}

bool CheckList::is_checked(const char *name) const {
  auto label = find_within<lvgl::Label, lvgl::IsAssertOnFail::no>(
    name,
    Names::check_symbol_name);
  if (label.is_valid()) {
    auto *c = user_data<Data>();
    return var::StringView(label.get_text()) == c->checked_symbol;
  }
  return false;
}
