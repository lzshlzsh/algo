/**
* @file to_roman.cpp
* @brief
* @version 1.0
* @date 03/27/2019 09:02:57 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <iostream>
#include <string>

using namespace std;

namespace {
class Solution {
 public:
  string intToRoman(int num) {
    int num_array[13] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    const char *roman_array[13] = {
      "I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"
    };
    std::string roman;
   
    if (!(num >=1 && num <= 3999)) {
      return roman;
    }

    for (auto i = 12; i >= 0 && num; --i) {
      for (auto n = num / num_array[i]; n > 0; n--) {
        roman += roman_array[i];
      }
      num %= num_array[i]; 
    }

    return roman;
  }
};
} // namespace

int main(int argc, char **argv) {
  int i = 4;
  Solution sol;

  if (argc >= 2) {
    i = atoi(argv[1]);
  }

  std::cout << i << " -> " << sol.intToRoman(i) << std::endl;
  return 0;
}
