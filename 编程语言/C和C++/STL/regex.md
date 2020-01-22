C++11正则表达式(regex_match、regex_search和regex_replace)

1. C++中需要注意转义字符的使用

```c++
cout << regex_match("123", regex("\\d+")) < endl; //结果为true，完全匹配
```

2. regex_match，完全匹配

   获取匹配结果的存储方式

   ```C++
   match_results<string::const+iterator> result;
   smatch result;
   ```

3. regex_search，搜索匹配

   搜索字符串中存在符合规则的子字符串

4. regex_replace，替换匹配，可以将符合匹配规则的子字符串替换为其他字符串

```C++
string str = "hell0_2019!";
regex pattern("hello");
cout << regex_replace(str, pattern, "233") << endl; //输出为: 233_2019!
```

