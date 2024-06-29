#pragma once

// 是否没有标准库
// 没有标准库你也需要提供一部分函数
#define NO_STD 1

// 忽略非法的参数 (定义即开启)
#define STD_SAFE_API // 调用标准库函数时检查参数
#define SAFE_API     // 调用本库的函数时检查参数

// 是否启用快速的色彩空间变换等
#define FAST_COLOR_TRANSFORM 1

#define OSAPI_MALLOC 1 // 是否支持 malloc 函数
#define OSAPI_PALLOC 0 // 是否支持 palloc 函数

#define OSAPI_SHM 0 // 是否支持共享内存

// 其实你可以做一个只有内核且只有一个进程的 OS (
#define OSAPI_MP 0 // 是否支持多进程
#define OSAPI_MT 0 // 是否支持多线程
