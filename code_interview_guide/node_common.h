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

static inline Node *build_single_link(const int n, const int start_value=0) {
  Node *head = nullptr, *tail;
  for (auto i = 0; i < n; ++i) {
    auto tmp = new Node(i+start_value);
    if (!head) {
      head = tmp;
    } else {
      tail->next_ = tmp;
    }
    tail = tmp;
  }
  return head;
}

static inline Node *build_loop_link(const int num, const int start_value=0) {
  Node *head = nullptr;
  Node *tail;
  Node *first_loop_node = nullptr;

  if (num < 1) {
    return head;
  }

  for (int i = 0; i < num; ++i) {
    auto tmp = new Node(i+start_value);
    if (!head) {
      head = tmp;
    } else {
      tail->next_ = tmp;
    }
    tail = tmp;
    if (i == (num/2)) {
      first_loop_node = tmp;
    }
  }

  tail->next_ = first_loop_node;

  return head;
}

static inline Node *get_first_loop_node(Node *head) {
  if (!head || !head->next_) {
    return nullptr;
  }

  auto slow = head->next_;
  auto fast = head->next_->next_;
  while (slow && fast && slow != fast) {
    slow = slow->next_;
    fast = fast->next_;
    if (!fast) {
      break;
    }
    fast = fast->next_;
  }

  if (!fast) {
    return nullptr;
  }

  slow = head;
  while (slow != fast) {
    slow = slow->next_;
    fast = fast->next_;
  }

  return slow;
}

static inline int print_link(Node *head) {
  auto first_loop_node = get_first_loop_node(head);
  int i = 2;

  if (!first_loop_node) {
    return print_single_link(head);
  }

  for (; i ;) {
    std::cout << head->value_ << ' ';
    head = head->next_;

    if (head == first_loop_node) {
      i--;
    }
  }
  if (first_loop_node) {
    std::cout << '(' << first_loop_node->value_ << ')';
  }

  std::cout << std::endl;

  return 0;
}

} // namespace common

#endif

