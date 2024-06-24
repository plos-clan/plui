#define NO_STD 0
#include <c.h>
#include <cpp.hpp>
#include <define.h>
#include <osapi.h>
#include <type.hpp>

namespace cpp {

template <typename T>
class BaseString;

template <typename T>
class BaseStringIterator {
public:
  using Type = BaseString<T>;

  Type  &s;
  size_t i;

  auto index() -> size_t {
    return i;
  }

  auto operator<=>(const BaseStringIterator &it) {
    return i - it.i;
  }

  auto operator=(size_t i) {
    this->i = i;
  }
};

template <typename T>
class BaseString {
public:
  using It = BaseStringIterator<T>;

  T     *data = null;
  size_t pos  = 0;
  size_t len  = 0;

  BaseString() = default;

  BaseString(const T *str) {
    if (str == null) return;
    len  = strlen(str);
    data = _rc_alloc(T, len + 1);
    strcpy(data, str);
  }

  BaseString(const T *str, size_t len) {
    if (str == null || len == 0) return;
    this->len = len;
    data      = _rc_alloc(T, len + 1);
    strncpy(data, str, len);
  }

  BaseString(const BaseString &s) noexcept : data(s.data), pos(s.pos), len(s.len) {
    _rc_ref(data);
  }

  BaseString(BaseString &&s) noexcept : data(s.data), pos(s.pos), len(s.len) {
    s.data = null;
    s.pos  = 0;
    s.len  = 0;
  }

  ~BaseString() {
    _rc_unref(data);
  }

  auto operator=(const BaseString &s) -> BaseString & {
    if (this == &s) return *this;
    _rc_unref(data);
    data = s.data;
    pos  = s.pos;
    len  = s.len;
    _rc_ref(data);
    return *this;
  }

  auto operator=(BaseString &&s) noexcept -> BaseString & {
    if (this == &s) return *this;
    _rc_unref(data);
    data   = s.data;
    pos    = s.pos;
    len    = s.len;
    s.data = null;
    s.pos  = 0;
    s.len  = 0;
    return *this;
  }

  auto begin() {}

  auto end() {}

  auto size() const -> size_t {
    return len;
  }

  auto length() const -> size_t {
    return len;
  }

  auto c_str() -> T * {
    if (_rc_refcnt(data) > 1) {
      _rc_unref(data);
      T *p = _rc_alloc(T, len + 1);
      strncpy(p, data + pos, len);
      data = p;
      pos  = 0;
    }
    return data;
  }

  auto copy_as_cstr() const -> T * {
    T *s = malloc((len + 1) * sizeof(T));
    if (s == null) return null;
    strncpy(s, data + pos, len);
    return s;
  }

  auto operator[](size_t i) const -> char {
    return data[pos + i];
  }

  auto operator()(size_t i) -> char & {
    if (_rc_refcnt(data) > 1) {
      _rc_unref(data);
      T *p = _rc_alloc(T, len + 1);
      strncpy(p, data + pos, len);
      data = p;
      pos  = 0;
    }
    return data[i];
  }

  auto at(size_t i) const -> char {
    if (i >= len) return 0;
    return data[pos + i];
  }

  auto refat(size_t i) -> char & {
    if (_rc_refcnt(data) > 1) {
      _rc_unref(data);
      T *p = _rc_alloc(T, len + 1);
      strncpy(p, data + pos, len);
      data = p;
      pos  = 0;
    }
    if (i >= len) return data[len];
    return data[i];
  }

  auto substr(size_t start) const -> BaseString && {
    if (start >= len) return BaseString();
    _rc_ref(data);
    return BaseString{data, pos + start, len - start};
  }

  auto substr(size_t start, size_t length) const -> BaseString && {
    if (start >= len) return BaseString();
    length = cpp::min(length, len - start);
    _rc_ref(data);
    return BaseString{data, pos + start, length};
  }

  auto sub(size_t start) const -> BaseString && {
    return substr(start);
  }

  auto sub(size_t start, size_t length) const -> BaseString && {
    return substr(start, length);
  }

  auto repeat(size_t times) const -> BaseString && {
    if (data == null || times == 0) return BaseString();
    T *p = _rc_alloc(T, len * times + 1);
    for (size_t i = 0; i < times; i++) {
      memcpy(p + i * len, data + pos, len);
    }
    p[len * times] = 0;
    return BaseString{p, 0, len * times + 1};
  }
};

using String = BaseString<char>;

} // namespace cpp

#include <gtest/gtest.h>

using String = cpp::String;

// 测试构造函数和基本功能
TEST(BaseStringTest, ConstructorAndBasicFunctions) {
  String str1("Hello");
  EXPECT_EQ(str1.size(), 5);
  EXPECT_STREQ(str1.c_str(), "Hello");

  String str2("World", 3);
  EXPECT_EQ(str2.size(), 3);
  EXPECT_STREQ(str2.c_str(), "Wor");

  String str3;
  EXPECT_EQ(str3.size(), 0);
  EXPECT_EQ(str3.c_str(), nullptr);
}

// 测试拷贝构造函数
TEST(BaseStringTest, CopyConstructor) {
  String str1("Hello");
  String str2(str1);

  EXPECT_EQ(str2.size(), 5);
  EXPECT_STREQ(str2.c_str(), "Hello");
}

// 测试移动构造函数
TEST(BaseStringTest, MoveConstructor) {
  String str1("Hello");
  String str2(std::move(str1));

  EXPECT_EQ(str1.size(), 0); // 移动后原对象应为空
  EXPECT_EQ(str1.c_str(), nullptr);
  EXPECT_EQ(str2.size(), 5);
  EXPECT_STREQ(str2.c_str(), "Hello");
}

// 测试拷贝赋值运算符
TEST(BaseStringTest, CopyAssignmentOperator) {
  String str1("Hello");
  String str2;
  str2 = str1;

  EXPECT_EQ(str2.size(), 5);
  EXPECT_STREQ(str2.c_str(), "Hello");
}

// 测试移动赋值运算符
TEST(BaseStringTest, MoveAssignmentOperator) {
  String str1("Hello");
  String str2;
  str2 = std::move(str1);

  EXPECT_EQ(str1.size(), 0); // 移动后原对象应为空
  EXPECT_EQ(str1.c_str(), nullptr);
  EXPECT_EQ(str2.size(), 5);
  EXPECT_STREQ(str2.c_str(), "Hello");
}

// 测试下标访问
TEST(BaseStringTest, SubscriptOperator) {
  String str("Hello");

  EXPECT_EQ(str[0], 'H');
  EXPECT_EQ(str[1], 'e');
  EXPECT_EQ(str[4], 'o');

  str(1) = 'a';
  EXPECT_EQ(str[1], 'a');
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
