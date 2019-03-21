/**
* @file rege_match.cpp
* @brief
* @version 1.0
* @date 03/13/2019 01:01:45 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <limits.h>
#include <string.h>

#include <string>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

namespace {
class Solution {
 public:
  Solution() {
    auto i = 1;
    op_priority_map_.emplace('(', std::make_pair(INT_MIN, 0));
    op_priority_map_.emplace(')', std::make_pair(INT_MIN, 0));
    op_priority_map_.emplace('|', std::make_pair(i++, 1));
    op_priority_map_.emplace('-', std::make_pair(i++, 1));
    op_priority_map_.emplace('*', std::make_pair(i++, 2));
    op_priority_map_.emplace('$', std::make_pair(INT_MIN, 0)); // 结尾符号
  }

  bool isMatch(string s, string p) {
    return dp_algo(s, p);
  }

  bool recursive_algo(const std::string &s, const std::string &p) {
    auto const s_len = s.length();
    auto const p_len = p.length();

    //    std::cout << s << '|' << p << std::endl;

    auto i = 0;
    auto j = 0;
    for (; i < p_len && j < s_len; ++i, ++j) {
      // pi: x*
      // sj: xxxxx
      // 递归匹配x*
      if (i+1 < p_len && p[i+1] == '*') {
        for (auto k = j; k < s_len+1; ++k) {
          if (k > j && p[i] != '.' && s[k-1] != p[i]) {
            return false;
          }
          if (recursive_algo(s.substr(k), p.substr(i+2))) {
            return true;
          }
        }
        return false;
      }

      if (p[i] != '.' && p[i] != s[j]) {
        return false;
      }
    }
    // 匹配空字符串
    for (; i+1 < p_len && p[i+1] == '*'; i += 2);

    return (i >= p_len && j >= s_len);
  }

  bool dp_algo(const std::string &s, const std::string &p) {
    auto const s_len = s.length();
    auto const p_len = p.length();

    // f[i][j]表示s[0:i-1]与p[0:j-1]是否匹配，是取值1，否取值0
    int f[s_len+1][p_len+1];
    memset(f, 0, sizeof(f));
    f[0][0] = 1;

    // s[0:i-1]: xxxY
    // p[0:j-1]: xxx*
    // f[i][j] = 
    // 1. f[i-1][j-1] && s[i-1] ~= p[j-1], 当p[j-1] != '*'
    // 2. (f[i-1][j] && s[i-1] ~= p[j-2]) || f[i][j-2], 当p[j-1] == '*'
    for (auto i = 0; i < s_len+1; ++i) {
        for (auto j = 1; j < p_len+1; ++j) {
            f[i][j] = (p[j-1] == '*' && j >= 2 && 
                       (f[i][j-2] || (i >= 1 && f[i-1][j] &&
                                      (p[j-2] == '.' || s[i-1] == p[j-2])))) ||
              (i >= 1 && f[i-1][j-1] && (p[j-1] == '.' || s[i-1] == p[j-1]));
        }
    }

    return f[s_len][p_len];
  }

  bool compiler_algo(const std::string &s, const std::string &p) {
    build_suffix_expr(p);
    return true;
  }

 private:
  // 操作符 -> <优先级，是否输出1/直接输出2>
  // '(', )'都算作操作符
  using OpPriorityMap = std::unordered_map<char, std::pair<int, int>>;

  std::string suffix_expr_;
  OpPriorityMap op_priority_map_;

  int build_suffix_expr(const std::string &p) {
    std::stack<OpPriorityMap::const_iterator> stack;

    suffix_expr_.clear();
    auto const p_suffix = p + "$";
    auto const len = p_suffix.length();
    for (auto i = 0; i < len; ++i) {
      auto c = p_suffix[i];

      for (; ;) {
        auto it = op_priority_map_.find(c);
        if (op_priority_map_.end() != it && it->second.second != 2) {
          while (!stack.empty()) {
            auto op_pri = stack.top();
            if (op_pri->second.first < it->second.first) {
              break;
            }
            if (op_pri->second.second) {
              suffix_expr_.push_back(op_pri->first);
            }
            stack.pop();
          }
          stack.emplace(it);
          break;
        } else {
          suffix_expr_.push_back(c);
          if (i + 1 < len && op_priority_map_.count(p_suffix[i+1]) == 0) {
            // ab中间插入连字符
            c = '-';
          } else {
            break;
          }
        }
      }
    }

    while (!stack.empty()) {
      auto op_pri = stack.top();
      if (op_pri->second.second) {
        suffix_expr_.push_back(op_pri->first);
      }
      stack.pop();
    }

    std::cout << suffix_expr_ << std::endl;
    return 0; 
  }
};

} // namespace

int main(int argc, char **argv) {
  const char *p = "c*a*b";
  const char *s = "aab";

  if (argc >= 2) {
    s = argv[1];
  }
  if (argc >= 3) {
    p = argv[2];
  }

  Solution sol;

  std::cout << "s: " << s << std::endl; 
  std::cout << "p: " << p << std::endl; 
//  std::cout << (sol.compiler_algo(s, p) ? "true" : "false") << std::endl;
  std::cout << (sol.recursive_algo(s, p) ? "true" : "false") << std::endl;
  std::cout << (sol.dp_algo(s, p) ? "true" : "false") << std::endl;

  return 0; 
}
