#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  const int num_object = objects.size();

  if (num_object == 0) {
    left, right = NULL;
  } else if (num_object == 1) {
    left = objects[0];
    right = NULL;
    insert_box_into_box(objects[0]->box, box);
  } else if (num_object == 2) {
    left = objects[0];
    right = objects[1];
    insert_box_into_box(objects[0]->box, box);
    insert_box_into_box(objects[1]->box, box);
  } else {
    for (int i = 0; i < num_object; i++) {
      insert_box_into_box(objects[i]->box, box);
    }

    const double x_length = abs(box.max_corner[0] - box.min_corner[0]);
    const double y_length = abs(box.max_corner[1] - box.min_corner[1]);
    const double z_length = abs(box.max_corner[2] - box.min_corner[2]);

    // what if infinity?

    int axis;
    axis = (x_length > y_length) ? 0 : 1;
    if (z_length > axis) axis = 2;

    const double m = abs(box.max_corner[axis] - box.min_corner[axis]) / 2;

    std::vector<std::shared_ptr<Object>> left_objects;
    std::vector<std::shared_ptr<Object>> right_objects;
    for (int i = 0; i < num_object; i++) {
      if ((objects[i]->box).center()[axis] < m) {
        left_objects.push_back(objects[i]);
      } else {
        right_objects.push_back(objects[i]);
      }
    }

    left = (left_objects.size() == 1) ? left_objects[0] : std::make_shared<AABBTree>(left_objects, a_depth + 1);
    right = (right_objects.size() == 1) ? right_objects[0] : std::make_shared<AABBTree>(right_objects, a_depth + 1);
  }
  ////////////////////////////////////////////////////////////////////////////
}
