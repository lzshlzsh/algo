/**
* @file reverse_integer.cpp
* @brief
* @version 1.0
* @date 03/06/2019 11:26:03 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <stdlib.h>
#include <stdint.h>

#include <iostream>

namespace {
class Solution {
 public:
  int reverse(int x) {
    auto const sign = (x >= 0 ? 1 : -1);
    uint64_t xx = (x >= 0 ? x : static_cast<uint64_t>(-1LL * x));

    const uint64_t MIN_ABS = (1ULL << 31);
    const uint64_t MAX_ABS = (1ULL << 31) - 1;

    uint64_t y = 0;
    while (xx) {
      y = (y * 10) + (xx % 10);
      xx /= 10;
    }
    if ((sign == 1 && y > MAX_ABS) ||
        (sign == -1 && y > MIN_ABS)) {
      return 0;
    }

    return static_cast<int>(y * sign);
  }
};
} // namespace

int main(int argc, char **argv) {
  int i = -123;
  Solution s;

  if (argc >= 2) {
    i = strtol(argv[1], nullptr, 0);
  }

  std::cout << i << std::endl;
  std::cout << s.reverse(i) << std::endl;

  return 0;
}
