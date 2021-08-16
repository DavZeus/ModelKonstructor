#include "model_compiler.h"

#include "data_extractor.h"
#include "io_operations.h"
#include "model_constructor.h"

#ifndef FMT_UNICODE
#define FMT_UNICODE 1
#endif
#include <fmt/core.h>

auto mc::make_rotation_model(const std::string &folder,
                             const model_constructor::methods method,
                             const model_constructor::additional_options option,
                             const unsigned step_count) -> void {
  const auto cloud = data_extractor::form_rotation(folder, step_count);

  fmt::print("Считано {} точек\n", cloud.number_of_points());

  const model_constructor constructor{method, option};
  const auto mesh = constructor.make_mesh(cloud);

  const auto file = io::write_mesh(mesh);
  fmt::print("Модель сохранена в файл {}\n", file);
}

auto mc::make_surface_model(const std::string &folder,
                            const model_constructor::methods method,
                            const model_constructor::additional_options option,
                            const float step_length) -> void {
  const auto cloud = data_extractor::form_surface(folder, step_length);

  fmt::print("Считано {} точек\n", cloud.number_of_points());

  const model_constructor constructor{method, option};
  const auto mesh = constructor.make_mesh(cloud);

  const auto file = io::write_mesh(mesh);
  fmt::print("Модель сохранена в файл {}\n", file);
}
