#ifndef IO_OPERATIONS_H
#define IO_OPERATIONS_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>

#include <filesystem>

namespace mc {
namespace io {
// Stores reconstructed model
using surface_mesh = CGAL::Surface_mesh<CGAL::Epick::Point_3>;

// Get current time as string
auto generate_time_string() -> std::string;
// Write mesh to stl file
auto write_mesh(const surface_mesh &mesh, std::filesystem::path filename = {})
    -> void;

} // namespace io

} // namespace mc
#endif // IO_OPERATIONS_H
