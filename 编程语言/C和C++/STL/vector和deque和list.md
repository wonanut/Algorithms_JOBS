# vector

属于C++标准模板库的部分内容，被认为是一个可以存储任意类型的**动态数组**，能够增加和压缩数据。

- 常数时间存取（下标访问）
- 前面或中间O(N)插入复杂度，尾端增删大部分是常数时间

就像数组一样，vector也采用的连续存储空间来存储元素。也就是意味着可以采用下标对vector的元素进行访问，和数组一样高效。但是又不像数组，它的大小是可以动态改变的，而且它的大小会被容器自动处理。

使用时头文件需包含:

```c++
#include <vector>
using namespace std; //vector是属于命名域的，需要通过命名限定，这里使用的是全局命名域方式（建议）
//using std::vector;
//vector<int> vInts;
//命名限定，可以连在一起：std::vector<int> vInts

vector<int> v1;//创建一个int的空向量
//初始化v1
for(int i=0;i<10;i++){
    v1.push_back(i);
}
//用数组来初始化vector，vector不可以像数组一样用{}来进行初始化
int a[3]={1,2,3};
v1(a,a+3)；//这里的第二个参数表示的是区间尾地址的下一个地址

vector<int> v2(v1);//创建一个v1的拷贝
vector<int> v3(100);//创建一个包含100个int类型数据的向量
vector<int> v4(100,0);//创建一个包含100个int类型数据的向量，并初始化为0
```

## **元素遍历**

```C
vector<int>::iterator it;

for(it=vec.begin();it!=vec.end();it++){  // 也可以it < vec.end(),<这种只有随机迭代器才可以用
    cout<< *it <<endl;
}

vector<int>::reverse_iterator it2;  //反向迭代器

for(it2 = vec.rbegin(); it2 != vec.rend(); ++it2)
{
    cout << *it2 << endl;
}
/*
vec.bgein() 开始指针
vec.end() 末尾指针，指向最后一个元素的下一位置
vec.size() 给出动态数组的大小
*/
//或者
for(int i=0;i<vec.size();i++){
    cout << vec.at(i) << endl;  //at方法访问会检查是否越界，是就抛出out of range异常,下标访问不会检查。
    cout << vec[i] << endl;  //下标随机访问
}
```

## **元素翻转**

```c++
#include<algorithm>

reverse(vec.begin(),vec.end());
```

## **元素排序**

```c++
#include<algorithm>

sort(vec.begin(),vec.end());//从小到大排序
//这里的第二个参数表示的是区间尾地址的下一个地址
//如果想从大到小排序，可以采用上面反转函数，也可以采用下面方法:
bool Comp(const int& a, const int& b) {
    return a > b;
}
sort(vec.begin(), vec.end(), Comp);
```

## 元素插入

```c++
vec.insert(vec.begin(), num); //在数组开始位置插入元素num
vec.insert(vec.begin(), 3, num); //在数组开始位置插入3个num
```

## 作为参数传递

```c++
#include <vector>
using namespace std;
// 传参方式
function1(vector< vector<int> vec>) //传值
function2(vector< vector<int>& vec>) //传引用
function3(vector< vector<int>* vec>) //传指针
    
// 调用形式
function1(vec>) //传值
function2(vec>) //传引用
function3(&vec>) //传指针
// 效果
// 1. 传值会发生拷贝构造
// 2. 传引用不会发生拷贝构造
// 3. 传指针不会发生拷贝构造
```

# deque  

双向队列，有head和tail指针，顺序存储。

头文件#include <deque>

- 在内存连续存放，随机存取元素都在常数时间完成（慢于vector）
- 两端增删元素性能较佳，对于在队头队尾之外的位置插入元素性能较差
- 所有适用于vector的操作都适用于deque

## 容器属性

- 序列：序列容器中的元素按严格的线性顺序排序。各个元素按其顺序访问他们的位置。
- 动态数组：通常使用动态数组实现deque，允许直接访问序列中的任何元素，并在序列的开头或结尾处提供相对快速的增加或删除。

## 迭代器

```
begin: 返回双端队列的开始位置迭代器
end: 返回deque结束位置迭代器
rbegin: 返回deque反向开始迭代器，即原始队列的最后一个元素的迭代器
rend: 返回原始队列的第一个元素的前一个位置的迭代器
cbegin: 返回deque开始元素的常量迭代器，即不可以通过cbegin所返回的迭代器修改队列元素的值
cend: 返回deque结束元素最后一个元素的下一位置常量迭代器，也不可以通过此迭代器修改元素的值
crbegin: 类似上面cbegin + rbegin的组合
crend: cend + rend
```

## 容器

```
size: 返回大小
max_size: deque可以达到的最大可能大小，但容器无法保证能够到达该大小
resize: 改变deque大小
empty: 判断空
shrink_to_fir: 请求减少容器内存使用量以适应其大小。
```

## 元素访问

```
operator[]: 通过下标访问队列指定元素的位置
at: 通过下标访问队列指定位置的元素，与[]等价
front: 返回deque的头元素，若队列为空，会导致未定义的行为发生。
back: 返回尾元素，若队列为空，会导致未定义的行为发生。
```

## 容器的更改

```
assign: 将新内容分配给deque，替换当前内容，并相应的修改其大小。（使用assign后，原容器中保存的任何元素都被销毁并被新构造的元素替换）
push_back: 末尾添加元素
push_front: 起始位置之前插入一个元素
pop_back: 删除最后一个元素，有效将容器大小减少一个
pop_front: 删除第一个元素，有效将容器大小减少一个
insert: 指定位置插入新元素，并返回插入的第一个新元素的迭代器
erase: 从容器中移除指定位置的元素或移除指定范围内的所有元素。
swap: void swap(deque& x)使用x的内容交换容器的内容
clear: 移除所有元素，size变为0
emplace: 通过在position处插入新元素来扩展容器
emplace_front：开头插入新元素
emplace_back: 结尾处插入新元素
```



# list 

双向链表

- 在内存不连续存放，随机插入都是常数级复杂度，不支持随机存取。（按下标访问）

- 除了具有所有顺序容器都具有的成员函数之外，还支持8个成员函数

  ```
  push_front: 在前面插入
  pop_front: 删除前面的元素
  sort: 排序
  remove: 删除和指定值相等的所有元素 eg.list1.remove(2)
  unique: 删除所有和前一个元素相同的元素（要做到元素不重复，在unique之前要先sort）
  merge: 合并
  reverse: 颠倒链表
  splice
  ```

  

















