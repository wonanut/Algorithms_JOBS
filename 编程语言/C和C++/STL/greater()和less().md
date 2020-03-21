## greater()和less()

- 头文件及模板定义

```c++
#include<functional>

// 从大到小排序
template <class T> struct greater {
    bool operator() (const T& x, const T& y) const {return x > y;}
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef bool result_type;
};

// 从小到大排序
template <class T> struct less {
    bool operator() (const T& x, const T& y) const {return x < y;}
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef bool result_type;
};
```

- sort()应用

```c++
int A[] = {1, 4, 3, 7, 10};
const int n = sizeof(A) / sizeof(int);
vector<int> v(a, a + n);

sort(v.begin(), v.end(), greater<int>()); // 从大到小排列
sort(v.begin(), v.end(), less<int>()); // 从大到小排列
```

- 优先队列应用

```c++
#inlcude <algorithm>
#include <queue>

int main()
{
	priority_queue<int> q;
    int a[4] = {2, 3, 1, 4};
    vector<int> arr(a, a + 4);
    for(int i = 0; i < arr.size(); ++i) {
        q.push(arr[i]);
    }
    while(!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }// 将会按照从大到小的顺序输出，因为priority_queue默认是大顶堆，每次出队都是最大的。
    
    priority_queue<int, vector<int>, greater<int> > q2;
    for(int i = 0; i < arr.size(); ++i) {
        q2.push(arr[i]);
    }
    while(!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }// 将会按照从小到大的顺序输出，因为greater构造的是小顶堆，每次出队都是最小的。
    return 0;
}
```































