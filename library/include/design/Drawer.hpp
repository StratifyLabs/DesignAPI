//
// Created by Tyler Gilbert on 1/15/22.
//

#ifndef RUSHROBOTS_DRAWER_HPP
#define RUSHROBOTS_DRAWER_HPP

#include <lvgl/ObjectAccess.hpp>
#include <lvgl/Event.hpp>

namespace design {

class Drawer : public lvgl::ObjectAccess<Drawer> {
public:

  struct Data : lvgl::UserDataAccess<Data> {
    Data(const char * name = "") : lvgl::UserDataAccess<Data>(name){}
    API_PMAZ(close_style, Data, lvgl::Style, {});
    API_PMAZ(partial_style, Data, lvgl::Style, {});
    API_PMAZ(open_style, Data, lvgl::Style, {});

  private:

  };

  explicit Drawer(Data & data);
  LVGL_OBJECT_ACCESS_CONSTRUCT_FROM_OBJECT(Drawer);
  LVGL_OBJECT_ACCESS_GET_CLASS(obj_class);

  //drawer can be horizontal or vertical
  Drawer &add_content(lvgl::Object object);

  Drawer & set_open_from_right();
  Drawer & set_open_from_top();
  Drawer & set_open_from_bottom();
  Drawer & set_open_from_left();

  Drawer & open();
  Drawer & open_partial();
  Drawer & close();

  bool is_opened() const;
  bool is_opened_partial() const;
  bool is_closed() const;

private:
  Drawer & cycle();

  Drawer & notify_content(lvgl::EventCode event_code);
};

} // namespace design
#endif // RUSHROBOTS_DRAWER_HPP
