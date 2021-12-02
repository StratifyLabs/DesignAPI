// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md


#include <printer/Printer.hpp>

#include "design/Card.hpp"

printer::Printer &
printer::operator<<(Printer &printer, const design::Card &a) {
  return printer;
}

using namespace design;

Card::Card(){

}

