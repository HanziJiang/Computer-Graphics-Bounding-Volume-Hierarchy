#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  double t_x_min, t_x_max, t_y_min, t_y_max, t_z_min, t_z_max;

  const double x_min = box.min_corner[0];
  const double y_min = box.min_corner[1];
  const double z_min = box.min_corner[2];
  const double x_max = box.max_corner[0];
  const double y_max = box.max_corner[1];
  const double z_max = box.max_corner[2];

  const double x_direction = ray.direction[0];
  const double y_direction = ray.direction[1];
  const double z_direction = ray.direction[2];

  const double x_e = ray.origin[0];
  const double y_e = ray.origin[1];
  const double z_e = ray.origin[2];

  if (1/x_direction >= 0) {
    t_x_min = (x_min - x_e) / x_direction;
    t_x_max = (x_max - x_e) / x_direction;
  } else {
    t_x_min = -(x_min - x_e) / x_direction;
    t_x_max = -(x_max - x_e) / x_direction;
  }

  if (1/y_direction >= 0) {
    t_y_min = (y_min - y_e) / y_direction;
    t_y_max = (y_max - y_e) / y_direction;
  } else {
    t_y_min = -(y_min - y_e) / y_direction;
    t_y_max = -(y_max - y_e) / y_direction;
  }

  if (1/z_direction >= 0) {
    t_z_min = (z_min - z_e) / z_direction;
    t_z_max = (z_max - z_e) / z_direction;
  } else {
    t_z_min = -(z_min - z_e) / z_direction;
    t_z_max = -(z_max - z_e) / z_direction;
  }

  return !((t_x_max < t_y_min) || (t_y_max < t_x_min) || (t_x_max < t_z_min) || (t_z_max < t_x_min) || (t_y_max < t_z_min) || (t_z_max < t_y_min));
  ////////////////////////////////////////////////////////////////////////////
}
