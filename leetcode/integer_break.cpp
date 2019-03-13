/**
* @file integer_break.cpp
* @brief
* @version 1.0
* @date 03/07/2019 09:08:27 AM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <stdlib.h>

#include <iostream>
#include <algorithm>

namespace {
class Solution {
 public:
  /**
   * f(n) = max{f(i)*j, f(i)*f(j), i*j, i*f(j) | i+j=n} =
   * max{max(f(i), i) * max(f(j), j) | i+j=n}
   */
  int dp_algo(const int n) {
    int f[n + 1];

    f[0] = 0;
    f[1] = 0;
    f[2] = 1;

    for (auto k = 3; k <= n; ++k) {
      f[k] = 0;
      for (auto i = 1; i <= k/2; ++i) {
        auto const j = k - i;
        f[k] = std::max(std::max(f[i], i) * std::max(f[j], j), f[k]);
      }
    }

    return f[n];
  }
  int math_algo(const int n) {
    int ret = 1;

    if (2 == n) {
      return 1;
    }
    if (3 == n) {
      return 2;
    }

    for (auto i = n; i; ) {
      switch (i) {
        case 2: 
        case 4: {
          ret *= 2;
          i -= 2;
          break;
        }
        case 3: 
        case 5: 
        default: {
          ret *= 3;
          i -= 3;
          break;
        }
      }
    }

    return ret;
  }

  int integerBreak(int n) {
    return math_algo(n);
  }
};
} // namespace

int main(int argc, char **argv) {
  Solution s;
  int n = 10;

  if (argc >=2 ) {
    n = strtol(argv[1], nullptr, 0);
  }
  if (!(n >= 2 && n <= 58)) {
    std::cout << "n should be between [" << 2 << "," << 58 << "]" << std::endl;
    return 0;
  }
  std::cout << s.dp_algo(n) << std::endl;;
  std::cout << s.math_algo(n) << std::endl;;

  return 0;
}
