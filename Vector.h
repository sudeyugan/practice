#include <iostream>

using namespace std;

typedef int Rank;
const int DEFAULT_CAPACITY = 3;

template <typename T>
class Vector {
protected:
    Rank _size;
    Rank _capacity;
    T* _elem;

    // 复制数组区间 [lo, hi)
    void copyFrom(T const* A, Rank lo, Rank hi) {
        _capacity = 2 * (hi - lo);
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; // 防止申请过小
        _elem = new T[_capacity];
        _size = 0;
        while (lo < hi) {
            _elem[_size++] = A[lo++];
        }
    }

    // 扩容
    void expand() {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        
        T* old_elem = _elem;
        _capacity = (_capacity < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : _capacity * 2; // 确保倍增
        _elem = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            _elem[i] = old_elem[i];
        }
        delete[] old_elem;
    }

public:
    // 构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = T()) {
        _capacity = (c < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : c;
        _elem = new T[_capacity];
        _size = s;
        for (int i = 0; i < s; i++) {
            _elem[i] = v;
        }
    }

    // 数组构造
    Vector(T const* A, Rank n) {
        copyFrom(A, 0, n);
    }
    
    // 拷贝构造
    Vector(Vector<T> const& V) {
        copyFrom(V._elem, 0, V._size);
    }

    // 【新增】赋值运算符重载 (防止内存泄漏/Double Free)
    Vector<T>& operator=(Vector<T> const& V) {
        if (_elem) delete[] _elem;
        copyFrom(V._elem, 0, V._size);
        return *this;
    }

    // 析构
    ~Vector() {
        if (_elem) delete[] _elem;
    }

