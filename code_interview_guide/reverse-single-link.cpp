/**
* @file reverse-single-link.cpp
* @brief
* @version 1.0
* @date 12/13/2018 09:32:52 AM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <iostream>

namespace {
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
  Node(const int value): value_(value), next_(nullptr) {}

  int value_;
  Node *next_;
 protected:
 private:
};

int print_link(const Node *head) {
  while (head) {
    std::cout << head->value_ << ' ';
    head = head->next_;
  }
  std::cout << std::endl;
  return 0;
}

Node *reverse_link2(Node *head) {
  if (!head || !head->next_) {
    return head;
  }

  auto next = head->next_;
  head->next_ = nullptr;
  while (next) {
    auto tmp = next->next_;
    next->next_ = head;
    head = next;
    next = tmp;
  }

  return head;
}

int reverse_link(Node *head) {
  Node *tail = head;
  Node *cur = head;
  
  if (!head || !head->next_) {
    return 0;
  }

  while (cur->next_ && cur->next_->next_) {
    tail = tail->next_;
    cur = cur->next_->next_;
  }
  cur = reverse_link2(tail->next_);
  tail->next_ = nullptr;

  tail = cur;
  for (; ;) {
    auto value = cur->value_;
    cur->value_ = head->value_;
    head->value_ = value;

    if (!cur->next_ || !head->next_) {
      break;
    }
    cur = cur->next_;
    head = head->next_;
  }

  // old number
  if (head->next_) {
    head = head->next_;
  }

  // revere right half
  head->next_ = reverse_link2(tail);
  return 0;
}

int test(const int size = 10) {
  Node *head = nullptr, *tail = nullptr;

  for (auto i = 0; i < size; ++i) {
    auto cur = new Node(i);
    if (!head) {
      head = cur;
    } else {
      tail->next_ = cur;
    }
    tail = cur;
  }

  print_link(head);
  reverse_link(head);
  print_link(head);

  while (head) {
    auto next = head->next_;
    delete head;
    head = next;
  }

  return 0;
}


} // namespace


int main(int argc, char **argv) {
  auto size = 10;
  if (argc >= 2) {
    size = atoi(argv[1]);
  }
  return test(size);
}
