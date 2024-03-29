#ifndef MODEL_CONSTRUCTOR_H
#define MODEL_CONSTRUCTOR_H

#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include <CGAL/Point_set_3.h>
#include <CGAL/Surface_mesh.h>

class model_constructor {
  // Stores points for use in CGAL
  using point_set =
      CGAL::Point_set_3<CGAL::Epick::Point_3, CGAL::Epick::Vector_3>;
  // Stores reconstructed model
  using surface_mesh = CGAL::Surface_mesh<CGAL::Epick::Point_3>;

public:
  // Reconstruction methods
  enum class methods : unsigned { advancing_front, scale_space, poisson };

private:
  // Chosen reconstruction methods
  methods method_;

public:
  /*
   * TODO: I do not know how to make this enum better because I can not
   * overload operators of nested enum class
   */

  // Pre-reconstruction point cloud modification program_arguments
  enum additional_options : unsigned {
    remove_outliers = 1,
    simplification = remove_outliers * 2,
    smooth = simplification * 2,
    all = remove_outliers | simplification | smooth
  };

private:
  // Chosen program_arguments
  additional_options options_;

  // Remove outliers from point cloud
  auto remove_outliers_from_set(point_set &points, unsigned k_neighbors) const
      -> void;
  // Simplify point cloud
  auto simplify_set(point_set &points, unsigned k_neighbors) const -> void;
  // Smooth point cloud
  auto smooth_set(point_set &points, unsigned k_neighbors) const -> void;
  // Perform pre-reconstruction point cloud modification if needed
  auto process_additional(point_set &points) const -> void;
  // Reconstruct model using advancing front method
  auto do_advancing_front(point_set &points) const -> surface_mesh;
  // Reconstruct model using scale space method
  auto do_scale_space(point_set &points) const -> surface_mesh;
  // Reconstruct model using poisson method
  auto do_poisson(point_set &points) const -> surface_mesh;

public:
  // Reconstruct model from point cloud acquired from camera
  [[nodiscard]] auto make_mesh(point_set points) const -> surface_mesh;

  explicit model_constructor(methods method, additional_options options = all);
};
#endif // MODEL_CONSTRUCTOR_H
