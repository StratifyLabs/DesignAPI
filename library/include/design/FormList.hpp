// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_FORM_LIST_HPP_
#define DESIGNAPI_DESIGN_FORM_LIST_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class FormList : public lvgl::ObjectAccess<FormList> {
public:
  class Data : public ::lvgl::UserDataAccess<Data> {
  public:
    explicit Data(const char *name = "") : UserDataBase(name) {}

    API_PUBLIC_BOOL(Data,allow_multiple, false);

    API_PMAZ(checked_symbol, Data, const char *, LV_SYMBOL_OK);
    API_PMAZ(not_checked_symbol, Data, const char *, "");

  };

  explicit FormList(Data &user_data);
  explicit FormList(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->list_class; }

  static constexpr auto value_name = "FormValue";

  enum class ItemType { boolean, string, number, navigation };

  class ItemData : public ::lvgl::UserDataAccess<ItemData> {
  public:
    using Callback = void (*)(lv_event_t *);
    explicit ItemData(const char *name) : UserDataBase(name) {}

    API_PMAZ(clicked_callback, ItemData, Callback, nullptr);
    API_PMAZ(symbol, ItemData, const char *, nullptr);
    API_PMAZ(type, ItemData, ItemType, ItemType::boolean);
    API_PMAZ(value, ItemData, var::KeyString, {});

  };

  FormList &add_item(const ItemData &item_data);
  FormList& update_item_value(const char * item_name, const char * item_value);

};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::FormList &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_FORM_LIST_HPP_
