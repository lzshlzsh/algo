/**
* @file atoi.cpp
* @brief
* @version 1.0
* @date 03/08/2019 09:46:01 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <limits.h>

#include <string>
#include <iostream>

using namespace std;

namespace {
class Solution {
 public:
  int myAtoi(string str) {
    int pos1 = -1;
    int pos2 = -1;
    int sign = 0;

    size_t i;
    for (i = 0; i < str.length(); ++i) {
      if (' ' == str[i]) {
        if (0 == sign && pos1 < 0) {
          continue;
        } else if (pos2 < 0) {
          pos2 = i;
        }
        break;
      } else if ('+' == str[i] || '-' == str[i]) {
        if (0 == sign) {
          sign = ('+' == str[i] ? 1 : -1);
          continue;
        } else if (pos2 < 0) {
          pos2 = i;
        }
        break;
      } else if (str[i] >= '0' && str[i] <= '9') {
        if (pos1 < 0) {
          pos1 = i;
          if (0 == sign) {
            sign = 1;
          }
        }
      } else {
        if (pos2 < 0) {
          pos2 = i;
        }
        break;
      }
    }
    if (i >= str.length() && pos2 < 0) {
      pos2 = str.length();
    }

    if (pos1 < 0 || pos2 < 0 || 0 == sign) {
      return 0;
    }
    for (; '0' == str[pos1]; ++pos1);
    if (pos1 >= pos2) {
      return 0;
    }

    int ret = 0;
    for (; pos1 < pos2; ++pos1) {
      const int cur = str[pos1] - '0';
      if (ret > INT_MAX/10 || (INT_MAX/10 == ret && cur > 7)) {
        return INT_MAX;
      }
      if (ret < INT_MIN/10 || (INT_MIN/10 == ret && cur > 8)) {
        return INT_MIN;
      }
      ret = ret * 10 + sign * cur;
    }

    return ret;
  }
};
} // namespace


int main(int argc, char **argv) {
  const char *str = "   -42";
  if (argc >= 2) {
    str = argv[1];
  }

  Solution s;

  std::cout << s.myAtoi(str) << std::endl;

  return 0;
}
