// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_GRID_HPP_
#define DESIGNAPI_DESIGN_GRID_HPP_

#include <api/api.hpp>

#include <lvgl/ObjectAccess.hpp>

namespace design {

class Column : public lvgl::ObjectAccess<Column> {
public:
  Column();

private:

};

class Row : public lvgl::ObjectAccess<Row> {
public:
  Row();

private:

};

class Gutter : public lvgl::ObjectAccess<Gutter> {
public:
  Gutter();

private:

};

}

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::Column &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_GRID_HPP_
