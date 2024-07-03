
# 内存分配

```c
void *malloc(size_t size);
void  free(void *ptr);
void *palloc(size_t size);
void  pfree(void *ptr);
```

在 `malloc/free` 与 `palloc/pfree` 中必须实现一对

`malloc` 用于通用的内存分配，`palloc` 用于分配整个内存页（内存页大小设置在宏 `PAGE_SIZE` 中）

返回的内存地址均没有对齐要求

`free` 与 `pfree` 需保证传入为 `null` 时的安全
