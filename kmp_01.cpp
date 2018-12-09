/**
* @file kmp_01.cpp
* @brief
* @version 1.0
* @date 12/09/2018 09:07:11 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <iostream>
#include <fstream>
#include <vector>

namespace {
/**
 * @brief 
 * @class Kmp
 */
class Kmp
{
 public:
  /**
   * @brief
   */
  Kmp(): lineno_(0) {}

  int run(const std::string &pattern) {
    if (pattern.empty()) {
      std::cout << "null pattern" << std::endl;
      return -1;
    }

    ifstream_.open(pattern.c_str());

    return 0;
  }
 protected:
 private:
  uint32_t lineno_;
  std::vector<int> prefix_f_;
  std::ifstream ifstream_;
};


}

int main(int argc, char **argv) {
  Kmp kmp;
  const char *pattern = "sammieliu";
  if (argc > 1) {
    pattern = argv[1];
  }
  return kmp.run(pattern);
}

