#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  const double a = A[0] - B[0];
  const double b = A[1] - B[1];
  const double c = A[2] - B[2];
  const double d = A[0] - C[0];
  const double e = A[1] - C[1];
  const double f = A[2] - C[2];
  const double g = ray.direction[0];
  const double h = ray.direction[1];
  const double i = ray.direction[2];
  const double j = A[0] - ray.origin[0];
  const double k = A[1] - ray.origin[1];
  const double l = A[2] - ray.origin[2];
  
  const double M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
  if (M == 0) return false;

  const double T = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;
  if (T < min_t) return false;
  
  const double gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
  if (gamma < 0 || gamma > 1) return false;
  
  const double beta = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;
  if (beta < 0 || beta > 1 - gamma) return false;
  
  t = T;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

