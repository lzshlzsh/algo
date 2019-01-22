/**
* @file btree_traverse.cpp
* @brief
* @version 1.0
* @date 01/20/2019 06:11:27 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/

#include <iostream>
#include <stack>

#include "btree_common.h"

using namespace common;

namespace {

void preorder_traverse(BtreeNode *head) {
  if (!head) {
    return;
  }
  std::cout << head->value_ << ' ';
  preorder_traverse(head->left_);
  preorder_traverse(head->right_);
}

void preorder_traverse_norecur(BtreeNode *head) {
  if (!head) {
    return;
  }

  std::stack<BtreeNode *> stack;

  stack.emplace(head);
  while (!stack.empty()) {
    auto cur = stack.top();
    stack.pop();
    std::cout << cur->value_ << ' ';
    if (cur->right_) {
      stack.emplace(cur->right_);
    }
    if (cur->left_) {
      stack.emplace(cur->left_);
    }
  }
}

void inorder_traverse(BtreeNode *head) {
  if (!head) {
    return;
  }
  inorder_traverse(head->left_);
  std::cout << head->value_ << ' ';
  inorder_traverse(head->right_);
}

void inorder_traverse_norecur(BtreeNode *head) {
  if (!head) {
    return;
  }
  std::stack<BtreeNode *>stack;

  stack.emplace(head);
  while (!stack.empty()) {
    while (head->left_) {
      head = head->left_;
      stack.emplace(head);
    }
    auto t = stack.top();
    stack.pop();
    std::cout << t->value_ << ' ';
    if (t->right_) {
      head = t->right_;
      stack.emplace(head);
    }
  }
}

void postorder_traverse(BtreeNode *head) {
  if (!head) {
    return;
  }
  postorder_traverse(head->left_);
  postorder_traverse(head->right_);
  std::cout << head->value_ << ' ';
}

void postorder_traverse_norecur(BtreeNode *head) {
  if (!head) {
    return;
  }
  std::stack<BtreeNode *>stack;
  BtreeNode *last = nullptr;

  stack.emplace(head);
  while (!stack.empty()) {
    while (head->left_) {
      head = head->left_;
      stack.emplace(head);
    }

    auto t = stack.top();

    if (t->left_ == last && t->right_) {
      head = t->right_;
      stack.emplace(head);
    } else {
      last = t;
      std::cout << t->value_ << ' ';
      stack.pop();
    }
  }
}

void test(const size_t node_num) {
  if (node_num <= 0) {
    return;
  }

  auto head = build_array_tree(node_num);

  std::cout << "p: ";
  preorder_traverse(head);
  std::cout << '\n';

  std::cout << "p: ";
  preorder_traverse_norecur(head);
  std::cout << '\n';

  std::cout << "i: ";
  inorder_traverse(head);
  std::cout << '\n';

  std::cout << "i: ";
  inorder_traverse_norecur(head);
  std::cout << '\n';

  std::cout << "o: ";
  postorder_traverse(head);
  std::cout << '\n';

  std::cout << "o: ";
  postorder_traverse_norecur(head);
  std::cout << '\n';
}

} // namespace

int main(int argc, char **argv) {
  int node_num = 10;

  if (argc >= 2) {
    node_num = atoi(argv[1]);
  }
  test(node_num);
  return 0;
}

