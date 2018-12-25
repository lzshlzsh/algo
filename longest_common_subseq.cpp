/**
* @file longest_common_subseq.cpp
* @brief
* @version 1.0
* @date 12/25/2018 09:16:45 AM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <time.h>

#include <iostream>
#include <vector>

#include "string_common.h"

using namespace common;
namespace {

enum {
  kNull = 0,
  kTopLeft = 1,
  kTop = 2,
  kLeft = 3,
};

int print_lc_subseq(
  const std::string &str1, const std::vector<std::vector<int>> &trace,
  const int i, const int j) {
 
  if (i == 0 || j == 0) {
    return 0;
  }

  if (trace[i][j] == kTopLeft) {
    print_lc_subseq(str1, trace, i-1, j-1);
    std::cout << str1[i-1];
  } else if (trace[i][j] == kTop) {
    print_lc_subseq(str1, trace, i-1, j);
  } else {
    print_lc_subseq(str1, trace, i, j-1);
  }

  return 0;
}

int lc_subseq(const std::string &str1, const std::string &str2) {
  std::vector<std::vector<int>> lc, trace;
  auto const len1 = str1.length();
  auto const len2 = str2.length();

  lc.resize(len1+1);
  trace.resize(len1+1);
  for (auto i = 0; i < len1+1; ++i) {
    lc[i].resize(len2+1);
    trace[i].resize(len2+1);
  }

  for (auto i = 0; i < len1+1; ++i) {
    for (auto j = 0; j < len2+1; ++j) {
      if (i == 0 || j == 0) {
        lc[i][j] = 0;
      } else if (str1[i-1] == str2[j-1]) {
        lc[i][j] = lc[i-1][j-1] + 1;
        trace[i][j] = kTopLeft;
      } else if (lc[i][j-1] >= lc[i-1][j]) {
        lc[i][j] = lc[i][j-1];
        trace[i][j] = kLeft;
      } else {
        lc[i][j] = lc[i-1][j];
        trace[i][j] = kTop;
      }
    }
  }

  std::cout << lc[len1][len2] << ':';
  print_lc_subseq(str1, trace, len1, len2);
  std::cout << std::endl;
  return 0;
}

int run(const size_t len) {
  std::string str, str2;

  srandom(time(nullptr));
  random_str(str, len); 
  random_str(str2, len); 

  std::cout << str << std::endl;
  std::cout << str2 << std::endl;

  lc_subseq(str, str2);
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

