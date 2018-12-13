/**
* @file quicksort.cpp
* @brief
* @version 1.0
* @date 12/13/2018 11:38:40 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <stdlib.h>

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

int partition(std::vector<int> &vec, const int start, const int end) {
  auto const pivot = vec[end];
  auto i = start - 1;

  for (auto j = start; j < end; ++j) {
    if (vec[j] <= pivot) {
      if (++i != j) {
        auto tmp = vec[i];
        vec[i] = vec[j];
        vec[j] = tmp;
      }
    }
  }
  if (++i != end) {
    vec[end] = vec[i];
    vec[i] = pivot;
  }
  return i;
}

int quicksort(std::vector<int> &vec, const int start, const int end) {
  if (start >= end) {
    return 0;
  }
  auto const mid = partition(vec, start, end);
  quicksort(vec, start, mid - 1);
  quicksort(vec, mid + 1, end);

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
  quicksort(vec, 0, num - 1);
  print_vec(vec);

  return 0;
}
} // namespace

int main() {
  srandom(time(nullptr));
  return test();
}
