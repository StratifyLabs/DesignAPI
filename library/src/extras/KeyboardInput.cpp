//
// Created by Tyler Gilbert on 1/5/22.
//

#include "design/extras/KeyboardInput.hpp"
#include "design/Grid.hpp"

#include "design/extras/Form.hpp"

using namespace lvgl;
using namespace design;

LVGL_OBJECT_ASSERT_SIZE(KeyboardInput);


KeyboardInput::KeyboardInput(const char *name) {
  construct_object(name);
  add(Column()
        .fill()
        .add_flag(Flags::event_bubble)
        .add(Label(Names::input_label)
               .set_text_as_static("")
               .add_style("form_hint")
               .fill_width()
               .add_flag(Flags::hidden))
        .add(lvgl::TextArea(Names::value_text_area)
               .fill_width()
               .add_style("form_field")
               .set_one_line_mode()
               .set_padding(0)
               .set_border_width(0))
        .add(lvgl::Keyboard(Names::keyboard)
               .fill_width()
               .set_flex_grow()
               .add_flag(Flags::event_bubble)));

  find<Keyboard>(Names::keyboard).set_text_area(find<TextArea>(Names::value_text_area));
}

KeyboardInput& KeyboardInput::update_form(Form & form) {
  const auto target_name = get_input_label().get_text();
  auto form_entry = form.find(target_name);
  const auto keyboard_value = get_text_area().get_text();
  form.set_value(form_entry, keyboard_value);
  return *this;
}
