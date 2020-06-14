#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // the number of triangles
  const int n = F.rows();

  double temp_t;
  double smallest_t = std::numeric_limits<double>::infinity();
  Eigen::RowVector3d A, B, C;
  int temp_hit_f;
  bool hit = false;

  for (int i = 0; i < n; i++) {
      A = V.row(F(i, 0));
      B = V.row(F(i, 1));
      C = V.row(F(i, 2));
      if (ray_intersect_triangle(ray, A, B, C, min_t, max_t, temp_t)) {
        if (temp_t < smallest_t) {
          smallest_t = temp_t;
          temp_hit_f = i;
          hit = true;
        }
      }
    }

    if (hit) {
      hit_t = smallest_t;
      hit_f = temp_hit_f;
      return (hit_t >= min_t && hit_t <= max_t);
    }

    return false;

  ////////////////////////////////////////////////////////////////////////////
}
