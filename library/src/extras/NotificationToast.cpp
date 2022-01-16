//
// Created by Tyler Gilbert on 1/16/22.
//

#include <lvgl/Button.hpp>
#include <lvgl/Event.hpp>
#include <lvgl/Label.hpp>

#include "design/Grid.hpp"
#include "design/Typography.hpp"
#include "design/HorizontalLine.hpp"
#include "design/extras/NotificationToast.hpp"

using namespace lvgl;
using namespace design;

NotificationToast::NotificationToast(chrono::MicroTime lifetime) {
  construct_object(Names::toast_name);
  add_style(Column::get_style());
  add_style("toast");
  add(Row()
        .fill_width()
        .set_background_opacity(Opacity::transparent)
        .add(Label(Names::title_label).add_style("toast_title").set_flex_grow())
        .add(Button(Names::close_button)
               .add_style("btn_sm btn_light")
               .add_label_as_static(LV_SYMBOL_CLOSE)
               .add_event_callback(EventCode::clicked, [](lv_event_t *e) {
                 Event(e)
                   .target()
                   .find_parent<NotificationToast>(Names::toast_name)
                   .remove_later(50_milliseconds);
               })));
  add(HorizontalLine());
  add(Paragraph(Names::message_label).fill_width().add_style("toast_message"));

  if (lifetime.milliseconds() > 0) {
    remove_later(lifetime);
  }
}

NotificationToast &NotificationToast::set_title_as_static(const char *value) {
  find<Label>(Names::title_label).set_text_as_static(value);
  return *this;
}

NotificationToast &NotificationToast::set_title(const char *value) {
  find<Label>(Names::title_label).set_text(value);
  return *this;
}

NotificationToast &NotificationToast::set_message_as_static(const char *value) {
  find<Label>(Names::message_label).set_text_as_static(value);
  return *this;
}

NotificationToast &NotificationToast::set_message(const char *value) {
  find<Label>(Names::message_label).set_text(value);
  return *this;
}
