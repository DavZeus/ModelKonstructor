#include <boost/exception/diagnostic_information.hpp>
#include <model_compiler.h>

#ifndef FMT_UNICODE
#define FMT_UNICODE 1
#endif
#include <fmt/core.h>
#include <fmt/ostream.h>

#include "program_arguments.h"

int main(int argc, char *argv[]) {
  try {
    program_arguments args;
    args.parse(argc, argv);

    if (args.check_value(program_arguments::help_switch) != 0U) {
      fmt::print("{}", args.get_allowed_options());
      return EXIT_SUCCESS;
    }

    if (args.check_value(program_arguments::folder_switch) == 0U) {
      fmt::print("Не указана папка с профилями. Для дополнительной информации "
                 "введите команду --help");
      return EXIT_SUCCESS;
    }
    const auto folder =
        args.get_value(program_arguments::folder_switch).as<std::string>();

    if (args.check_value(program_arguments::type_switch) == 0U) {
      fmt::print("Не указан тип сканирования. Для дополнительной информации "
                 "введите команду --help");
      return EXIT_SUCCESS;
    }

    switch (const auto type = static_cast<program_arguments::type>(
                args.get_value(program_arguments::type_switch).as<unsigned>());
            type) {
    case program_arguments::rotation: {

      if (args.check_value(program_arguments::steps_switch) == 0U) {
        fmt::print("Не указано количество шагов двигателя. Для дополнительной "
                   "информации введите команду --help");
        return EXIT_SUCCESS;
      }
      const auto steps =
          args.get_value(program_arguments::steps_switch).as<unsigned>();

      mc::make_rotation_model(folder, steps);
    } break;
    case program_arguments::surface: {
      if (args.check_value(program_arguments::length_switch) == 0U) {
        fmt::print("Не указано расстояние между профилями. Для дополнительной "
                   "информации введите команду --help");
        return EXIT_SUCCESS;
      }
      const auto length =
          args.get_value(program_arguments::length_switch).as<float>();

      mc::make_surface_model(folder, length);
    } break;
    default:
      fmt::print("Неправильный тип сканирования. Для дополнительной информации "
                 "введите команду --help");
    }
  } catch (const boost::exception &ex) {
    fmt::print(stderr, "\n{}\n", boost::diagnostic_information(ex));
  } catch (const std::exception &ex) {
    fmt::print(stderr, "\n{}\n", ex.what());
  }
}
