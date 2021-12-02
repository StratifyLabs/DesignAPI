// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef LIBRARYAPI_LIBRARY_CLASS_HPP_
#define LIBRARYAPI_LIBRARY_CLASS_HPP_

#include <api/api.hpp>

namespace lib {

class LibraryClass : public api::ExecutionContext {
public:
  LibraryClass();
  ~LibraryClass();
private:
  //This macro is for generating getter/setters fro m_number
  API_ACCESS_FUNDAMENTAL(LibraryClass,int,number,0);
};

}

namespace printer {
class Printer;
//Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const lib::LibraryClass &a);
} // namespace printer

#endif // LIBRARYAPI_LIBRARY_CLASS_HPP_
