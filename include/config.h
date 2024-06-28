#pragma once

// 该项表示没有标准库
#define NO_STD 1 // 该项必须定义为 0 或 1 不能不定义

#define STD_SAFE_API // 调用标准库函数时检查参数
#define SAFE_API     // 调用本库的函数时检查参数

// 是否启用快速的色彩空间变换等
#define FAST_COLOR_TRANSFORM 1
