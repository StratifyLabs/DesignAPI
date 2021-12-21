//
// Created by Tyler Gilbert on 12/21/21.
//

#ifndef DESIGNAPI_DESIGN_MACROS_H_
#define DESIGNAPI_DESIGN_MACROS_H_

#define INCBIN_PREFIX design_incbin_
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_SILENCE_BITCODE_WARNING 1

#include "incbin.h"

#define DESIGN_INCBIN_DATA(NAME) design_incbin_##NAME##_data

#endif // DESIGNAPI_DESIGN_MACROS_H_
