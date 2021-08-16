#ifndef DATA_EXTRACTOR_H
#define DATA_EXTRACTOR_H

#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include <CGAL/Point_set_3.h>

namespace mc {
class data_extractor { // Stores points for use in CGAL
  using point_set =
      CGAL::Point_set_3<CGAL::Epick::Point_3, CGAL::Epick::Vector_3>;

public:
  static auto form_rotation(const std::string &folder,
                            const unsigned steps_count = 200) -> point_set;
  static auto form_surface(const std::string &folder,
                           const float step_length = 5.F) -> point_set;
};
} // namespace mc

#endif // DATA_EXTRACTOR_H
