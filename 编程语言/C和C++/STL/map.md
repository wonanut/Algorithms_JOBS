# Map

- 是STL的一个关联容器，提供一对一（key, value）的数据处理能力。


- 内部是通过自建一棵红黑树（非严格意义上的平衡二叉树）。具有对数据自动排序的功能，所以在map内部所有的数据都是有序的。


- 每个元素都是一个pair模板类的对象，可以修改value，不能修改key。


- 查找元素的复杂度是log(N)


```c++
#include <map>
#include <string>

//声明
map<string, string> m;

//数据的插入
//用insert函数插入pair
m.insert(pair<string, string>("001", "a"));
//数组方式插入
m["001"] = "a";

//大小
m.size();

//遍历
//迭代器
map<string,string>::itrator it;
for(it = m.begin(); it != m.end(); it++){
    cout << it->first <<' '<< it->second <<endl;
}
//数组
for(int i = 0; i <= m.size(); i++){  //注意这里是<=
    cout << m[i] <<endl;
}
```

