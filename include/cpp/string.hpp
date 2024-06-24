#pragma once
#include <define.h>
#include <type.hpp>

namespace cpp {

#ifdef SAFE_API
auto utf8_to_32(const u8 *&s) -> u32 {
  u32 code;
  if (s[0] < 0x80) { // ASCII字符（单字节）
    code = *s++;
  } else if ((s[0] & 0xe0) == 0xc0) { // 2字节UTF-8字符
    if ((s[1] & 0xc0) != 0x80) goto err;
    code  = (*s++ & 0x1f) << 6;
    code |= (*s++ & 0x3f);
  } else if ((s[0] & 0xf0) == 0xe0) { // 3字节UTF-8字符
    if ((s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80) goto err;
    code  = (*s++ & 0x0F) << 12;
    code |= (*s++ & 0x3f) << 6;
    code |= (*s++ & 0x3f);
  } else if ((s[0] & 0xf8) == 0xf0) { // 4字节UTF-8字符
    if ((s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80 || (s[3] & 0xc0) != 0x80) goto err;
    code  = (*s++ & 0x07) << 18;
    code |= (*s++ & 0x3f) << 12;
    code |= (*s++ & 0x3f) << 6;
    code |= (*s++ & 0x3f);
  } else { // 非法的UTF-8序列
    goto err;
  }
  return code;

err:
  s++;
  return 0xfffd; // 跳过非法序列
}
#else
auto utf8_to_32(const u8 *&s) -> u32 {
  u32 code;
  if (*s < 0x80) { // ASCII字符（单字节）
    code = *s++;
  } else if ((*s & 0xe0) == 0xc0) { // 2字节UTF-8字符
    code  = (*s++ & 0x1f) << 6;
    code |= (*s++ & 0x3f);
  } else if ((*s & 0xf0) == 0xe0) { // 3字节UTF-8字符
    code  = (*s++ & 0x0F) << 12;
    code |= (*s++ & 0x3f) << 6;
    code |= (*s++ & 0x3f);
  } else if ((*s & 0xf8) == 0xf0) { // 4字节UTF-8字符
    code  = (*s++ & 0x07) << 18;
    code |= (*s++ & 0x3f) << 12;
    code |= (*s++ & 0x3f) << 6;
    code |= (*s++ & 0x3f);
  } else { // 非法的UTF-8字节，按单字节处理
    s++;
    return 0xfffd;
  }
  return code;
}
#endif

} // namespace cpp
