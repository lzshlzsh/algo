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

#include "string_common.h"

using namespace common;
namespace {

int run(const size_t len) {
  std::string str, str2;

  srandom(time(nullptr));
  random_str(str, len); 
  random_str(str2, len); 

  std::cout << str << std::endl;
  std::cout << str2 << std::endl;
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


