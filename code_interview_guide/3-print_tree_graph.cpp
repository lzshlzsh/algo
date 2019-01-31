/**
* @file 3-print_tree_graph.cpp
* @brief
* @version 1.0
* @date 01/31/2019 09:58:12 AM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/

#include "./btree_common.h"

using namespace common;

namespace {

} // namespace

int main(int argc, char **argv) {
  int len = 10;

  if (argc >= 2) {
    len = atoi(argv[1]);
  }

  auto root = build_array_tree(len);

  print_tree_graph(root);

  free_array_tree(root);
  return 0;
}
