#include "model_compiler.h"

#include "data_extractor.h"
#include "model_constructor.h"

auto mc::make_surface_model(const std::string &folder, const float step_length)
    -> void {
  const auto cloud = data_extractor::form_surface(folder, step_length);

  const model_constructor constructor{
      model_constructor::methods::advancing_front};
  const auto mesh = constructor.make_mesh(cloud);
}

auto mc::make_rotation_model(const std::string &folder,
                             const unsigned step_count) -> void {
  const auto cloud = data_extractor::form_rotation(folder, step_count);

  const model_constructor constructor{
      model_constructor::methods::advancing_front};
  const auto mesh = constructor.make_mesh(cloud);
}
