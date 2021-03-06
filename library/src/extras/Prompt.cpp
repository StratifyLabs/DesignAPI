//
// Created by Tyler Gilbert on 12/29/21.
//

#include <lvgl/Button.hpp>

#include "design/Grid.hpp"
#include "design/HorizontalLine.hpp"
#include "design/Typography.hpp"

#include "design/extras/Prompt.hpp"

using namespace lvgl;
using namespace design;

LVGL_OBJECT_ASSERT_SIZE(Prompt);

Prompt::Prompt(const char * name) {
  construct_object(Data::create_from_name(name));

  auto * data = user_data<Data>();

  add_style("card");
  add(Container(Names::container).fill().add(Column(Names::column).fill()));

  auto column = find<Column>(Names::column);

  column.add(Heading1(data->title))
    .add(HorizontalLine())
    .add(Paragraph(Names::message_label, data->message)
           .fill_width()
           .set_flex_grow())
    .add(Row(Names::button_row));

  auto button_row = find<Row>(Names::button_row)
                      .fill_width()
                      .add(NakedContainer().set_height(0).set_flex_grow());

  if (data->accept_callback) {
    button_row.add(
      lvgl::Button(Names::accept_button)
        .add_label(data->accept)
        .add_style("prompt_accept_btn")
        .add_event_callback(EventCode::clicked, data->accept_callback));
  }

  if (data->reject_callback) {
    button_row.add(
      lvgl::Button(Names::reject_button)
        .add_label(data->reject)
        .add_style("prompt_reject_btn")
        .add_event_callback(EventCode::clicked, data->reject_callback));
  }
}

lvgl::Label Prompt::get_message_label() const {
  return find<lvgl::Label>(Names::message_label);
}

Column Prompt::get_content_column() const {
  return find<Column>(Names::column);
}
