#pragma once

#include <boost/program_options.hpp>

class program_arguments {

  boost::program_options::options_description description_;

  boost::program_options::variables_map vm_;

  constexpr static std::string_view help_header{""};

  // Descriptions
  constexpr static std::string_view help_desc{
      "вывод вспомогоательного сообщения"};
  constexpr static std::string_view type_desc{
      "тип сканирования: 0 - вращение, 1 - поверхность"};
  constexpr static std::string_view folder_desc{
      "папка, в которой находятся текстовые файлы отсканированных профилей"};
  constexpr static std::string_view steps_desc{
      "количество шагов двигателя, необходимое для совершения одного полного "
      "оборота (исользуется с типом 1)"};
  constexpr static std::string_view length_desc{
      "расстояние между полосами сканирования в пикселях (используется с типом "
      "2)"};
  constexpr static std::string_view method_desc{
      "метод реконструкции: 0 - опережающая реконструкция фронта, 1 - "
      "масштабная реконструкция пространства, 2 - "
      "реконструкция Пуассона"};
  constexpr static std::string_view additional_desc{
      "дополнительные операции над облаком точек: 1 - упрощение; 2 - удаление "
      "\"посторонних\" точек; 4 - сглаживание; значения, получаемые операцией "
      "ИЛИ над предыдущими значениями"};

  // Default values
  inline static unsigned method_value = 0;
  inline static unsigned additional_value = 7;

public:
  // Switches
  constexpr static std::string_view help_switch{"help"};
  constexpr static std::string_view type_switch{"type"};
  constexpr static std::string_view folder_switch{"folder"};
  constexpr static std::string_view steps_switch{"steps"};
  constexpr static std::string_view length_switch{"length"};
  constexpr static std::string_view method_switch{"method"};
  constexpr static std::string_view additional_switch{"add"};

  enum type : unsigned { rotation, surface };

  // Get program program_arguments description (for console output mainly)
  [[nodiscard]] auto get_allowed_options() const
      -> const boost::program_options::options_description &;
  // Process program program_arguments
  auto parse(int argc, char *argv[]) -> void;
  // Check if value present by switch
  [[nodiscard]] auto check_value(const std::string_view &key) const -> size_t;
  // Get value by switch
  [[nodiscard]] auto get_value(const std::string_view &key) const
      -> boost::program_options::variable_value;
  program_arguments();
};
