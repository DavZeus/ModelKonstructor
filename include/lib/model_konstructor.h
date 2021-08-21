#ifndef MODEL_COMPILER_H
#define MODEL_COMPILER_H

#ifndef MK_STATIC
#ifdef MODELKONSTRUCTORDYNAMIC_EXPORTS
#define MK_API __declspec(dllexport)
#else
#define MK_API __declspec(dllimport)
#endif
#else
#define MK_API
#endif // !MK_STATIC

#include <string>

#include "model_generator.h"

namespace mk {

extern "C++" MK_API auto make_rotation_model(const char *folder,
                                             unsigned method, unsigned option,
                                             unsigned step_count = 200) -> void;
extern "C++" MK_API auto make_surface_model(const char *folder, unsigned method,
                                            unsigned option,
                                            float step_length = 10.F) -> void;

} // namespace mk

#endif // MODEL_COMPILER_H
