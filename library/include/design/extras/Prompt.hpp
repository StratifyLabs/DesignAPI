//
// Created by Tyler Gilbert on 12/29/21.
//

#ifndef DESIGNAPI_DESIGN_EXTRAS_PROMPT_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_PROMPT_HPP_

#include <lvgl/Event.hpp>
#include <lvgl/Label.hpp>

#include "../macros.hpp"
#include "../Grid.hpp"

namespace design {

class Prompt : public lvgl::ObjectAccess<Prompt> {
public:
  struct Data : public lvgl::UserDataAccess<Data> {
    Data(const char *name = "") : lvgl::UserDataAccess<Data>(name) {}

    API_PMAZ(accept, Data, const char *, LV_SYMBOL_OK);
    API_PMAZ(accept_callback, Data, lvgl::Event::Callback, nullptr);
    API_PMAZ(message, Data, const char *, "message");
    API_PMAZ(name, Data, const char *, "");
    API_PMAZ(reject, Data, const char *, LV_SYMBOL_CLOSE);
    API_PMAZ(reject_callback, Data, lvgl::Event::Callback, nullptr);
    API_PMAZ(title, Data, const char *, "title");
  };

  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Prompt);

  Column get_content_column() const;

  lvgl::Label get_message_label() const;

private:
  struct Names {
    DESIGN_DECLARE_NAME(accept_button);
    DESIGN_DECLARE_NAME(button_row);
    DESIGN_DECLARE_NAME(cancel_button);
    DESIGN_DECLARE_NAME(column);
    DESIGN_DECLARE_NAME(container);
    DESIGN_DECLARE_NAME(message_label);
    DESIGN_DECLARE_NAME(reject_button);
    DESIGN_DECLARE_NAME(title_label);
  };
};

} // namespace design

#endif // DESIGNLAB_PROMPT_HPP
