/**
* @file max_nodec.cpp
* @brief
* @version 1.0
* @date 12/06/2018 07:44:14 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
  std::ifstream fs("./max_nondeac.input");
  int i;
  std::vector<int> v;
  std::vector<int> path;
  std::vector<std::pair<int, int>> f; // <i(index of v), f(i)>

  while (fs >> i) {
    v.emplace_back(i);
    std::cout << i << ' ';
  }
  std::cout << '\n';
  path.resize(v.size(), -1);

  for (i = 0; i < static_cast<int>(v.size()); ++i) {
    auto it = std::upper_bound(
      f.begin(), f.end(), v[i], [&v](
        const int val, const std::pair<int, int> &a) -> bool {
      return val < v[a.first];
      }); 
    if (f.end() == it) {
      if (f.empty()) {
        f.emplace_back(std::make_pair(i, 1));
      } else {
        path[i] = f.back().first;
        auto const len = f.back().second + 1;
        f.emplace_back(std::make_pair(i, len));
      }
    } else {
      it->first = i;
      if (f.begin() != it) {
        --it;
        path[i] = it->first;
      }
    }
  }

  std::cout << f.back().second << std::endl;
  for (i = f.back().first; -1 != i; i = path[i]) {
    std::cout << v[i] << ' ';
  }
  std::cout << std::endl;

  return 0;
}

