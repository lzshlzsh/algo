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

 public:
  /**
   * @brief 
   * 参考：https://articles.leetcode.com/longest-palindromic-substring-part-ii/
   * 时间复杂度：O(N)
   * 空间复杂度：O(N)
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

      // 扩充p[i]，隐含的扩充r，最多扩充N次
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

  /**
   * @brief
   * 动态规划算法
   * @param[in] s
   * @return
   */
  const std::string dynamic_programming_algo(const std::string &s) {
    auto const len = s.length();
    std::vector<std::vector<bool>> f;
   
    if (len == 0) {
      return "";
    } 

    f.resize(len);
    for (auto &it: f) {
      it.resize(len, false);
    }
    auto max_i = 0, max_len = 1;
    
    for (auto t = 0; t < len; ++t) {
      for (auto i = 0; (i + t) < len; ++i) {
        auto const j = i + t;
        if (j == i) {
          f[i][j] = true;
        } else if (j - i == 1) {
          f[i][j] = (s[i] == s[j]);
        } else {
          f[i][j] = (f[i + 1][j - 1] && s[i] == s[j]);
        }
//        if (f[i][j]) {
//          std::cout << "T: " << s.substr(i, j-i+1) << std::endl;
//        } else {
//          std::cout << "F: " << s.substr(i, j-i+1) << std::endl;
//        }
        if (f[i][j] && max_len < (j - i + 1)) {
          max_i = i;
          max_len = j - i + 1;
        }
      }
    }

    return s.substr(max_i, max_len);
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
  std::cout << solution.dynamic_programming_algo(s) << std::endl;

  return 0;
}
