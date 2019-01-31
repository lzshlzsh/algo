/**
* @file btree_common.h
* @brief
* @version 1.0
* @date 01/20/2019 05:51:55 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#ifndef  BTREE_COMMON_H_
#define  BTREE_COMMON_H_

#include <cstddef>
#include <cmath>
#include <sstream>
#include <iostream>

namespace common {

/**
 * @brief 
 * @class BtreeNode
 */
class BtreeNode
{
 public:
  /**
   * @brief
   */
  BtreeNode(): value_(0), left_(nullptr), right_(nullptr) {}
  BtreeNode(const int value): BtreeNode() {
    value_ = value;
  }

  int value_;
  BtreeNode *left_;
  BtreeNode *right_;
 protected:
 private:
};

static inline BtreeNode *build_array_tree(const size_t node_num) {
  if (node_num <= 0) {
    return nullptr;
  }
  auto head = new BtreeNode[node_num];
  for (auto i = 0; i < node_num; ++i) {
    auto &t = head[i];
    auto const left = (i + 1) * 2 - 1;
    auto const rigth = left + 1;

    t.value_ = i + 1;
    if (left < node_num) {
      t.left_ = &head[left];
    }
    if (rigth < node_num) {
      t.right_ = &head[rigth];
    }
  }
  return head;
}

static inline void free_array_tree(BtreeNode *root) {
  if (!root) {
    return;
  }
  delete []root;
}

static inline int get_height(const BtreeNode *root) {
  if (!root) {
    return 0;
  }
  return std::fmax(get_height(root->left_) + 1, get_height(root->right_) + 1);
}

static inline int get_height(const BtreeNode *root, int lvl) {
  if (!root) {
    return lvl;
  }
  return std::fmax(get_height(root->left_, lvl + 1),
                  get_height(root->right_, lvl + 1));
}

static inline int print_tree_graph(
  const BtreeNode *root, const char direct=' ', const int height=0) {
  if (!root) {
    return 0;
  }
  print_tree_graph(root->right_, 'v', height + 1);

  std::stringstream ss;
  auto const width = 15;

  ss << direct << root->value_ << direct;
  auto const print = ss.str();
  auto const left = (width - print.length()) / 2;
  auto const right = width - left - print.length();

  std::cout << std::string(width * height + left, ' ')
    << print << std::string(right, ' ') << std::endl;

  print_tree_graph(root->left_, '^', height + 1);
  return 0;
}

} // namespace common
#endif

