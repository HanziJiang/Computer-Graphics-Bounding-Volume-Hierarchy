#include "triangle_triangle_intersection.h"
#include "Ray.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  const struct Ray r0(A0, A1-A0);
  const struct Ray r1(A2, A0-A2);
  const struct Ray r2(A1, A2-A1);

  const struct Ray r3(B0, B1-B0);
  const struct Ray r4(B2, B0-B2);
  const struct Ray r5(B1, B2-B1);
  
  double t;
  if (ray_intersect_triangle(r0, B0, B1, B2, 0.0, 1.0, t) || (ray_intersect_triangle(r1, B0, B1, B2, 0.0, 1.0, t)) || (ray_intersect_triangle(r2, B0, B1, B2, 0.0, 1.0, t))) {
    return true;
  }

  if (ray_intersect_triangle(r3, A0, A1, A2, 0.0, 1.0, t) || (ray_intersect_triangle(r4, A0, A1, A2, 0.0, 1.0, t)) || (ray_intersect_triangle(r5, A0, A1, A2, 0.0, 1.0, t))) {
    return true;
  }
  
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