    // 基础接口
    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }
    
    // 插入
    Rank insert(Rank r, T const& e) {
        expand();
        for (int i = _size; i > r; i--) {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        _size++;
        return r;
    }
    // 默认插入末尾
    Rank push_back(T const& e) { return insert(_size, e); }

    // 区间删除 [lo, hi)
    int remove(Rank lo, Rank hi) {
        if (lo == hi) return 0;
        while (hi < _size) {
            _elem[lo++] = _elem[hi++];
        }
        _size = lo;
        return hi - lo;
    }

    // 单元素删除
    T remove(Rank r) {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }

    // 访问器
    T& operator[](Rank r) { return _elem[r]; }
    const T& operator[](Rank r) const { return _elem[r]; }

    // 无序查找 (O(n))
    Rank find(T const& e, Rank lo, Rank hi) const {
        for (int i = hi - 1; i >= lo; i--) {
            if (_elem[i] == e) return i;
        }
        return -1;
    }
    Rank find(T const& e) const { return find(e, 0, _size); }

    // 无序去重 (O(n^2))
    int deduplicate() {
        int old_size = _size;
        int i = 1;
        while (i < _size) {
            if (find(_elem[i], 0, i) < 0) {
                i++;
            } else {
                remove(i);
            }
        }
        return old_size - _size;
    }

    // 逆序对统计
    int disorder() {
        int n = 0;
        for (int i = 0; i < _size - 1; i++) {
            if (_elem[i] > _elem[i + 1]) n++;
        }
        return n;
    }

    // 有序查找 (二分查找 O(log n)) - 返回不大于 e 的最后一个元素秩
    Rank search(T const& e, Rank lo, Rank hi) const {
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (e < _elem[mid]) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo - 1;
    }

    // 有序去重 (O(n))
    int uniquify() {
        if (_size < 2) return 0;
        int old_size = _size;
        int i = 0, j = 1;
        while (j < _size) {
            if (_elem[j] != _elem[i]) {
                _elem[++i] = _elem[j];
            }
            j++;
        }
        _size = i + 1;
        return old_size - _size;
    }

    // 交换
    void swap(T& a, T& b) {
        T temp = a; a = b; b = temp;
    }

    // ==========================================
    //            排序算法区 (SORTING)
    //    注意：所有区间均为 [lo, hi) 左闭右开
    // ==========================================

    // 1. 冒泡排序
    void bubbleSort(Rank lo, Rank hi) {
        bool exchange = true;
        while (exchange) {
            exchange = false;
            for (int i = lo + 1; i < hi; i++) {
                if (_elem[i] < _elem[i - 1]) {
                    swap(_elem[i], _elem[i - 1]);
                    exchange = true;
                }
            }
            hi--; // 每一趟扫描后，最大的元素沉底，hi 前移
        }
    }

    // 2. 插入排序
    void insertSort(Rank lo, Rank hi) {
        for (int i = lo + 1; i < hi; i++) {
            int j = i;
            T temp = _elem[j];
            // 这里的比较逻辑决定升序/降序
            while (j > lo && (temp < _elem[j - 1])) {
                _elem[j] = _elem[j - 1];
                j--;
            }
            _elem[j] = temp;
        }
    }

    // 选择排序辅助函数：找最大值索引
    Rank max(Rank lo, Rank hi) {
        Rank maxRank = lo;
        for (int i = lo + 1; i < hi; i++){
            if (_elem[i] >= _elem[maxRank]) maxRank = i; // >= 保证稳定性
        }
        return maxRank;
    }

    // 3. 选择排序
    void selectSort(Rank lo, Rank hi) {
        while (lo < hi) {
            Rank maxRank = max(lo, hi);
            swap(_elem[maxRank], _elem[hi - 1]); // 将最大值换到最后
            hi--;
        }
    }

    // 归并排序辅助：Merge
    void merge(Rank lo, Rank mi, Rank hi) {
        T* A = _elem + lo; // A 指向被归并区间的起点
        int lf = mi - lo;
        int lr = hi - mi;
        
        T* B = new T[lf]; // 备份左半段
        for (int i = 0; i < lf; i++) B[i] = A[i];
        
        T* C = _elem + mi; // C 指向右半段 (直接用原数组)
        
        int i = 0, j = 0, k = 0;
        // i: B的索引, j: C的索引, k: A的索引
        while (i < lf && j < lr) {
            if (C[j] < B[i]) { // 为了稳定性，当相等时优先取 B (左侧)
                A[k++] = C[j++];
            } else {
                A[k++] = B[i++];
            }
        }
        // 如果 B 还有剩余，直接追加 (C剩余不用管，因为已经在原位置)
        while (i < lf) A[k++] = B[i++];
        
        delete[] B;
    }

    // 4. 归并排序
    void mergesort(Rank lo, Rank hi) {
        if (hi - lo < 2) return;
        Rank mi = (lo + hi) >> 1;
        mergesort(lo, mi);
        mergesort(mi, hi);
        merge(lo, mi, hi);
    }

    // 快速排序辅助：Partition (轴点构造)
    Rank partition(Rank lo, Rank hi) {
        // [修正] 使用模板类型 T，而不是 int
        swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); // 随机交换，避免最坏情况
        T pivot = _elem[lo]; 
        hi--; // 转为闭区间 [lo, hi]
        
        while (lo < hi) {
            while (lo < hi && pivot <= _elem[hi]) hi--;
            if (lo < hi) _elem[lo++] = _elem[hi];
            
            while (lo < hi && _elem[lo] <= pivot) lo++;
            if (lo < hi) _elem[hi--] = _elem[lo];
        }
        _elem[lo] = pivot;
        return lo;
    }

    // 5. 快速排序
    void quicksort(Rank lo, Rank hi) {
        if (hi - lo < 2) return;
        Rank mi = partition(lo, hi);
        quicksort(lo, mi);
        quicksort(mi + 1, hi);
    }

    // 6. 希尔排序
    void shellSort(Rank lo, Rank hi) {
        int n = hi - lo;
        // Gap 序列：n/2, n/4...
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = lo + gap; i < hi; i++) {
                T temp = _elem[i];
                int j = i;
                // 此时是在 lo 偏移量基础上比较
                while (j >= lo + gap && _elem[j - gap] > temp) {
                    _elem[j] = _elem[j - gap];
                    j -= gap;
                }
                _elem[j] = temp;
            }
        }
    }

    // 堆排序辅助：下滤
    // [修正] 增加参数 T* A，用于处理子区间，否则 _elem[j] 会访问错误的绝对索引
    void percolateDown(T* A, Rank n, Rank i) {
        int j;
        while (i != (j = -1)) { // 暂存 logic
             // 左孩子索引 (0-based relative to A)
            int left = 2 * i + 1;
            if (left >= n) break; // 无孩子

            // 找较大的孩子
            j = left;
            int right = left + 1;
            if (right < n && A[right] > A[left]) {
                j = right;
            }

            // 比较父子
            if (A[i] >= A[j]) break; // 满足堆序
            swap(A[i], A[j]);
            i = j; // 继续下滤
        }
    }

    // 7. 堆排序
    void heapSort(Rank lo, Rank hi) {
        int n = hi - lo;
        T* A = _elem + lo; // 获取子区间的指针
        
        // 建堆 (Floyd算法，O(n))
        for (int i = n / 2 - 1; i >= 0; i--) {
            percolateDown(A, n, i); // [修正] 传入 A
        }
        
        // 排序
        while (n > 1) {
            swap(A[0], A[--n]); // 将最大值换到末尾
            percolateDown(A, n, 0); // 对剩余部分下滤
        }
    }

    // 8. 计数排序 (仅适用于整数，为了通用性这里加了类型检查注释)
    // 复杂度 O(n + k)
    void countingSort() {
        if (_size < 2) return;
        // [警告] 仅当 T 为 int 或可转换为 int 时有效
        T maxVal = _elem[0], minVal = _elem[0];
        for (int i = 1; i < _size; i++) {
            if (_elem[i] > maxVal) maxVal = _elem[i];
            if (_elem[i] < minVal) minVal = _elem[i];
        }
        
        int range = (int)(maxVal - minVal + 1);
        int* count = new int[range];
        for (int i = 0; i < range; i++) count[i] = 0;
        
        for (int i = 0; i < _size; i++) count[(int)(_elem[i] - minVal)]++;
        
        int k = 0;
        for (int i = 0; i < range; i++) {
            while (count[i]-- > 0) {
                _elem[k++] = (T)(i + minVal);
            }
        }
        delete[] count;
    }
    
    // 供 main 调用测试
    void print(const char* msg = "") {
        if (msg && *msg) cout << "[" << msg << "] ";
        for (int i = 0; i < _size; i++) cout << _elem[i] << " ";
        cout << endl;
    }
    
    // 为了方便乱序测试
    void shuffle() {
        for (int i = _size - 1; i > 0; i--) {
            swap(_elem[i], _elem[rand() % (i + 1)]);
        }
    }
};