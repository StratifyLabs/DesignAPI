//
// Created by Tyler Gilbert on 12/10/21.
//

#ifndef DESIGN_API_DESIGN_EXTRAS_CARDS_HPP
#define DESIGN_API_DESIGN_EXTRAS_CARDS_HPP

#include <lvgl/Generic.hpp>

namespace design {

//

class Cards {

public:

  /*! \details This card has an icon on a color background
   * on the left and a white background with standard
   * text on the right.
   *
   *
   *
   */
  class A : public lvgl::ObjectAccess<A> {
  public:
    struct Construct {

      API_PMAZ(name,Construct,const char*,"");
      API_PMAZ(background_style,Construct,const char*,"bg_primary");
      API_PMAZ(icon,Construct,const char*,"");

    };
    A(const Construct & options);
  };



};

} // namespace design

#endif // DESIGN_API_DESIGN_EXTRAS_CARDS_HPP
