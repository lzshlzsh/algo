/**
* @file memorymove.cpp
* @brief
* @version 1.0
* @date 12/06/2018 12:26:00 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <iostream>
#include <string.h>

void my_memmove(char *p1, const char *p2, const size_t sz) {
//  memcpy(p1, p2, sz); // Oops
//  memmove(p1, p2, sz);
  if (p1 == p2) {
    return;
  }
  if (p1 < p2) {
    // copy from head
    auto const offset = p2 - p1;
    auto const batch_sz = (offset / 8) ? 8 :
      ((offset / 4) ? 4 :
       ((offset / 2) ? 2 : 1));
    int i = 0;
    switch (batch_sz) {
      case 8: {
        for (i = 0; (i+8) <= sz; i += 8) {
          *reinterpret_cast<uint64_t *>(p1+i) =
            *reinterpret_cast<const uint64_t *>(p2+i);
        }
        break;
      }
      case 4: {
        for (i = 0; (i+4) <= sz; i += 4) {
          *reinterpret_cast<uint32_t *>(p1+i) =
            *reinterpret_cast<const uint32_t *>(p2+i);
        }
      }
      case 2: {
        for (i = 0; (i+2) <= sz; i += 2) {
          *reinterpret_cast<uint16_t *>(p1+i) =
            *reinterpret_cast<const uint16_t *>(p2+i);
        }
      }
      default: {
        break;
      }
    }

    for (; i < sz; ++i) {
      *(p1+i) = *(p2+i);
    }
  } else {
    // copy from end
    auto const offset = p1 - p2;
    auto const batch_sz = (offset / 8) ? 8 :
      ((offset / 4) ? 4 :
       ((offset / 2) ? 2 : 1));
    int i = 0;
    switch (batch_sz) {
      case 8: {
        for (i = sz-8; (i-8) >= -1; i -= 8) {
          *reinterpret_cast<uint64_t *>(p1+i) =
            *reinterpret_cast<const uint64_t *>(p2+i);
        }
        break;
      }
      case 4: {
        for (i = sz-4; (i-4) >= -1; i -= 4) {
          *reinterpret_cast<uint32_t *>(p1+i) =
            *reinterpret_cast<const uint32_t *>(p2+i);
        }
      }
      case 2: {
        for (i = sz-2; (i-2) >= -1; i -= 2) {
          *reinterpret_cast<uint16_t *>(p1+i) =
            *reinterpret_cast<const uint16_t *>(p2+i);
        }
      }
      default: {
        break;
      }
    }

    for (; i >= 0; --i) {
      *(p1+i) = *(p2+i);
    }
  }
}

int main() {
  char str[] = "abcdefghi01234567890\0";

  std::cout << sizeof(str) << std::endl;

  my_memmove(str+1, str, sizeof(str) - 1);

  std::cout << str << std::endl;

  return 0;
}

