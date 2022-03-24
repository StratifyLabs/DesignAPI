//
// Created by Tyler Gilbert on 1/5/22.
//

#include "design/extras/KeyboardInput.hpp"
#include "design/Grid.hpp"

using namespace lvgl;
using namespace design;

KeyboardInput::KeyboardInput(Data &data) {
  construct_object(data.cast_as_name());
  add(Column()
        .fill()
        .add_flag(Flags::event_bubble)
        .add(lvgl::TextArea(Names::value_text_area)
               .fill_width()
               .set_one_line_mode()
               .set_padding(0)
               .set_border_width(0))
        .add(lvgl::Keyboard(Names::keyboard)
               .fill_width()
               .set_mode(data.mode)
               .set_flex_grow()
               .add_flag(Flags::event_bubble)));

  find<Keyboard>(Names::keyboard).set_text_area(find<TextArea>(Names::value_text_area));
}