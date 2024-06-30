#pragma once
#include <define.h>
#include <type.h>

// 说明一下宏定义
// __THROW 表明函数不会抛出异常
// __wur 表明必须处理函数的返回值
// 使用这些宏定义是为了能够尽可能地兼容标准库
// 使与标准库头文件一起编译时不会报错

// 默认认为分页大小是 4k
// 如果是 2M 请调整为 2097152
#define PAGE_SIZE 4096

#if NO_STD == 0
#  include <cstdio>
#  include <cstdlib>
#  include <cstring>
#endif

#ifdef __cplusplus
extern "C" {
#endif

dlimport int printf(const char *_rest fmt, ...);

//* ----------------------------------------------------------------------------------------------------
//& 内存分配
// 为了高效地访问内存，建议 8 或 16 字节对齐
dlimport void *malloc(size_t size);
dlimport void  free(void *ptr);
#if NO_STD
#  if !OSAPI_MALLOC && !OSAPI_PALLOC
#    error "请至少支持 palloc 与 malloc 中的一项"
#  endif
//- 如果没有 malloc 就使用此库内置的 malloc
//- 但内置的 malloc 目前还没有完工
//- 没有 palloc 就使用 malloc, 定义在下方
#  if OSAPI_MALLOC && !OSAPI_PALLOC
finline void *palloc(size_t size) {
  return malloc(size);
}
finline void pfree(void *ptr) {
  free(ptr);
}
#  else
// 按页分配保证传入的 size 为 PAGE_SIZE 的整数倍
// 返回内存的对齐没有要求
dlimport void *palloc(size_t size);
dlimport void  pfree(void *ptr);
#  endif
#else
finline void *palloc(size_t size) {
  return valloc(size);
}
finline void pfree(void *ptr) {
  free(ptr);
}
#endif

#if !OSAPI_FILE_UNIX && !OSAPI_FILE_EASY
#  warning "建议至少支持一种文件读写方式"
#  define NO_FILE_API // 定义即不支持文件读写
#else
// 都必须支持的API
dlimport int     remove(cstr filename); //  删除文件
// 类unix的文件API
dlimport int     open(cstr filename, int flags, ...) __nonnull((1));
dlimport ssize_t read(int fd, void *buf, size_t n);
dlimport ssize_t write(int fd, const void *buf, size_t n);
dlimport ssize_t seek(int fd, ssize_t offset, int whence);
dlimport int     close(int fd);
// 简单的文件API（这是最简单的API了吧）
// 获取文件大小，如果没有这个函数就会用seek到末尾的方式来获取
dlimport ssize_t filesize(cstr filename);
dlimport void   *readfile(cstr filename, size_t *size_p);
dlimport int     writefile(cstr filename, const void *data, size_t size);
#endif

#if !NO_STD || OSAPI_MT
// 返回当前线程的tid
dlimport int gettid() __THROW;
#endif
#if !NO_STD || OSAPI_MP
// 返回当前进程的pid
dlimport int getpid() __THROW;
#endif

#if !NO_STD || OSAPI_MP || OSAPI_MT
// 返回进程号
// 返回0表示由内核唤醒，返回>0表示由用户进程唤醒，返回<0表示错误
dlimport int pause();
// 唤醒指定pid的进程，返回0表示成功，返回<0表示失败
dlimport int wakeup(int pid);
#endif

#if OSAPI_SHM
// shmalloc 返回资源描述符(rd) rd为大于等于0的整数
// 小于 0 表示错误
dlimport int shmalloc(size_t size);
dlimport int shmget(int rd, void *addr_p, size_t *size_p);
dlimport int shmfree(int rd);
#endif

#ifdef __cplusplus
}
#endif
