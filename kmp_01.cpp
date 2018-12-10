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
#include <string>

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

  int run(const std::string &file, const std::string &pattern) {
    std::string line;
    if (pattern.empty()) {
      std::cout << "null pattern" << std::endl;
      return -1;
    }

    compute_prefix_f(pattern);

    ifstream_.open(file.c_str());
    while (std::getline(ifstream_, line)) {
      lineno_++;
      //std::cout << lineno_ << " " << line << std::endl;
      find_str(line, pattern);
    }

    return 0;
  }
 protected:
 private:
  uint32_t lineno_;
  std::vector<int> prefix_f_;
  std::ifstream ifstream_;

  int compute_prefix_f(const std::string &pattern) {
    int k = -1;
    prefix_f_.resize(pattern.length(), -1);

    for (auto i = 1; i < pattern.length(); ++i) {
      while(k >= 0 && pattern[k+1] != pattern[i]) {
        k = prefix_f_[k];
      }
      if (pattern[k+1] == pattern[i]) {
        k++;
      }
      prefix_f_[i] = k;
    }

    return 0;
  }
  int find_str(const std::string &line, const std::string &pattern) {
    int k = -1;
    for (auto i = 0; i < line.length(); ++i) {
      while (k >= 0 && pattern[k+1] != line[i]) {
        k = prefix_f_[k];
      }
      if (pattern[k+1] == line[i]) {
        k++;
      }
      if (k == pattern.length() - 1) {
        std::cout << "find " << pattern << " at line " << lineno_
          << " column " << i + 1 - pattern.length() + 1 << std::endl;
        k = prefix_f_[k];
      }
    }
    return 0;
  }
};


}

int main(int argc, char **argv) {
  Kmp kmp;
  const char *pattern = "sammieliu";
  if (argc > 1) {
    pattern = argv[1];
  }
  return kmp.run("kmp_01.cpp", pattern);
}

