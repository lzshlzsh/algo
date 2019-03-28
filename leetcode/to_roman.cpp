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

  int romanToInt(string s) {
    int num = 0;
    auto len = s.length();

    for (auto i = 0; i < len; ) {
      switch (s[i]) {
        case 'I': {
          if (i < len-1 && (s[i+1] == 'V' || s[i+1] == 'X')) {
            if (s[i+1] == 'V') {
              num += 4;
            } else {
              num += 9;
            }
            i += 2;
          } else {
            num += 1;
            i++;
          }
          break;
        }
        case 'V': {
          num += 5;
          i++;
          break;
        }
        case 'X': {
          if (i < len-1 && (s[i+1] == 'L' || s[i+1] == 'C')) {
            if (s[i+1] == 'L') {
              num += 40;
            } else {
              num += 90;
            }
            i += 2;
          } else {
            num += 10;
            i++;
          }
          break;
        }
        case 'L': {
          num += 50;
          i++;
          break;
        }
        case 'C': {
          if (i < len-1 && (s[i+1] == 'D' || s[i+1] == 'M')) {
            if (s[i+1] == 'D') {
              num += 400;
            } else {
              num += 900;
            }
            i += 2;
          } else {
            num += 100;
            i++;
          }
          break;
        }
        case 'D': {
          num += 500;
          i++;
          break;
        }
        case 'M': {
          num += 1000;
          i++;
          break;
        }
      }
    }
    return num;
  }
};
} // namespace

int main(int argc, char **argv) {
  int i = 4;
  Solution sol;

  if (argc >= 2) {
    i = atoi(argv[1]);
  }
  
  auto const str = sol.intToRoman(i);
  std::cout << i << " -> " << str << std::endl;
  std::cout << str << " -> " << sol.romanToInt(str) << std::endl;
  return 0;
}
