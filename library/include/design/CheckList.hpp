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

  CheckList &add_item(const char *name, const char *text);

  CheckList &clear_all();

  CheckList &set_checked(const char *name, bool value = true);

  bool is_checked(const char *name) const;
};

} // namespace design

namespace printer {
class Printer;
// Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::CheckList &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_CHECK_LIST_HPP_
