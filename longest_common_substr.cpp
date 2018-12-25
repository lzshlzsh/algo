/**
* @file longest_common_substr.cpp
* @brief
* @version 1.0
* @date 12/25/2018 09:16:51 AM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <time.h>

#include <iostream>
#include <vector>

#include "string_common.h"

using namespace common;
namespace {

int lc_substr(const std::string &str1, const std::string &str2) {
  auto const len1 = str1.length();
  auto const len2 = str2.length();
  std::vector<std::vector<int>> lc;
  int lc_max = 0;
  size_t pos = 0;
  
  lc.resize(len1);
  for (auto &it: lc) {
    it.resize(len2);
  }

  for (auto i = 0; i < len1; ++i) {
    for (auto j = 0; j < len2; ++j) {
      if (i == 0 || j == 0) {
        lc[i][j] = 0;
      } else if (str1[i-1] == str2[j-1]) {
        lc[i][j] = lc[i-1][j-1] + 1;
        if (lc[i][j] > lc_max) {
          lc_max = lc[i][j];
          pos = i-1;
        }
      } else {
        lc[i][j] = 0;
      }
    }
  }

  std::cout << lc_max << ':' << str1.substr(pos - lc_max + 1, lc_max)
    << std::endl;

  return 0;
}

int run(const size_t len) {
  std::string str, str2;

  srandom(time(nullptr));
  random_str(str, len); 
  random_str(str2, len); 

  std::cout << str << std::endl;
  std::cout << str2 << std::endl;
 
  lc_substr(str, str2);
  return 0;
} 


} // namespace

int main(int argc, char **argv) {
  size_t len = 16;

  if (argc >= 2) {
    len = atoi(argv[1]);
  }

  run(len);

  return 0;
}


