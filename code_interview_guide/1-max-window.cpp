/**
 * @file 1-max-window.cpp
 * @brief
 * @version 1.0
 * @date 01/31/2019 12:20:35 AM
 * @author lzshlzsh,lzshlzsh@163.com
 * @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
 */
#include <iostream>
#include <vector>
#include <list>

#include "../array_common.h"

using namespace common;

namespace {

std::vector<int> get_max_window(const int *A, const size_t num,
                                const size_t win) {
  std::list<int> max_queue;
  std::vector<int> ret;

  for (auto i = 0; i < num; ++i) {
    while (!max_queue.empty() && A[i] >= A[max_queue.back()]) {
      max_queue.pop_back();
    }
    if (!max_queue.empty() && (max_queue.front() <= (i-win))) {
      max_queue.pop_front();
    }
    max_queue.emplace_back(i);

    if (i >= (win - 1)) {
      ret.emplace_back(A[max_queue.front()]);
    }
  }

  return ret;
}

}

int main() {
  const int A[] = {4, 3, 5, 4, 3, 3, 6, 7};
  auto const array_len = sizeof(A) / sizeof(A[0]);
  auto const win_len = 3;
  auto const ret = get_max_window(A, array_len, win_len);

  print_array(A, array_len);

  for (auto i = 0; i < win_len - 1; ++i) {
    std::cout << std::setfill(' ') << std::setw(5) << ' ';
  }

  print_array(ret, ret.size()); 
  return 0;
}

