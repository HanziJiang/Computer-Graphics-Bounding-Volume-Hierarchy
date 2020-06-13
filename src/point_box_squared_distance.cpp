#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  double length = 0;
  double sqrd_distance = 0;

  for (int i = 0; i < 3; i++) {
    if (query[i] < box.min_corner[i]) {
      length = query[i] - box.min_corner[i];
    } else if (box.min_corner[i] <= query[i] && query[i] <= box.max_corner[i]) {
      length = 0;
    } else {
      length = query[i] - box.max_corner[i];
    }
    sqrd_distance += pow(length, 2);
  }

  return sqrd_distance;
  ////////////////////////////////////////////////////////////////////////////
}
