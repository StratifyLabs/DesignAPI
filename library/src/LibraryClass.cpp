// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md


#include <var/StackString.hpp> //for NumberString
#include <printer/Printer.hpp>

#include "lib/LibraryClass.hpp"

printer::Printer &
printer::operator<<(Printer &printer, const lib::LibraryClass &a) {
  return printer.key(a, var::NumberString(a.number());
}

using namespace lib;

LibraryClass::LibraryClass(){
  //do construction work here
}

LibraryClass::~LibraryClass(){
  //do destructor work here
}