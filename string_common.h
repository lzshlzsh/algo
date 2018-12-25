/**
* @file string_common.h
* @brief
* @version 1.0
* @date 12/25/2018 09:21:27 AM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <stdlib.h>

#include <string>

namespace common {

static inline int random_str(std::string &str, const size_t len) {
  str.resize(len);

  char *c_str = const_cast<char *>(str.data());

  for (auto i = 0; i < len; ++i) {
    c_str[i] = 'a' + random() % 10;
  }
  return 0;
}


} // namespace common

