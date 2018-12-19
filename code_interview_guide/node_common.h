/**
* @file node_common.h
* @brief
* @version 1.0
* @date 12/19/2018 09:33:24 AM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#ifndef  NODE_COMMON_H_
#define  NODE_COMMON_H_
#include <iostream>

namespace common {
/**
 * @brief 
 * @class Node
 */
class Node
{
 public:
  /**
   * @brief
   */
  Node(int value): value_(value), next_(nullptr) {}

  int value_;
  Node *next_;
 protected:
 private:
};

static inline int print_single_link(const Node *head) {
  while (head) {
    std::cout << head->value_ << ' ';
    head = head->next_;
  }
  std::cout << std::endl;
  return 0;
}

static inline Node *build_single_link(const int n) {
  Node *head = nullptr, *tail;
  for (auto i = 0; i < n; ++i) {
    auto tmp = new Node(i);
    if (!head) {
      head = tmp;
    } else {
      tail->next_ = tmp;
    }
    tail = tmp;
  }
  return head;
}

} // namespace common

#endif

