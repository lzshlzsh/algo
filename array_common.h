/**
* @file array_common.h
* @brief
* @version 1.0
* @date 01/31/2019 09:04:19 AM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#ifndef  ARRAY_COMMON_H_
#define  ARRAY_COMMON_H_

#include <stdlib.h>

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>

namespace common {

static inline int *build_array_random(const size_t len) {
  if (len <= 0) {
    return nullptr;
  }
  auto array = new int[len];
  for (auto i = 0; i < len; ++i) {
    array[i] = random() % (5 * len);
  }
  return array;
}

static inline void free_array(int *array) {
  if (!array) {
    return;
  }
  delete []array;
}

template <typename T>
void print_array(const T &array, const size_t len) {
  for (auto i = 0; i < len; ++i) {
    std::cout << std::setfill(' ') << std::setw(5) << array[i];
  }

  std::cout << std::endl;
}

static inline std::vector<int> build_vector_random(const size_t len) {
  std::vector<int> array;

  if (len <= 0) {
    return array;
  }
  array.reserve(len);

  for (auto i = 0; i < len; ++i) {
    array[i] = random() % (5 * len);
  }
  return array;
}

} // namespace common
#endif

