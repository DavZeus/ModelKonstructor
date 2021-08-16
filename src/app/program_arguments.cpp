#include "program_arguments.h"

auto program_arguments::get_allowed_options() const
    -> const boost::program_options::options_description & {
  return description_;
}

auto program_arguments::parse(int argc, char *argv[]) -> void {
  store(parse_command_line(argc, argv, description_), vm_);
  notify(vm_);
}

auto program_arguments::check_value(const std::string_view &key) const
    -> size_t {
  return vm_.count(key.data());
}

auto program_arguments::get_value(const std::string_view &key) const
    -> boost::program_options::variable_value {
  return vm_.at(key.data());
}

program_arguments::program_arguments()
    : description_("Допустимые аргументы командной строки") {
  description_.add_options()(help_switch.data(), help_desc.data())(
      type_switch.data(), boost::program_options::value<unsigned>(),
      type_desc.data())(folder_switch.data(),
                        boost::program_options::value<std::string>(),
                        folder_desc.data())(
      steps_switch.data(), boost::program_options::value<unsigned>(),
      steps_desc.data())(length_switch.data(),
                         boost::program_options::value<float>(),
                         length_desc.data())(
      method_switch.data(),
      boost::program_options::value<decltype(method_value)>()->default_value(
          method_value),
      method_desc.data())(
      additional_switch.data(),
      boost::program_options::value<decltype(additional_value)>()
          ->default_value(additional_value),
      additional_desc.data());
}
