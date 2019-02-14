/**
 * @file longest_palindrom.cpp
 * @brief
 * @version 1.0
 * @date 02/09/2019 11:03:25 AM
 * @author lzshlzsh,lzshlzsh@163.com
 * @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
 */

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
 public:

  const std::string preprocess(const std::string &s) {
    // 预处理，把"babad"处理成"^#b#a#b#a#d#$"
    if (s.empty()) {
      return "^$";
    }
    std::string ret = "^#";
    for (auto i = 0; i < s.length(); ++i) {
      ret += s.substr(i, 1) + "#";
    }
    ret += "$";

    return ret;
  }

  /**
   * @brief 
   * 参考：https://articles.leetcode.com/longest-palindromic-substring-part-ii/
   * @param[in] s
   * @return
   */
  const std::string manacher_algorithm(const std::string &s) {
    auto const t = preprocess(s);
    std::vector<int> p;
    auto c = 0, r = 0;

    p.resize(t.length(), 0);

    for (auto i = 1; i < t.length() - 1; ++i) {
      auto const i_mirror = 2*c - i; // i - c == c - i_mirror
      
      p[i] = (r > i) ? std::min(p[i_mirror], r - i) : 0;

      // 扩充p[i]
      while (t[i + p[i] + 1] == t[i - p[i] - 1]) {
        p[i]++;
      }
      
      // 扩充r
      if (i + p[i] > r) {
        c = i;
        r = i + p[i];
      }
    }

    auto max_c = 0, max_p = 0;
    for (auto i = 1; i < t.length(); ++i) {
      if (p[i] > max_p) {
        max_c = i;
        max_p = p[i];
      }
    }

    return s.substr((max_c - max_p - 1) / 2, max_p);
  }

  std::string longestPalindrome(std::string s) {
    return manacher_algorithm(s);
  }
};

int main(int argc, char **argv) {
  Solution solution;
  const char *s = "babad";

  if (argc >= 2) {
    s = argv[1];
  }

  std::cout << s << std::endl;
  std::cout << solution.longestPalindrome(s) << std::endl;

  return 0;
}
