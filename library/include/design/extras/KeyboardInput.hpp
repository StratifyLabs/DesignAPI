//
// Created by Tyler Gilbert on 1/5/22.
//

#ifndef DESIGNAPI_DESIGN_EXTRAS_KEYBOARD_INPUT_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_KEYBOARD_INPUT_HPP_

#include <lvgl/TextArea.hpp>
#include <lvgl/Keyboard.hpp>
#include <lvgl/Event.hpp>

#include "../macros.hpp"

class KeyboardInput : public lvgl::ObjectAccess<KeyboardInput> {
public:

  using Mode = lvgl::Keyboard::Mode;


  struct Data : public lvgl::UserDataAccess<Data>{

    Data(const char * name) : lvgl::UserDataAccess<Data>(name){}

    API_PMAZ(mode, Data, Mode, lvgl::Keyboard::Mode::text_lower);
    API_PMAZ(notify_callback, Data, lvgl::Event::Callback, nullptr);

    API_PMAZ(target, Data, lv_obj_t *, nullptr);


  };


  KeyboardInput(Data & data);
  KeyboardInput(lv_obj_t * object){ m_object = object; }

  const char * get_value() const {
    return get_text_area().get_text();
  }

  lvgl::TextArea get_text_area() const {
    return find<lvgl::TextArea>(Names::value_text_area);
  }

  lvgl::Keyboard get_keyboard() const {
    return find<lvgl::Keyboard>(Names::keyboard);
  }

private:
  struct Names {
    DESIGN_DECLARE_NAME(value_text_area);
    DESIGN_DECLARE_NAME(keyboard);
  };


};

#endif // DESIGNAPI_DESIGN_EXTRAS_KEYBOARD_INPUT_HPP_
