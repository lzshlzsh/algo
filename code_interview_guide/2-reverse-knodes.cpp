/**
 * @file 2-reverse-knodes.cpp
 * @brief
 * @version 1.0
 * @date 01/31/2019 12:21:04 AM
 * @author lzshlzsh,lzshlzsh@163.com
 * @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
 */
#include "node_common.h"

#include <stdlib.h>

using namespace common;

namespace {

Node *do_reverse_knodes(Node *head, const int k) {
  if (!head || k < 2) {
    return head;
  }
  Node *prev = nullptr;
  Node *h1;
  Node *tail, *tail2;

  for (; ;) {
    int tmp_k = k;
    if (!prev) {
      tail = head;
      tail2 = head;
    } else {
      tail = prev->next_;
      tail2 = prev->next_;
    }
    while (tail && --tmp_k && tail->next_) {
      tail = tail->next_;
    }

    if (tmp_k) {
      break;
    }

    if (prev) {
      prev->next_ = tail;
    } else {
      head = tail;
    }
    h1 = tail2;
    prev = h1;
    h1 = h1->next_;
    prev->next_ = tail->next_;
    while (h1 != tail) {
      auto next = h1->next_;
      h1->next_ = prev;
      prev = h1;
      h1 = next;
    }
    h1->next_ = prev;
    prev = tail2;
  }

  return head;
}

int reverse_knodes(const int n, const int k) {
  auto head = build_single_link(n);
  print_single_link(head);
  head = do_reverse_knodes(head, k);
  print_single_link(head);
  return 0;
}

} // namespace

int main(int argc, char **argv) {
  int n = 10;  
  int k = 3;

  if (argc >= 2) {
    n = atoi(argv[1]);
  }
  if (argc >= 3) {
    k = atoi(argv[2]);
  }
  reverse_knodes(n, k);
  return 0;
}

