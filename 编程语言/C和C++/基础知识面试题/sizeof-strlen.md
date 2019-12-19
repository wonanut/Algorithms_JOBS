# sizeof和strlen有哪些区别

注意！！sizeof不能用来计算字符串长度！！！

1. sizeof是操作符，strlen是函数。sizeof后如果是类型，必须加括弧；如果是变量名，可以不加括弧。

2. sizeof操作符的结果类型是size_t，它在头文件中typedef为unsigned int类型，保证能容纳实现所建立的最大对象的字节大小。

3. sizeof可以用类型做参数（还可以用函数做参数），strlen只能用hcar*做参数，且必须是以"\0"结尾的。

   ```c
   short fun();
   printf("%d \n", sizeof(fun())); // 输出2
   ```

4. 数组做sizeof的参数不退化，传递给strlen就退化为指针了。

   - 对以数组为形参的函数，传过去之后实参都变成数组首地址，即为退化。而sizeof不是函数，所以保留数组特性不退化。

5. 大部分编译程序在编译的时候sizeof就被计算过了，这就是sizeof(x)可以用来定义数组维数的原因。strlen的结果要在运行时才计算出来，它用来计算字符串的长度，不是类型占内存的大小。

6. 在计算字符串数组的长度上有区别，如：

   ```c
   char str[20]="0123456789";
   int a = sizeof(str);  //10
   int b = strlen(str);  //20，求的是数组所占内存空间大小
   ```

7. 如果要计算指针所指向的字符串的长度，则一定要用strlen。如：

   ```c
   char *ss = "0123456789";
   int a = sizeof(ss); //4, 计算的是ss指针所占用的内存空间大小。
   int b = strlen(ss); //10，计算的是ss指针所指向的字符串的长度。
   ```