/**
 * @file 3-tree_edge.cpp
 * @brief
 * @version 1.0
 * @date 01/31/2019 12:21:24 AM
 * @author lzshlzsh,lzshlzsh@163.com
 * @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
 */
#include <stdlib.h>

#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "btree_common.h"

using namespace common;

namespace {

// 每一层的<左边界节点，右边界节点>
using LeftRightEdge = std::vector<std::pair<const BtreeNode *,
      const BtreeNode *>>;

BtreeNode *build_myarray_tree() {
  auto root = new BtreeNode[16];
  
  for (auto i = 0; i < 16; ++i) {
    root[i].value_ = i + 1;
  }

  root[0].left_ = &root[1];
  root[0].right_ = &root[2];

  root[1].right_ = &root[3];

  root[2].left_ = &root[4];
  root[2].right_ = &root[5];

  root[3].left_ = &root[6];
  root[3].right_ = &root[7];

  root[4].left_ = &root[8];
  root[4].right_ = &root[9];

  root[7].right_ = &root[10];

  root[8].left_ = &root[11];

  root[10].left_ = &root[12];
  root[10].right_ = &root[13];

  root[11].left_ = &root[14];
  root[11].right_ = &root[15];

  return root;
}

BtreeNode *build_myarray_tree2() {
  BtreeNode *root = new BtreeNode[8];

  for (auto i = 0; i < 8; ++i) {
    root[i].value_ = i + 1;
  }

  root[0].left_ = &root[1];
  root[0].right_ = &root[2];

  root[1].left_ = &root[3];
  root[1].right_ = &root[4];

  root[2].left_ = &root[5];

  root[5].left_ = &root[6];
  root[5].right_ = &root[7];

  return root;
}

int get_left_right_node(
  const BtreeNode *root,
  LeftRightEdge &left_right_edge,
  const int lvl = 0) {
  if (!root) {
    return 0;
  }
  if (!left_right_edge[lvl].first) {
    left_right_edge[lvl].first = root;
  }
  left_right_edge[lvl].second = root;

  get_left_right_node(root->left_, left_right_edge, lvl+1);
  get_left_right_node(root->right_, left_right_edge, lvl+1);

  return 0;
}

int print_leaf_not_in_left(const BtreeNode *root,
               const LeftRightEdge &left_right_edge,
               const int lvl = 0) {
  if (!root) {
    return 0;
  }

  if (!root->left_ && !root->right_ &&
      root != left_right_edge[lvl].first &&
      root != left_right_edge[lvl].second) {
    std::cout << root->value_ << ' ';
  }

  print_leaf_not_in_left(root->left_, left_right_edge, lvl+1);
  print_leaf_not_in_left(root->right_, left_right_edge, lvl+1);

  return 0;
}

int print_edge1(const BtreeNode *root) {
  if (!root) {
    return 0;
  }
  auto const height = get_height(root);
  LeftRightEdge left_right_edge;

  left_right_edge.resize(height);
  get_left_right_node(root, left_right_edge);
 
  for (auto i = 0; i < height; ++i) {
    std::cout << left_right_edge[i].first->value_ << ' ';
  }
  std::cout << '|';
  print_leaf_not_in_left(root, left_right_edge);

  std::cout << '|';
  for (auto i = height-1; i >= 0; --i) {
    if (left_right_edge[i].second != left_right_edge[i].first) {
      std::cout << left_right_edge[i].second->value_ << ' ';
    }
  }

  std::cout << std::endl;
  return 0;
}
 
int print_edge2(BtreeNode *root) {
  return 0;
}

} // namespace

int main(int argc, char **argv) {
  int num = 10;
  if (argc >= 2) {
    num = atoi(argv[1]);
  }

  auto root1 = build_array_tree(num);
  auto root2 = build_myarray_tree();
  auto root3 = build_myarray_tree2();
  
  print_tree_graph(root1, ' ', 0, 6);
  print_edge1(root1);
  print_edge2(root1);

  std::cout << "\033[32m------------------------------------------\033[0m\n";
  print_tree_graph(root2, ' ', 0, 6);
  print_edge1(root2);
  print_edge2(root2);

  std::cout << "\033[32m------------------------------------------\033[0m\n";
  print_tree_graph(root3, ' ', 0, 6);
  print_edge1(root3);
  print_edge2(root3);

  free_array_tree(root1);
  free_array_tree(root2);
  free_array_tree(root3);
  return 0;
}

