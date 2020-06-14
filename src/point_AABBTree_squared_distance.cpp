#include "point_AABBTree_squared_distance.h"
#include <queue>
#include "CloudPoint.h"

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  if (!root) return false;

  // Reference: assignment page and https://en.cppreference.com/w/cpp/container/priority_queue
  const double d_root = point_box_squared_distance(query, root->box);
  std::priority_queue<std::pair<double, std::shared_ptr<Object>>, std::vector<std::pair<double, std::shared_ptr<Object>>>, std::greater<std::pair<double, std::shared_ptr<Object>>>> Q;
  std::pair<double, std::shared_ptr<Object>> pair = std::make_pair(d_root, root);
  Q.push(pair);
  sqrd = std::numeric_limits<double>::infinity();
  // the pair that is popped out from Q
  std::pair<double, std::shared_ptr<Object>> popped_pair;
  double d_s, d_l, d_r;
  std::shared_ptr<Object> subtree;
  std::shared_ptr<CloudPoint> cloud_point_attempt;
  std::shared_ptr<AABBTree> AABB;
  double sqrd_min = std::numeric_limits<double>::infinity();;

  while (!Q.empty()) {
    popped_pair = Q.top();
    Q.pop();
    d_s = popped_pair.first;
    if (d_s < min_sqrd || d_s > max_sqrd) continue;
    subtree = popped_pair.second;
    if (d_s < sqrd_min) {
      cloud_point_attempt = std::dynamic_pointer_cast<CloudPoint>(subtree);
      if (cloud_point_attempt) {
        if (cloud_point_attempt->point_squared_distance(query, min_sqrd, max_sqrd, sqrd_min, descendant)) {
          if (sqrd_min < sqrd) {
            sqrd = sqrd_min;
            descendant = cloud_point_attempt;
          }
        }
      } else {
        AABB = std::dynamic_pointer_cast<AABBTree>(subtree);
        d_l = point_box_squared_distance(query, AABB->left->box);
        Q.push(std::make_pair(d_l, AABB->left));
        d_r = point_box_squared_distance(query, AABB->right->box);
        Q.push(std::make_pair(d_r, AABB->right));
      }
    }
  }
  return (min_sqrd <= sqrd && sqrd <= max_sqrd);
  ////////////////////////////////////////////////////////////////////////////
}
