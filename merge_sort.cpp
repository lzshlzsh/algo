/**
 * @file merge_sort.cpp
 * @brief
 * @version 1.0
 * @date 12/14/2018 12:23:28 AM
 * @author sammieliu,sammieliu@tencent.com
 * @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
 */
#include <stdlib.h>
#include <limits.h>

#include <vector>
#include <iostream>
#include <iomanip>

namespace {

int print_vec(const std::vector<int> &vec) {
  for (auto const &it: vec) {
    std::cout << std::setw(2) << it << ' ';
  }
  std::cout << std::endl;
  return 0;
}

int merge_sort(std::vector<int> &vec, const int start, const int end) {
  if (start >= end) {
    return 0;
  }
  auto const mid = (start + end) / 2;
  std::vector<int> left, right;

  for (auto i = start; i <= mid; ++i) {
    left.emplace_back(vec[i]);
  }
  for (auto i = mid + 1; i <= end; ++i) {
    right.emplace_back(vec[i]);
  }
  left.emplace_back(INT_MAX);
  right.emplace_back(INT_MAX);

  merge_sort(left, 0, mid - start);
  merge_sort(right, 0, end - mid - 1);

  for (auto i = 0, j = 0, k = 0; k <= end - start; k++) {
    if (left[i] <= right[j]) {
      vec[k] = left[i++];
    } else {
      vec[k] = right[j++];
    }
  }

  return 0;
}

int test() {
  std::vector<int> vec;
  auto num = random() % 30;
  
  while (num <= 0) {
    num = random() % 30;
  }

  for (auto i = 0; i < num; ++i) {
    vec.emplace_back(random() % (2 * num));
  }

  print_vec(vec);
  merge_sort(vec, 0, num - 1);
  print_vec(vec);

  return 0;
}
} // namespace

int main() {
  srandom(time(nullptr));
  return test();
}
