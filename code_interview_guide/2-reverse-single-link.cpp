/**
 * @file 2-reverse-single-link.cpp
 * @brief
 * @version 1.0
 * @date 01/31/2019 12:21:11 AM
 * @author lzshlzsh,lzshlzsh@163.com
 * @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
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
  cur = tail->next_; //first node of right half
  tail->next_ = nullptr;
  auto prev = tail; // last node of left half

  // 后半部分反转
  while (cur) {
    auto next = cur->next_;
    cur->next_ = prev;
    prev = cur;
    cur = next;
  }

  // 交换节点值
  cur = prev; // last node of right half
  while (cur && head) {
    if (cur != head) {
      auto value = cur->value_;
      cur->value_ = head->value_;
      head->value_ = value;
    }

    cur = cur->next_;
    head = head->next_;
  }

  // 后半部分反转回去
  cur = nullptr;
  while (prev) {
    head = prev->next_;
    prev->next_ = cur;
    cur = prev;
    prev= head;
  }

  return 0;
}

int reverse_link2(Node *head) {
  if (!head || !head->next_) {
    return 0;
  }

  auto tail = head->next_;
  while (tail->next_) {
    tail = tail->next_;
  }

  // swap head and tail
  auto value = head->value_;
  head->value_ = tail->value_;
  tail->value_ = value;

  // swap middle
  auto prev = tail;
  auto cur = head->next_;
  while (cur != tail) {
    auto next = cur->next_;
    cur->next_ = prev;
    prev = cur;
    cur = next;
  }

  head->next_ = prev;

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
  reverse_link2(head);
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
