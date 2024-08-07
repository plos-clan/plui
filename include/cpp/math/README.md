
# C++ 实用函数：数学库

- `base.hpp`

  | 标识符      | 简介                           |
  |-------------|--------------------------------|
  | F32_EPSILON | 32位浮点数可以判断为相等的差值 |
  | F64_EPSILON | 64位浮点数可以判断为相等的差值 |
  | PI          | 常用常数                       |
  | E           | 常用常数                       |
  | SQRT2       | 根号 2                         |
  | PHI         | 黄金分割比 (1.618)             |

- `bits.hpp`

  | 标识符      | 简介                       |
  |-------------|----------------------------|
  | clz         | 二进制第一个 1 前 0 的个数 |
  | bit_reverse | 位逆序                     |

- `exp-log.hpp`

  | 标识符 | 简介            |
  |--------|-----------------|
  | exp2   | 2 的幂          |
  | exp    | e 的幂          |
  | log2   | 以 2 为底的对数 |
  | pow    | 幂              |

- `math.hpp`

  | 标识符    | 简介                              |
  |-----------|-----------------------------------|
  | diff      | 两个数的差（大减小）              |
  | equals    | 判断是否相等（浮点相近即相等）    |
  | min       | 最小值                            |
  | max       | 最大值                            |
  | clamp     | 将数据限制到 \[min,max\] 的范围内 |
  | abs       | 绝对值                            |
  | gcd       | 最大公约数                        |
  | lcm       | 最小公倍数                        |
  | mod       | 整除后的余数                      |
  | factorial | 阶乘                              |

- `sin.hpp`

  | 标识符 | 简介   |
  |--------|--------|
  | sin    | 正弦   |
  | cos    | 余弦   |
  | tan    | 正切   |
  | asin   | 逆正弦 |
  | acos   | 逆余弦 |
  | atan   | 逆正切 |
  | atan2  | 逆正切 |

- `sqrt.hpp`

  | 标识符 | 简介   |
  |--------|--------|
  | square | 平方   |
  | cube   | 立方   |
  | sqrt   | 平方根 |
  | cbrt   | 立方根 |

- `sum.hpp`

  | 标识符 | 简介   |
  |--------|--------|
  | sum    | 求和   |
  | avg    | 求平均 |
