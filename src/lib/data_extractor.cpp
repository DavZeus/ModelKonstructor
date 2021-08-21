#include "data_extractor.h"

#include <filesystem>
#include <fstream>
#include <numbers>

auto mk::data_extractor::form_rotation(const std::string &folder,
                                       const unsigned steps_count)
    -> point_set {
  constexpr float full_angle = 360.F;
  constexpr float half_of_full_angle = full_angle / 2.F;
  const float angle = full_angle / static_cast<float>(steps_count);

  point_set cloud;

  float rad = 0.F;

  for (unsigned angle_multiplier = 0U;
       const auto &file : std::filesystem::directory_iterator(folder)) {
    std::ifstream fin(file);
    fin.imbue(std::locale(""));
    if (fin && !std::filesystem::is_empty(file)) {
      const float cos_rad = std::cos(rad);
      const float sin_rad = std::sin(rad);
      while (!fin.eof()) {
        constexpr float camera_width = 3840.F; // TODO: Adjust to camera

        float x;
        float y;
        float z;

        std::string line; // TODO: Check performance of string out of scope

        std::getline(fin, line, '\n');
        if (line.empty()) {
          continue;
        }
        std::stringstream ss(line);
        ss.imbue(std::locale(""));
        ss >> x >> z;

        x = camera_width / 2.F - x;

        y = cos_rad * x;
        x = sin_rad * x;

        cloud.insert({x, y, z});
      }
    }
    ++angle_multiplier;
    if (angle_multiplier >= steps_count) {
      break;
    }
    rad = angle * static_cast<float>(angle_multiplier) *
          std::numbers::pi_v<float> / half_of_full_angle;
  }
  return cloud;
}

auto mk::data_extractor::form_surface(const std::string &folder,
                                      const float step_length) -> point_set {
  point_set cloud;

  for (unsigned step_multiplier = 0U;
       const auto &file : std::filesystem::directory_iterator(folder)) {
    std::ifstream fin(file);
    fin.imbue(std::locale(""));

    const float y = step_length * static_cast<float>(step_multiplier);

    if (!fin && std::filesystem::is_empty(file)) {
      continue;
    }

    while (!fin.eof()) {
      float z;
      float x;
      std::string line; // TODO: Check performance of string out of scope

      std::getline(fin, line);
      if (line.empty()) {
        continue;
      }

      std::stringstream ss(line);
      ss.imbue(std::locale(""));
      ss >> x >> z;

      cloud.insert({x, y, z});
    }

    ++step_multiplier;
  }

  return cloud;
}
