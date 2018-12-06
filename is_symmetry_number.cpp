/**
* @file is_symmetry_number.cpp
* @brief
* @version 1.0
* @date 12/06/2018 01:12:29 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <iostream>

int is_symmetry_number(const int num) {
  auto pos_num = (num >= 0) ? num : -num;
  int A[16] = {0};
  int i = 0;
  
  A[0] = pos_num % 10;
  for (; pos_num /= 10; ) {
    A[++i] = pos_num % 10;
  }

  for (int left = 0, right = i; left <= right; left++, right--) {
    if (A[left] != A[right]) {
      return 0;
    }
  }
  return 1;
}

int main() {
  std::cout << is_symmetry_number(1234321) << std::endl;
  std::cout << is_symmetry_number(1234341) << std::endl;
  std::cout << is_symmetry_number(12344321) << std::endl;

  return 0;
}

