#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class Heap {
private:
	bool heap_type;		// type = 0：小顶堆， type = 1：大顶堆
	vector<T> data;
	size_t _size;

	void sink_down(int pos, int node_numbers);
	void sink_up(int pos);
	void heapify_aux();
	inline bool const cmp(int pos1, int pos2) {
		return (data[pos1] < data[pos2]) ^ heap_type;
	}
public:
	Heap(bool type = 0) { data.push_back(INT_MAX); _size = 0; heap_type = type; }
	Heap(vector<T>& arr, bool type = 0);
	inline size_t size() { return _size; }
	void heapify(vector<T>& arr, bool type = 0);
	void insert(const T val);
	T getTop();
	T delTop();
	void printHeap();
	void heapSort();
};

// 从当前节点往下更新
template<typename T>
void Heap<T>::sink_down(int pos, int node_numbers) {
	int child_1_pos = pos * 2;
	int child_2_pos = pos * 2 + 1;
	
	// 如果当前节点没有子节点
	if (child_1_pos > node_numbers) return;
	// 如果当前节点只有左子节点
	else if (child_2_pos > node_numbers) {
		if (cmp(child_1_pos, pos)) {
			swap(data[pos], data[child_1_pos]);
			sink_down(child_1_pos, node_numbers);
		}
	}
	// 如果当前节点有左右子节点
	else {
		int min_val_pos;
		if (this->heap_type == 0) {
			min_val_pos = data[child_1_pos] <= data[child_2_pos] ? child_1_pos : child_2_pos;
		}
		else {
			min_val_pos = data[child_1_pos] >= data[child_2_pos] ? child_1_pos : child_2_pos;
		}
		if (cmp(min_val_pos, pos)) {
			swap(data[pos], data[min_val_pos]);
			sink_down(min_val_pos, node_numbers);
		}
	}
}

// 从当前节点往上更新
template<typename T>
void Heap<T>::sink_up(int pos) {
	int root_pos = pos / 2;
	if (root_pos == 0) return;
	
	if (cmp(pos, root_pos)) {
		swap(data[pos], data[root_pos]);
		sink_up(root_pos);
	}

}

template<typename T>
Heap<T>::Heap(vector<T>& arr, bool type) {
	data.push_back(INT_MAX);
	this->_size = 0;
	this->heap_type = type;
	for (int i = 0; i < arr.size(); i++) {
		data.push_back(arr[i]);
		_size++;
		sink_up(i + 1);
	}
}

template<typename T>
void Heap<T>::heapify_aux() {
	for (int i = size() / 2; i >= 1; i--) {
		sink_down(i, size());
	}
}

template<typename T>
void Heap<T>::heapify(vector<T>& arr, bool type) {
	data.clear();
	data.push_back(INT_MAX);
	this->heap_type = type;
	for (unsigned int i = 0; i < arr.size(); i++) data.push_back(arr[i]);
	this->_size = arr.size();

	heapify_aux();
}

template<typename T>
void Heap<T>::printHeap() {
	for (int i = 1; i <= size(); i++) {
		cout << data[i] << " | ";
	}
	cout << endl;
}

template<typename T>
void Heap<T>::heapSort() {
	if (size() <= 1) return;

	int cur_pos = size();
	while (cur_pos != 1) {
		swap(data[1], data[cur_pos]);
		sink_down(1, --cur_pos);
	}
}

template<typename T>
void Heap<T>::insert(const T val) {
	data.push_back(val);
	this->_size++;
	sink_up(size());
}

template<typename T>
T Heap<T>::getTop() {
	if (size() == 0) return data[0];
	return data[1];
}

template<typename T>
T Heap<T>::delTop() {
	if (size() == 0) return data[0];
	int ret = data[1];

	swap(data[1], data[size()]);
	data.pop_back();
	this->_size--;
	heapify_aux();
	return ret;
}