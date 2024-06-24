#include <cstdint>
#include <iostream>

template <typename T>
auto gcd(T a, T b) -> T {
  while (b != 0) {
    T t = b;
    b   = a % b;
    a   = t;
  }
  return a;
}

template <typename T>
auto lcm(T a, T b) -> T {
  return a / gcd(a, b) * b;
}

auto main() -> int {
  uint64_t a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b) << ' ' << lcm(a, b) << std::endl;
  return 0;
}
