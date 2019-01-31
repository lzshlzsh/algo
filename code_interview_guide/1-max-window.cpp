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

template <typename T>
std::vector<int> get_max_window(const T &A, const size_t num,
                                const size_t win) {
  std::list<int> max_queue;
  std::vector<int> ret;

  for (auto i = 0; i < num; ++i) {
    while (!max_queue.empty() && A[i] >= A[max_queue.back()]) {
      max_queue.pop_back();
    }
    if (!max_queue.empty() && i >= win && (max_queue.front() <= (i-win))) {
      max_queue.pop_front();
    }
    max_queue.emplace_back(i);

    if (i >= (win - 1)) {
      ret.emplace_back(A[max_queue.front()]);
    }
  }

  return ret;
}

template <typename T>
int test(const T &array, const size_t array_len, const size_t win_len) {
  auto const ret = get_max_window(array, array_len, win_len);

  print_array(array, array_len);

  for (auto i = 0; i < win_len - 1; ++i) {
    std::cout << std::setfill(' ') << std::setw(5) << ' ';
  }

  print_array(ret, ret.size()); 

  return 0;
}

}

int main(int argc, char **argv) {
  const int A[] = {4, 3, 5, 4, 3, 3, 6, 7};
  int len = 10;

  srandom(time(nullptr));

  test(A, sizeof(A) / sizeof(A[0]), 3);

  if (argc >= 2) {
    len = atoi(argv[1]);
  }
  test(build_vector_random(len), len, 3);
  return 0;
}

