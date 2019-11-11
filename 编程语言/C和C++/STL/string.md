# string

字符串实际上是使用'\0'和null终止的一维字符数组。c/c++在内存中存储的时候会比字符串多一个字符。

## 初始化

```c++
#include <string>

string str = "hello world";
char cstr[] = "abc";
string s1(str); //调用复制构造函数生成s1，s1是str的复制品
string s2(str, 6);//将str开始于位置6的部分当作s2初值
string s3(str, 6, 3); //开始于6，长度顶多为3

string s4(cstr);
string s1(3, 'x'); // 生成s1="xxx"
```

**操作符**：可以用==, !=, >=等比较字符串，返回bool类型（成员函数compare也可以比较，可以和字符串一部分比较）。用+或者+=来连接两个字符串，可以通过下标访问特定字符，这一点和数组一样。

## 获取长度

```c++
int len1 = str.length();
int len2 = str.size();
```

## 赋值和连接

```c++
//用=赋值
string s1("cat"), s2;
s2 = s1;
//用assign赋值
s2.assign(s1);
//用assign成员函数进行部分赋值
s2.assign(s1, 1, 3); //从下标为1的字符开始复制3个字符 
```

- 连接

  - +运算符连接

    ```c++
    string s1("good"), s2("morning");
    s1 += s2;
    cout << s1;
    ```

  - 成员函数append连接

    ```c++
    s1.append(s2);
    s2.append(s1, 3, s1.size());
    // 从下标为3开始，连接s1的s1.size()个字符，如果字符串内没有足够字符，则复制到字符串最后一个字符。
    ```

    

## 下标访问

- a[i]，下表运算符[]不做范围检查，速度快。
- s.at(i)，成员函数at会做范围检查，如果超出范围，会抛出out_of_range异常

## 查找

```c++
size_type find( const char *str, size_type index );//返回str在字符串中第一次出现的位置（从index开始查找），如果没找到则返回string::npos
size_type find( const char *str, size_type index, size_type length );  //返回str在字符串中第一次出现的位置（从index开始查找，长度为length），如果没找到就返回string::npos
size_type find( char ch, size_type index );  // 返回字符ch在字符串中第一次出现的位置（从index开始查找），如果没找到就返回string::npos

//需求： 查找字符串a是否包含字符串b
if(strA.find(strB) != string::npos) return true;


// 成员函数rfind(),从后往前找

```

## 类型转换

```c++
char *strs = str.c_str();  //string转换成const char *，以'\0'街尾
string str(cstr); //char*转换成string
```

- 成员函数data() 返回char*


## 其他常用函数

```
string &insert(int p, const string &s); //在p位置插入字符串s
string &append(const char *s);  //把字符串s连接到当前字符串结尾
void push_back(char c); //当前字符串尾部添加一个字符c，和vector类似

// 成员函数swap()
s1.swap(s2);  //交换两个字符串
```

- 成员函数替换replace()
- 成员函数erase()
- 成员函数插入insert()

## to_string函数（C++11支持）

```c++
//各种类型转string型
string to_string (int val);
string to_string (long val);
string to_string (long long val);
string to_string (unsigned val);
string to_string (unsigned long val);
string to_string (unsigned long long val);
string to_string (float val);
string to_string (double val);
string to_string (long double val)
```



##  应用典例

字符串的切割，c++和java不同，java有提供对应的split切割函数，c++需要自己实现。

用strtok函数进行字符串分割，将其封装成splitStr方法，实现如下：

```c++
/*
原型： char *strtok(char *str, const char *delim)；
功能：分解字符串为一组字符串
参数：str为要分解的字符串，delim为分隔符字符串
返回值：从str开头的一个个被分割的串，没有时返回NULL
*/
vector<string> splitStr(const string& str, const string& delim){
       vector<string> res;
       if("" == str) return res;
       //先将要切割的字符串从string转换成char*类型
       char *strs = new char[str.length() + 1];
       strcpy(strs, str.c_str());
       char *delims = new char[delim.length() + 1];
       strcpy(delims, delim.c_str());

       char *p = strtok(strs, d);
       while(p){
           string s = p;
           res.push_back(s);
           p = strtok(NULL, d);
       }
       retun res;
   }
```

## 字符串处理函数

```c++
char *strtok(char *str, const char *delim) //字符串切割
char *strstr( char *str, char * substr ); //字符串中查找字符串，返回substr第一次出现的地址，没有返回NULL
char * strchr (const char *str, char c); //查找某字符在字符串中首次出现的位置，返回地址，否则返回NULL。strrchr()函数可以返回字符最后一次出现的位置
```

### 字符串子串substr()

```c++
//语法：
// basic_string substr(size_type index, size_type num = npos)
// 作用：返回本字符串的一个字串，从index开始，长num歌字符。如果欸有指定，将是默认值npos。返回从Index开始的剩余字符串。

string str="hello";
str.substr(startpos, length);// 取从startpos开始的长度为length的字符串
str.substr(num); // 取从num开始的剩余的字符串
```

#### substr应用案例：剑指offer的左旋字符串

```c++
string LeftRotateString(string str, int n) {
        if(str.length() == 0 || n == 0) return str;
        string tmp_before = str.substr(0, n);  // 返回从index=0，长度为n的子字符串
        string tmp_after = str.substr(n);  // 返回index=n之后的子字符串
        return tmp_after + tmp_before;
    }
```

