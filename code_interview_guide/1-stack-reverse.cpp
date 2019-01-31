/**
 * @file 1-stack-reverse.cpp
 * @brief
 * @version 1.0
 * @date 01/31/2019 12:20:48 AM
 * @author lzshlzsh,lzshlzsh@163.com
 * @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
 */
#include <stack>
#include <iostream>

namespace {

int get_and_remove_bottom(std::stack<int> &s) {
  auto const t = s.top();
  
  s.pop();
  if (s.empty()) {
    return t;
  }
  auto const b = get_and_remove_bottom(s);
  s.push(t);
  return b;
}

void reverse(std::stack<int> &s) {
  auto const b = get_and_remove_bottom(s);
  if (!s.empty()) {
    reverse(s);
  }
  s.push(b);
}

}

int main() {
  std::stack<int> s;

  for (auto i = 0; i < 5; ++i) {
    s.emplace(i);
  }

  reverse(s);

  std::cout << "top<";
  while (!s.empty()) {
    std::cout << s.top() << ',';
    s.pop();
  }
  std::cout << ">bottom\n";

  return 0;
}
