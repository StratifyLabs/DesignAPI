//
// Created by Tyler Gilbert on 2/23/22.
//

#ifndef RUSHROBOTS_LOADINGCIRCLES_HPP
#define RUSHROBOTS_LOADINGCIRCLES_HPP

#include <lvgl/ObjectAccess.hpp>

#include "../macros.hpp"

namespace design {

class LoadingCircles : public lvgl::ObjectAccess<LoadingCircles> {
public:
  LoadingCircles(const char * name, lv_coord_t height);
  LVGL_OBJECT_ACCESS_CONSTRUCT_FROM_OBJECT(LoadingCircles);
  LoadingCircles& update_progress(int value);

private:
  struct Names {
    DESIGN_DECLARE_NAME(circle_row);
  };

  void update_size(int offset);

};

}
#endif // RUSHROBOTS_LOADINGCIRCLES_HPP
