// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_EXTRAS_CHECK_LIST_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_CHECK_LIST_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class CheckList : public lvgl::ObjectAccess<CheckList> {
public:
  class Data : public lvgl::UserDataAccess<Data> {
  public:
    explicit Data(const char *name = "") : UserDataBase(name) {}

    API_PMAZ(checked_symbol, Data, const char *, LV_SYMBOL_OK);

    //these start with `is`
    API_PUBLIC_BOOL(Data, allow_multiple, false);

    API_PMAZ(not_checked_symbol, Data, const char * , "");
  };

  explicit CheckList(const Data &user_data);
  explicit CheckList(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->list_class; }

  CheckList &add_item(const char *name, const char *text);
  CheckList &clear_all();
  CheckList &set_checked(const char *name, bool value = true);
  bool is_checked(const char *name) const;

private:
  struct Names {
    static constexpr auto check_symbol_name = "CheckSymbol";
  };

  void update_border_side();
};

} // namespace design


#endif // DESIGNAPI_DESIGN_EXTRAS_CHECK_LIST_HPP_
