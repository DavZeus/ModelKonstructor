#include "model_konstructor.h"

#include "data_extractor.h"
#include "io_operations.h"

#ifndef FMT_UNICODE
#define FMT_UNICODE 1
#endif
#include <fmt/core.h>

auto mk::make_rotation_model(const char *folder, const unsigned method,
                             const unsigned option, const unsigned step_count)
    -> void {
  const auto cloud = data_extractor::form_rotation(folder, step_count);

  fmt::print("Считано {} точек\n", cloud.number_of_points());

  model_generator::methods selected_metod{method};
  model_generator::additional_options selected_options{option};

  const model_generator constructor{selected_metod, selected_options};

  const auto mesh = constructor.make_mesh(cloud);

  const auto file = io::write_mesh(mesh);
  fmt::print("Модель сохранена в файл {}\n", file);
}

auto mk::make_surface_model(const char *folder, const unsigned method,
                            const unsigned option, const float step_length)
    -> void {
  const auto cloud = data_extractor::form_surface(folder, step_length);

  fmt::print("Считано {} точек\n", cloud.number_of_points());

  model_generator::methods selected_metod{method};
  model_generator::additional_options selected_options{option};

  const model_generator constructor{selected_metod, selected_options};

  const auto mesh = constructor.make_mesh(cloud);

  const auto file = io::write_mesh(mesh);
  fmt::print("Модель сохранена в файл {}\n", file);
}
