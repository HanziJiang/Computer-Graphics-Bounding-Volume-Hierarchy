#include "AABBTree.h"
#include "iostream"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  if (!ray_intersect_box(ray, box, min_t, max_t)) return false;

  t = std::numeric_limits<double>::infinity();
  double left_t, right_t;
  std::shared_ptr<Object> left_descendant, right_descendant;

  bool i1 = (left == NULL) ? false : left->ray_intersect(ray, min_t, max_t, left_t, left_descendant);
  bool i2 = (right == NULL) ? false : right->ray_intersect(ray, min_t, max_t, right_t, right_descendant);

  std::shared_ptr<AABBTree> AABB_attempt;

  if (i1) {
    AABB_attempt = std::dynamic_pointer_cast<AABBTree>(left);

    // it is a shape
    if (!AABB_attempt) {
      left_descendant = left;
    }
  }

  if (i2) {
    AABB_attempt = std::dynamic_pointer_cast<AABBTree>(right);

    // it is a shape
    if (!AABB_attempt) {
      right_descendant = right;
    }
  }

  if (i1 && i2) {
    if (left_t <= right_t) {
      t = left_t;
      descendant = left_descendant;
    } else {
      t = right_t;
      descendant = right_descendant;
    }
  } else if (i1) {
    t = left_t;
    descendant = left_descendant;
  } else if (i2) {
    t = right_t;
    descendant = right_descendant;
  }
  
  return (!(isinf(t)) && (descendant != 0));
  ////////////////////////////////////////////////////////////////////////////
}

