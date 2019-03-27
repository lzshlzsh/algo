/**
 * @file 3-btree_traverse.cpp
 * @brief
 * @version 1.0
 * @date 01/31/2019 12:21:18 AM
 * @author lzshlzsh,lzshlzsh@163.com
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
  // 循环不变性：head节点已入栈，以head节点为根的子树尚未遍历
  while (!stack.empty()) {
    head = stack.top();
    stack.pop();
    std::cout << head->value_ << ' ';
    if (head->right_) {
      stack.emplace(head->right_);
    }
    if (head->left_) {
      stack.emplace(head->left_);
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
  // 循环不变性：
  // 不变性1. head节点已入栈，以head节点为根的子树尚未遍历。或者
  // 不变性2. head节点为叶节点
  while (!stack.empty()) {
    // 循环中做三件事
    // 1. 沿着左子树入栈
    while (head->left_) {
      head = head->left_;
      stack.emplace(head);
    }
    // 2. 回退栈。
    //  2.1 如果满足不变性1，则head左子树为空。
    //  此时需要遍历head节点以及head的右子树。
    //  2.2 如果满足不变性2，则head左右子树都为空。
    //  设上次遍历输出的节点为O则栈顶恰好时后继节点，因为：
    //  如果从左子树回退，后继节点即是作子树的
    auto t = stack.top();
    stack.pop();
    std::cout << t->value_ << ' ';
    if (t->right_) {
      head = t->right_;
      stack.emplace(head);
    }
  }
}

void inorder_traverse_norecur2(BtreeNode *head) {
    if (!head) {
        return;
    }

    std::stack<BtreeNode *>stack;
    stack.emplace(head);
    auto last_enter = head;

    while (!stack.empty()) {
        head = stack.top();

        // 关键点:
        // 1. 如何知道左子树已经遍历，通过最近进栈节点是否为栈顶节点判断
        if (head->left_ && last_enter == head) {
            stack.emplace(head->left_);
            last_enter = head->left_;
        } else {
            std::cout << head->value_ << ' ';
            stack.pop();
            if (head->right_) {
                stack.emplace(head->right_);
                last_enter = head->right_;
            }
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

void postorder_traverse_norecur2(BtreeNode *head) {
  if (!head) {
    return;
  }
  std::stack<BtreeNode *>stack;
  stack.emplace(head);
  auto last_enter = head;
  BtreeNode *last_visit = nullptr;

  while (!stack.empty()) {
      head = stack.top();

      // 关键点：
      // 1. 如何知道左子树已经遍历，通过最近进栈节点是否为栈顶节点判断
      // 2. 如何知道右子树已经遍历，通过最近打印节点是否为右孩子判断
      if (head->left_ && last_enter == head) {
          stack.emplace(head->left_);
          last_enter = head->left_;
      } else if (head->right_ && last_visit != head->right_) {
          stack.emplace(head->right_);
          last_enter = head->right_;
      } else {
          stack.pop();
          std::cout << head->value_ << ' ';
          last_visit = head;
      }
  }
}


void test(const size_t node_num) {
  if (node_num <= 0) {
    return;
  }

  auto head = build_array_tree(node_num);

  std::cout << "p1: ";
  preorder_traverse(head);
  std::cout << '\n';

  std::cout << "p2: ";
  preorder_traverse_norecur(head);
  std::cout << '\n';

  std::cout << "i1: ";
  inorder_traverse(head);
  std::cout << '\n';

  std::cout << "i2: ";
  inorder_traverse_norecur(head);
  std::cout << '\n';

  std::cout << "i3: ";
  inorder_traverse_norecur2(head);
  std::cout << '\n';

  std::cout << "o1: ";
  postorder_traverse(head);
  std::cout << '\n';

  std::cout << "o2: ";
  postorder_traverse_norecur(head);
  std::cout << '\n';

  std::cout << "o3: ";
  postorder_traverse_norecur2(head);
  std::cout << '\n';

  free_array_tree(head);
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

