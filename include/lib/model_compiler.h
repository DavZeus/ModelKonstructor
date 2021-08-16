#ifndef MODEL_COMPILER_H
#define MODEL_COMPILER_H

#include <string>

#include "model_constructor.h"

namespace mc {

auto make_rotation_model(
    const std::string &folder,
    model_constructor::methods method =
        model_constructor::methods::advancing_front,
    model_constructor::additional_options option = model_constructor::all,
    unsigned step_count = 200) -> void;
auto make_surface_model(
    const std::string &folder,
    model_constructor::methods method =
        model_constructor::methods::advancing_front,
    model_constructor::additional_options option = model_constructor::all,
    float step_length = 10.F) -> void;

} // namespace mc

#endif // MODEL_COMPILER_H
