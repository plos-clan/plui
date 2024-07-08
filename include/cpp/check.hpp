#pragma once

template <typename T, const T &(*GET)(), void (*SET)(const T &)>
class Property {
public:
  Property() = default;

  auto operator=(const T &val) -> Property & {
    return SET(val);
  }

  operator T &() {
    return GET();
  }
};

template <typename T, const T &(*GET)(const T &), void (*SET)(T &, const T &)>
class Checked {
private:
  T value;

public:
  Checked() = default;

  auto operator=(const T &val) -> Checked & {
    SET(value, val);
    return *this;
  }

  operator T &() {
    return GET(value);
  }
};
