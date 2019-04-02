/**
* @file 3-bst-maxtop.cpp
* @brief
* @version 1.0
* @date 04/01/2019 11:02:12 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <iostream>
#include <algorithm>

#include  "btree_common.h"

namespace {

/**
 * @brief 
 * @class BstMaxTop
 */
class BstMaxTop
{
 public:
  /**
   * @brief
   */
  BstMaxTop() {
    (void)init_tree();
  }
  ~BstMaxTop() {
    common::free_array_tree(root_);
  }

  int bst_maxtop1() {
    return bst_maxtop1(root_);
  }

  int bst_maxtop2() {
    return bst_maxtop2(root_);
  }

 protected:
 private:
  common::BtreeNode *root_;

  int init_tree() {
    root_ = new common::BtreeNode[15];
    root_[0].value_ = 6;
    root_[0].left_ = &root_[1];
    root_[0].right_ = &root_[2];

    root_[1].value_ = 1;
    root_[1].left_ = &root_[3];
    root_[1].right_ = &root_[4];

    root_[2].value_ = 12;
    root_[2].left_ = &root_[5];
    root_[2].right_ = &root_[6];

    root_[3].value_ = 0;
    root_[4].value_ = 3;

    root_[5].value_ = 10;
    root_[5].left_ = &root_[7];
    root_[5].right_ = &root_[8];

    root_[6].value_ = 13;
    root_[6].left_ = &root_[9];
    root_[6].right_ = &root_[10];

    root_[7].value_ = 4;
    root_[7].left_ = &root_[11];
    root_[7].right_ = &root_[12];

    root_[8].value_ = 14;
    root_[8].left_ = &root_[13];
    root_[8].right_ = &root_[14];

    root_[9].value_ = 20;
    root_[10].value_ = 16;
    root_[11].value_ = 2;
    root_[12].value_ = 5;
    root_[13].value_ = 11;
    root_[14].value_ = 15;

    common::print_tree_graph(root_);

    return 0;
  }

  int bst_maxtop1(common::BtreeNode *root) {
    if (!root) {
      return 0;
    }

    return std::max(bst_maxtop1(root->left_), std::max(
        bst_maxtop1(root->right_), bst_maxtop1_root(root, root)));
  }

  int bst_maxtop1_root(common::BtreeNode *root, common::BtreeNode *cur) {
    if (!root || !cur || !is_bst_node(root, cur)) {
      return 0;
    }
    return bst_maxtop1_root(root, cur->left_) +
      bst_maxtop1_root(root, cur->right_) + 1;
  }

  bool is_bst_node(common::BtreeNode *root, common::BtreeNode *cur) {
    if (!root) {
      return false;
    }
    if (root == cur) {
      return true;
    }

    if (cur->value_ < root->value_) {
      return is_bst_node(root->left_, cur);
    } else {
      return is_bst_node(root->right_, cur);
    }
  }

  int bst_maxtop2(common::BtreeNode *root) {
    return 0;
  }
};


} // namespace

int main(int argc, char **argv) {
  BstMaxTop bst_maxtop;

  std::cout << bst_maxtop.bst_maxtop1() << std::endl;
  std::cout << bst_maxtop.bst_maxtop2() << std::endl;

  return 0;
}
