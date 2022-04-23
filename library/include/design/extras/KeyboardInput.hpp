//
// Created by Tyler Gilbert on 1/5/22.
//

#ifndef DESIGNAPI_DESIGN_EXTRAS_KEYBOARD_INPUT_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_KEYBOARD_INPUT_HPP_

#include <lvgl/TextArea.hpp>
#include <lvgl/Keyboard.hpp>
#include <lvgl/Event.hpp>


#include "../macros.hpp"

namespace design {

class Form;
class KeyboardInput : public lvgl::ObjectAccess<KeyboardInput> {
public:
  using Mode = lvgl::Keyboard::Mode;

  explicit KeyboardInput(const char *name);
  explicit KeyboardInput(lv_obj_t *object) { m_object = object; }

  const char *get_value() const { return get_text_area().get_text(); }

  lvgl::Label get_input_label() const { return find<lvgl::Label>(Names::input_label); }

  lvgl::TextArea get_text_area() const {
    return find<lvgl::TextArea>(Names::value_text_area);
  }

  lvgl::Keyboard get_keyboard() const { return find<lvgl::Keyboard>(Names::keyboard); }

  KeyboardInput &update_form(Form & form);

private:
  struct Names {
    DESIGN_DECLARE_NAME(value_text_area);
    DESIGN_DECLARE_NAME(keyboard);
    DESIGN_DECLARE_NAME(input_label);
  };
};

}

#endif // DESIGNAPI_DESIGN_EXTRAS_KEYBOARD_INPUT_HPP_
