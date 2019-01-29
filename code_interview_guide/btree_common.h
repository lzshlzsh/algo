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

} // namespace common
#endif

