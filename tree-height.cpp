/**
* @file tree-height.cpp
* @brief
* @version 1.0
* @date 01/29/2019 09:57:24 AM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <iostream>
#include <cmath>

#include "code_interview_guide/btree_common.h"

using namespace common;
namespace {

int get_height(BtreeNode *root) {
  if (!root) {
    return 0;
  }
  return std::max(get_height(root->left_) + 1, get_height(root->right_) + 1);
}

int get_height(BtreeNode *root, int lvl) {
  if (!root) {
    return lvl;
  }
  return std::max(get_height(root->left_, lvl + 1),
                  get_height(root->right_, lvl + 1));
}

} // namespace

int main(int argc, char **argv) {
  int num = 10;
  if (argc >= 2) {
    num = atoi(argv[1]);
  }
  auto root = build_array_tree(num);

  std::cout << num << ": " << get_height(root) << std::endl;
  std::cout << num << ": " << get_height(root, 0) << std::endl;

  return 0;
}

