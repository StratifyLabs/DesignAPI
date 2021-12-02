// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_CHECK_LIST_HPP_
#define DESIGNAPI_DESIGN_CHECK_LIST_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class CheckList : public lvgl::ObjectAccess<CheckList> {
public:
  class Data : public lvgl::UserDataAccess<Data> {
  public:
    explicit Data(const char *name) : UserDataBase(name) {}

  private:
    API_AB(Data, allow_multiple, false);
    API_AF(Data, const char *, checked_symbol, LV_SYMBOL_OK);
    API_AF(Data, const char *, not_checked_symbol, "");
  };

  explicit CheckList(const Data &user_data);
  explicit CheckList(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->list_class; }

  static constexpr auto check_symbol_name = "CheckSymbol";

  CheckList &add_item(const char *name, const char *text) {
    auto object = api()->list_add_btn(m_object, "", text);
    set_user_data(object, name);
    auto button = lvgl::Container(object).get<lvgl::Button>();
    button.add_flag(Flags::event_bubble)
      .add(lvgl::Label(check_symbol_name)
             .set_width(size_from_content)
             .set_alignment(lvgl::Alignment::right_middle)
             .set_text_static(""));
    return *this;
  }

  CheckList &clear_all() {
    for (u32 i = 0; i < get_child_count(); i++) {
      auto label = get_child(i).find<lvgl::Label, lvgl::IsAssertOnFail::no>(
        check_symbol_name);
      if (label.object()) {
        label.set_text_static("");
      }
    }
    return *this;
  }

  CheckList &set_checked(const char *name, bool value = true) {
    auto label = find_within<lvgl::Label, lvgl::IsAssertOnFail::no>(
      name,
      check_symbol_name);
    if (label.is_valid()) {
      auto *c = user_data<Data>();
      label.set_text_static(
        value ? c->checked_symbol() : c->not_checked_symbol());
    }
    return *this;
  }

  bool is_checked(const char *name) const {
    auto label = find_within<lvgl::Label, lvgl::IsAssertOnFail::no>(
      name,
      check_symbol_name);
    if (label.is_valid()) {
      auto *c = user_data<Data>();
      return var::StringView(label.get_text()) == c->checked_symbol();
    }
    return false;
  }
};

} // namespace design

namespace printer {
class Printer;
// Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::CheckList &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_CHECK_LIST_HPP_
