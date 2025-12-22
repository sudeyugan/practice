#include <iostream>
#include "Vector.h" // 引入你写的头文件

using namespace std;

// 辅助函数：打印 Vector 内容
template <typename T>
void printVector(Vector<T>& v) {
    cout << "Size: " << v.size() << " | Data: [ ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== 1. 测试构造与扩容 ===" << endl;
    // 初始化一个默认容量为 3 的向量
    Vector<int> v; 
    
    // 插入 5 个元素，触发自动扩容 (3 -> 6)
    for (int i = 0; i < 5; i++) {
        v.insert(i, i * 10); // 插入 0, 10, 20, 30, 40
        cout << "Inserted " << i * 10 << " -> ";
        printVector(v);
    }

    cout << "\n=== 2. 测试随机访问与修改 ===" << endl;
    // 测试 operator[]
    cout << "v[2] is: " << v[2] << endl;
    v[2] = 999; // 修改
    cout << "Modified v[2] to 999 -> ";
    printVector(v);

    cout << "\n=== 3. 测试区间删除 (remove range) ===" << endl;
    // 当前: [0, 10, 999, 30, 40]
    // 删除下标 [1, 3) -> 即删除 10 和 999
    int removedCount = v.remove(1, 3);
    cout << "Removed elements in range [1, 3). Count: " << removedCount << endl;
    cout << "Result -> ";
    printVector(v); 
    // 预期结果: [0, 30, 40]

    cout << "\n=== 4. 测试单元素删除 (remove single) ===" << endl;
    // 删除下标 1 的元素 (30)
    int val = v.remove(1);
    cout << "Removed element at index 1: " << val << endl;
    cout << "Result -> ";
    printVector(v);
    // 预期结果: [0, 40]

    return 0;
}