#include <define.h>
#include <type.h>

#if NO_STD == 0
#  include <cstdio>
#  include <cstdlib>
#  include <cstring>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if NO_STD

dlimport int printf(const char *_rest fmt, ...);

dlimport void *malloc(size_t size);
dlimport void  free(void *ptr);

dlimport int     open(cstr filename, int flags, int mode);
dlimport ssize_t read(int fd, void *buf, size_t n);
dlimport ssize_t write(int fd, const void *buf, size_t n);
dlimport ssize_t seek(int fd, ssize_t offset, int whence);
dlimport int     close(int fd);

// 返回当前进程的pid
dlimport int getpid();
// 返回0表示由内核唤醒，返回>0表示由用户进程唤醒，返回<0表示错误
dlimport int pause();
// 唤醒指定pid的进程，返回0表示成功，返回<0表示失败
dlimport int wakeup(int pid);

// shmalloc 返回资源描述符(rd) rd为大于等于0的整数
dlimport int shmalloc(size_t size);
dlimport int shmget(int rd, void *addr_p, size_t *size_p);
dlimport int shmfree(int rd);

#else

#endif

#ifdef __cplusplus
}
#endif
