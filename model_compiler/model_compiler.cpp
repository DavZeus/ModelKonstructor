#include "model_compiler.h"

#include "data_extractor.h"
#include "io_operations.h"
#include "model_constructor.h"

auto mc::make_rotation_model(const std::string &folder,
                             const model_constructor::methods method,
                             const model_constructor::additional_options option,
                             const unsigned step_count) -> void {
  const auto cloud = data_extractor::form_rotation(folder, step_count);

  const model_constructor constructor{method, option};
  const auto mesh = constructor.make_mesh(cloud);

  io::write_mesh(mesh);
}

auto mc::make_surface_model(const std::string &folder,
                            const model_constructor::methods method,
                            const model_constructor::additional_options option,
                            const float step_length) -> void {
  const auto cloud = data_extractor::form_surface(folder, step_length);

  const model_constructor constructor{method, option};
  const auto mesh = constructor.make_mesh(cloud);

  io::write_mesh(mesh);
}
