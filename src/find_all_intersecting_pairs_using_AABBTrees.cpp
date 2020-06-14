#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  //////////////////////////////////////////////////////////////////////////
  if (!rootA && !rootB) return;

  // Reference: assignment page
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> Q;
  std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> popped_pair;
  std::shared_ptr<AABBTree> AABB_attempt_1, AABB_attempt_2;

  if (box_box_intersect(rootA->box,rootB->box)) {
    Q.push_back(std::make_pair(rootA, rootB));
  }
  
  while (!Q.empty()) {
    popped_pair = Q.front();
    Q.pop_front();
    AABB_attempt_1 = std::dynamic_pointer_cast<AABBTree>(popped_pair.first);
    AABB_attempt_2 = std::dynamic_pointer_cast<AABBTree>(popped_pair.second);

    // if both are leaves
    if (!AABB_attempt_1 && !AABB_attempt_2) {
      leaf_pairs.push_back(popped_pair);

    // if first is a leaf
    } else if (!AABB_attempt_1) {
      if (box_box_intersect(popped_pair.first->box, AABB_attempt_2->left->box)) {
        Q.push_back(std::make_pair(popped_pair.first, AABB_attempt_2->left));
      }
      if (box_box_intersect(popped_pair.first->box, AABB_attempt_2->right->box)) {
        Q.push_back(std::make_pair(popped_pair.first, AABB_attempt_2->right));  
      }

    // if second is a leaf
    } else if (!AABB_attempt_2){
      if (box_box_intersect(popped_pair.second->box, AABB_attempt_1->left->box))
        Q.push_back(std::make_pair(AABB_attempt_1->left, popped_pair.second));
      if (box_box_intersect(popped_pair.second->box, AABB_attempt_1->right->box))
        Q.push_back(std::make_pair(AABB_attempt_1->right, popped_pair.second));
      
    // if neither is leaf
    } else {
      if (box_box_intersect(AABB_attempt_1->left->box, AABB_attempt_2->left->box)) {
        Q.push_back(std::make_pair(AABB_attempt_1->left, AABB_attempt_2->left));
      }
      if (box_box_intersect(AABB_attempt_1->left->box, AABB_attempt_2->right->box)) {
        Q.push_back(std::make_pair(AABB_attempt_1->left, AABB_attempt_2->right));
      }
      if (box_box_intersect(AABB_attempt_1->right->box, AABB_attempt_2->left->box)) {
        Q.push_back(std::make_pair(AABB_attempt_1->right, AABB_attempt_2->left));
      }
      if (box_box_intersect(AABB_attempt_1->right->box, AABB_attempt_2->right->box)) {
        Q.push_back(std::make_pair(AABB_attempt_1->right, AABB_attempt_2->right));
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
