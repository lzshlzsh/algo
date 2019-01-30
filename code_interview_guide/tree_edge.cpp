/**
* @file tree_edge.cpp
* @brief
* @version 1.0
* @date 01/29/2019 10:41:36 PM
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

// 最底层的叶节点
using Leaf = std::vector<const BtreeNode *>;

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

int get_edge(
  const BtreeNode *root,
  LeftRightEdge &left_right_edge,
  Leaf &leaf,
  const int height,
  const int lvl = 0) {
  if (!root) {
    return 0;
  }
  if (!left_right_edge[lvl].first) {
    left_right_edge[lvl].first = root;
  }
  left_right_edge[lvl].second = root;

  if (lvl == height - 1 && !root->left_ && !root->right_) {
    leaf.emplace_back(root);
  }

  get_edge(root->left_, left_right_edge, leaf, height, lvl+1);
  get_edge(root->right_, left_right_edge, leaf, height, lvl+1);

  return 0;
}

int print_edge1(const BtreeNode *root) {
  if (!root) {
    return 0;
  }
  auto const height = get_height(root);
  LeftRightEdge left_right_edge;
  Leaf leaf;
  std::unordered_set<const BtreeNode *> leaf_set;

  left_right_edge.resize(height);
  get_edge(root, left_right_edge, leaf, height);

  // 先打印左边界
  for (auto i = 0; i < height; ++i) {
    std::cout << left_right_edge[i].first->value_ << ' ';
  }
  std::cout << '|';
  // 再打印最底层的非左边界的叶节点
  for (auto const &it: leaf) {
    if (it != left_right_edge[height-1].first) {
      std::cout << it->value_ << ' ';
    }
    leaf_set.emplace(it);
  }
  // 再打印右边界未曾打印的节点
  for (auto i = height-1; i >= 0; --i) {
    // 节点已在左边界打印
    if (left_right_edge[i].second == left_right_edge[i].first) {
      continue;
    } 
    // 节点已在叶节点打印
    if (i == height - 1 && leaf_set.count(left_right_edge[i].second) > 0) {
      continue;
    }
    std::cout << left_right_edge[i].second->value_ << ' ';
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
  
  print_edge1(root1);
  print_edge2(root1);

  print_edge1(root2);
  print_edge2(root2);

  free_array_tree(root1);
  free_array_tree(root2);
  return 0;
}

