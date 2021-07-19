#ifndef MODEL_COMPILER_H
#define MODEL_COMPILER_H

#include <string>

namespace mc {
auto make_rotation_model(const std::string &folder,
                         const unsigned step_count = 200) -> void;
auto make_surface_model(const std::string &folder,
                        const float step_length = 10.F) -> void;
} // namespace mc

#endif // MODEL_COMPILER_H
