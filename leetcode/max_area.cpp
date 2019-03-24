/**
* @file max_area.cpp
* @brief
* @version 1.0
* @date 03/24/2019 01:59:58 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

namespace {
class Solution {
 public:
  int maxArea(vector<int>& height) {
      auto const len = height.size();

      if (len <= 1) {
          return 0;
      }
      int f = 0;
      for (int i=0, j=len-1; i < j; ) {
          f = std::max(f, std::min(height[i], height[j]) * (j-i));
          if (height[i] < height[j]) {
              ++i;
          } else if (height[i] == height[j]) {
              ++i;
              --j;
          } else {
              --j;
          }
      }
      return f;
  }
};
} // namespace

int main(int argc, char **argv) {
    std::vector<int> height{1,8,6,2,5,4,8,3,7};
    
    Solution sol;
    std::cout << sol.maxArea(height) << std::endl;
    return 0;
}
