#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();
#include <iostream>

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  I = -1;
  sqrD = std::numeric_limits<double>::infinity();

  const int n = points.rows();

  double distance;
  Eigen::RowVector3d point;
  for (int i = 0; i < n; i++) {
    point = points.row(i);
    distance = pow(point[0]-query[0], 2) + pow(point[1]-query[1], 2) + pow(point[2]-query[2], 2);
    if (distance < sqrD) {
      sqrD = distance;
      I = i;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
