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
    // std::locale::global(std::locale(".utf-8"));

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

    const auto method = static_cast<model_constructor::methods>(
        args.get_value(program_arguments::method_switch).as<unsigned>());
    const auto additional = static_cast<model_constructor::additional_options>(
        args.get_value(program_arguments::additional_switch).as<unsigned>());

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

      mc::make_rotation_model(folder, method, additional, steps);
    } break;
    case program_arguments::surface: {
      if (args.check_value(program_arguments::length_switch) == 0U) {
        fmt::print("Не указано расстояние между профилями. Для дополнительной "
                   "информации введите команду --help");
        return EXIT_SUCCESS;
      }
      const auto length =
          args.get_value(program_arguments::length_switch).as<float>();

      mc::make_surface_model(folder, method, additional, length);
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
