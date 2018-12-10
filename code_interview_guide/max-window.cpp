/**
* @file max-window.cpp
* @brief
* @version 1.0
* @date 12/10/2018 12:44:53 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <iostream>
#include <vector>
#include <list>

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
  auto const ret = get_max_window(A, sizeof(A) / sizeof(A[0]), 3);

  for (auto const &it: A) {
    std::cout << it << ' ';
  }
  std::cout << std::endl;

  for (auto i = 0; i < 2; ++i) {
    std::cout << "  ";
  }
  for (auto const &it: ret) {
    std::cout << it << ' ';
  }
  std::cout << std::endl;
  return 0;
}

