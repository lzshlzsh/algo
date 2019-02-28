/**
* @file z_print.cpp
* @brief
* @version 1.0
* @date 02/28/2019 09:32:59 AM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/

#include <stdlib.h>

#include <iostream>

using namespace std;

namespace {
class Solution {
 public:
  string convert(string s, int numRows) {
    if (numRows <= 1 || s.empty()) {
      return s;
    }
    auto const len = s.length();
    char buf[len+1];
    auto k = 0;
    for (auto i = 0; i < numRows; ++i) {
      for (auto j = 0; ; j += 2) {
        auto pos = j * (numRows - 1);

        if (j && i && (i != (numRows - 1)) && pos-i < len) {
          buf[k++] = s[pos-i];
        }
        if (pos+i < len) {
          buf[k++] = s[pos+i];
        } else {
          break;
        }
      }
    }
    buf[k] = '\0';
    return buf;
  }
};

} // namespace

int main(int argc, char **argv) {
  std::string s = "LEETCODEISHIRING";
  auto num_rows = 3;
 
  if (argc >= 2) {
    s = argv[1];
  }
  if (argc >= 3) {
    num_rows = atoi(argv[2]);
  }

  Solution sol;
  
  std::cout << sol.convert(s, num_rows) << std::endl;
  return 0;
}
