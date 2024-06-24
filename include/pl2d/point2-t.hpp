#define _Point(_name, _type)                                                                       \
  struct _name {                                                                                   \
    _type x, y;                                                                                    \
                                                                                                   \
    auto operator+(const _name &p) const -> _name {                                                \
      return {x + p.x, y + p.y};                                                                   \
    }                                                                                              \
    auto operator+(_type d) const -> _name {                                                       \
      return {x + d, y + d};                                                                       \
    }                                                                                              \
    auto operator-(const _name &p) const -> _name {                                                \
      return {x - p.x, y - p.y};                                                                   \
    }                                                                                              \
    auto operator-(_type d) const -> _name {                                                       \
      return {x - d, y - d};                                                                       \
    }                                                                                              \
    auto operator*(const _name &p) const -> _name {                                                \
      return {x * p.x, y * p.y};                                                                   \
    }                                                                                              \
    auto operator*(_type s) const -> _name {                                                       \
      return {x * s, y * s};                                                                       \
    }                                                                                              \
    auto operator/(const _name &p) const -> _name {                                                \
      return {x / p.x, y / p.y};                                                                   \
    }                                                                                              \
    auto operator/(_type s) const -> _name {                                                       \
      return {x / s, y / s};                                                                       \
    }                                                                                              \
                                                                                                   \
    auto operator+=(const _name &p) -> _name & {                                                   \
      x += p.x;                                                                                    \
      y += p.y;                                                                                    \
      return *this;                                                                                \
    }                                                                                              \
    auto operator+=(_type d) -> _name & {                                                          \
      x += d;                                                                                      \
      y += d;                                                                                      \
      return *this;                                                                                \
    }                                                                                              \
    auto operator-=(const _name &p) -> _name & {                                                   \
      x -= p.x;                                                                                    \
      y -= p.y;                                                                                    \
      return *this;                                                                                \
    }                                                                                              \
    auto operator-=(_type d) -> _name & {                                                          \
      x -= d;                                                                                      \
      y -= d;                                                                                      \
      return *this;                                                                                \
    }                                                                                              \
    auto operator*=(const _name &p) -> _name & {                                                   \
      x *= p.x;                                                                                    \
      y *= p.y;                                                                                    \
      return *this;                                                                                \
    }                                                                                              \
    auto operator*=(_type s) -> _name & {                                                          \
      x *= s;                                                                                      \
      y *= s;                                                                                      \
      return *this;                                                                                \
    }                                                                                              \
    auto operator/=(const _name &p) -> _name & {                                                   \
      x /= p.x;                                                                                    \
      y /= p.y;                                                                                    \
      return *this;                                                                                \
    }                                                                                              \
    auto operator/=(_type s) -> _name & {                                                          \
      x /= s;                                                                                      \
      y /= s;                                                                                      \
      return *this;                                                                                \
    }                                                                                              \
                                                                                                   \
    auto dot(const _name &p) const -> _type {                                                      \
      return x * p.x + y * p.y;                                                                    \
    }                                                                                              \
                                                                                                   \
    auto mod() const -> _type {                                                                    \
      return cpp::sqrt(x * x + y * y);                                                             \
    }                                                                                              \
                                                                                                   \
    auto trans(const Matrix2 &m) const -> _name {                                                  \
      _type _x = m.xx * x + m.yx * y + m.dx;                                                       \
      _type _y = m.xy * x + m.yy * y + m.dy;                                                       \
      return _name{_x, _y};                                                                        \
    }                                                                                              \
                                                                                                   \
    auto apply(const Matrix2 &m) -> _name & {                                                      \
      _type _x = m.xx * x + m.yx * y + m.dx;                                                       \
      _type _y = m.xy * x + m.yy * y + m.dy;                                                       \
      x        = _x;                                                                               \
      y        = _y;                                                                               \
      return *this;                                                                                \
    }                                                                                              \
                                                                                                   \
    auto operator*(const Matrix2 &m) const -> _name {                                              \
      return trans(m);                                                                             \
    }                                                                                              \
    friend auto operator*(const Matrix2 &m, const _name &p) -> _name {                             \
      return p.trans(m);                                                                           \
    }                                                                                              \
    auto operator*=(const Matrix2 &m) -> _name {                                                   \
      return apply(m);                                                                             \
    }                                                                                              \
  };
