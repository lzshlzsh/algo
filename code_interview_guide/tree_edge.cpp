/**
* @file tree_edge.cpp
* @brief
* @version 1.0
* @date 01/29/2019 10:41:36 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <stdlib.h>

#include "btree_common.h"

using namespace common;

namespace {

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

} // namespace

int main(int argc, char **argv) {
  int num = 0;
  if (argc >= 2) {
    num = atoi(argv[1]);
  }

  auto root1 = build_array_tree(num);
  auto root2 = build_myarray_tree();
  

  free_array_tree(root1);
  free_array_tree(root2);
  return 0;
}

