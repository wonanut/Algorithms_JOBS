# c/c++常用内存操作函数

## malloc, calloc和free

头文件：<stdlib.h>

- malloc用来进行内存分配，在堆上申请内存空间。如果分配成功返回被分配内存的指针，否则返回空。

```c++
// @size: 申请的内存大小, size_t是typedef重定义的类型，通常是整型相关数据类型的重定义
// header: malloc.h或stdlib.h
void *malloc(size_t size);

int *n;
n = (int*)malloc(sizeof(int));
```

- free用来完成内存释放。

```c++
void free(void *ptr);
```

- calloc在内存动态存储区分配n个长度为size的连续空间，成功返回一个指向分配起始地址的指针，失败返回NULL

```c++
void *calloc(size_t n, size_t size);
```

calloc在动态分配完内存后，自动初始化内存空间为0.malloc不初始化，里面数据是随机的垃圾数据。

## memset

头文件：<string.h>或<memory.h>

- 将s中的当前位置的后面n个字节用ch替换并返回s。（以字节为单位进行填充）
- 在一段内存块中填充某个给定的值，用来对较大结构体或数组进行初始化清零操作。

```c++
//@s: 首地址
//@ch: 每字节填充的数
//@n: 总字节数
void *memset(void *s, int c, size_t n)
{
    const unsigned char uc = c;  // 只截取后8位
    unsigned char *su;
    for(su = s; 0 < n; ++su, --n)
        *su =uc;
    return s;
}

// memset(arr, 0, n*sizeof(int));填充int数组的n个元素为0
// 这里的调用for循环执行4*n次，int占4字节
```

## memcpy和memmove

头文件：<string.h>

- memcpy实现

  实际上memcpy是一个高效的内存拷贝函数，内部实现只有在地址不对齐的时候memcpy才会一个字节一个字节拷贝内存，当地址对齐时，会使用CPU字长（32位或64位）来拷贝。

  ```c++
  // @dest:目的地址
  // @src:源地址
  // count: 需要拷贝的内存大小
  void * memcpy(void* dest, const void* src, size_t count)
  {
      assert(src != NULL && dest != NULL);
      char* tmp_dest = (char*)dest;
      const char* tmp_src = (const char*)src;  //使得每次均是对内存中一个字节的拷贝
      while(count--)
          *tmp_dest++ = *tmp_src++;
      return dest;
  }
  ```

- memmove实现

  ```c++
  // @dest:目的地址
  // @src:源地址
  // count: 需要拷贝的内存大小
  void* memmove(void* dest, const void* src, size_t count)
  {
  	assert(src != NULL && dest != NULL);
      char* tmp_dest = (char*)dest;
      const char* tmp_src = (const char*)src;
      
      if(tmp_src < tmp_dest && tmp_src + count > dest) {  
          //当src地址小于dest，且src+count地址高于dest时从后往前拷贝
          tmp_src += count - 1;
          tmp_dest += count - 1;
          while(count--) {
              *tmp_dest-- = *tmp_src--;
          }
  	} else {  // 其余情况都从前往后
          while(count--)
              *tmp_dest++ = *tmp_src++;
      }
      return dest;  //返回目的地址
  }
  ```

内存拷贝分为如下三种场景

1. 源和目的内存区域完全不重叠

   ![1](C:\Users\wuhui\Documents\GitHub\Algorithms_JOBS\编程语言\C和C++\figures\1.png)

2. 当源和目的内存区域重叠，且dst在src前

   ![2](C:\Users\wuhui\Documents\GitHub\Algorithms_JOBS\编程语言\C和C++\figures\2.jpg)

3. 当源和目的内存区域重叠，且dst在src后

   ![3](C:\Users\wuhui\Documents\GitHub\Algorithms_JOBS\编程语言\C和C++\figures\3.jpg)

   对于场景1和2，memcpy都可以正常完成拷贝工作，但场景3memcpy会出错，因为src的第4和5块内容被dst拷贝后的内容覆盖。memmove对场景3进行拷贝时，会从src的最后向前拷贝，反向拷贝可以避免出错。

## strcpy

<string.h>

- strcpy实现：将src指向的以'\0'结尾的字符串拷贝到dest指向的位置。
- 说明：src和dest所指向的地址不可以重叠，且dest必须有足够的空间来存储src。

```c++
// @dest: 目的字符串地址
// @src: 源字符串地址
char *strcpy( char *dest, const char *src )  
{  
char *strTemp = dest;  
    while(*strTemp ++ = *src++);  
    return dest;  
}
```















