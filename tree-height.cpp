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

int main(int argc, char **argv) {
  int num = 10;
  if (argc >= 2) {
    num = atoi(argv[1]);
  }
  auto root = build_array_tree(num);

  std::cout << num << ": " << get_height(root) << std::endl;
  std::cout << num << ": " << get_height(root, 0) << std::endl;

  free_array_tree(root);
  return 0;
}

