typedef int Rank;
const int DEFAULT_CAPACITY = 3;

template <typename T>
class Vector{
    protected:
        Rank _size;
        Rank _capacity;
        T* _elem;
        void copyFrom(T const* A, Rank lo, Rank hi) {
            _capacity = 2*(hi - lo);
            _elem = new T[_capacity];
            _size = 0;
            while (lo < hi){
                _elem[_size++] = A[lo++]; 
            }
        }

        void expand(){
            if (_size < _capacity){
                return;
            }else{
                T* old_elem = _elem;
                _capacity = _capacity * 2;
                _elem = new T[_capacity];
                for (int i = 0; i < _size; i++){
                    _elem[i] = old_elem[i];
                }
                delete []   old_elem;
            }
        }


    public:
        Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = T()){
            if (c < DEFAULT_CAPACITY){
                _capacity = DEFAULT_CAPACITY;
            }else{
                _capacity = c;
            }
            _elem = new T[_capacity];
            _size = s;
            for (int i =0; i < s; i++){
                _elem[i] = v;
            }
        }

        Vector(T const* A, Rank n){
            copyFrom(A, 0, n);
        }

        ~Vector(){
            if(_elem){
                delete[] _elem;
            }
        }

        Rank size() const{
            return _size;
        }

        bool empty(){
            return _size <= 0;
        }
        Rank insert(Rank r, T const& e){
            expand();
            for (int i = _size; i > r; i--){
                _elem[i] = _elem[i-1];
            }
            _elem[r] = e;
            _size++;
            return r;
        }

        int remove(Rank lo,Rank hi){
            if(lo == hi){
                return 0;
            }else{
                while (hi < _size){
                    _elem[lo++] = _elem[hi++];
                } 
                _size = lo; 
                return hi - lo;
            }
        }

        T remove(Rank r){
            T e = _elem[r]; 
            remove(r, r+1);
            return e;
        }

        T& operator[](Rank r){
            return _elem[r];
        }

        const T& operator[](Rank r) const { return _elem[r]; }

        Rank find(T const& e, Rank lo, Rank hi) const {
            for(int i = hi-1; i >= lo; i--){
                if(_elem[i] == e ){
                    return i;
                }
            }
            return -1;
        }

        Rank find(T const& e) const { return find(e, 0, _size); }

        int deduplicate(){
            int old_size = _size;
            int i = 1;
            while(i < _size){
                if(find(_elem[i],0,i) < 0){
                    i++;
                }else{
                    remove(i);
                }
            }
            return old_size - _size;
        }

        int disorder(){
            int n = 0;
            for(int i = 0; i< _size-1; i++){
                if(_elem[i] > _elem[i+1]){
                    n++;
                }
            }
            return n;
        }

        Rank search(T const& e, Rank lo, Rank hi) const {
            while (lo <hi){
                int mid = (lo + hi) >> 1;
                if(e < _elem[mid]){
                    hi = mid;
                }else{
                    lo = mid + 1;
                }
            }
            return lo-1;
        }

        int uniquify(){
            int old_size =_size;
            int i = 0, j = 1;
            while (j < _size){
                if (_elem[j] != _elem[i]){
                    i++;
                    _elem[i] = _elem[j];
                }
                j++;
            }
            _size = i + 1;
            return old_size - _size;
        }

        void swap(T& a, T& b){
            T temp = a;
            a = b;
            b = temp;
        }

        void bubbleSort(Rank lo, Rank hi){
            bool exchange = true;
            while(exchange == true){
                exchange = false;
                for(int i = lo + 1; i < hi; i++){
                    if (_elem[i] < _elem[i-1]){
                        swap(_elem[i], _elem[i-1]);
                        exchange = true;
                    }
                }
            }
            return;
        }

        void insertSort(Rank lo, Rank hi){
            for(int i = lo + 1; i < hi; i++){
                int j = i;
                T temp = _elem[j];
                while (j > lo && (temp < _elem[j-1])){
                    _elem[j] = _elem[j-1];
                    j--;
                }
                _elem[j] = temp;
            }
            return;
        }

        Rank max(Rank lo, Rank hi){
            T e = _elem[lo];
            Rank r = lo;
            lo++;
            while(lo < hi){
                if(_elem[lo] >= e){
                    e = _elem[lo];
                    r = lo;  
                }
                lo++;
            }
            return r;
        }

        void selectSort(Rank lo, Rank hi){
            for (int i = hi-1; i > lo; i--){
                swap (_elem[max(lo, i+1)], _elem[i]);
            }
            return;
        }

        void merge(Rank lo, Rank mi, Rank hi){
            int lf = mi - lo;
            int lr = hi - mi;
            T* A = _elem + lo;
            T* B = new T[lf];
            for(int i = 0; i < lf; i++){
                B[i] = A[i];
            }
            T* C = _elem + mi;
            int i = 0, j = 0;
            while(i < lf && j < lr){
                if(B[i] <= C[j]){
                    A[i+j] = B[i];
                    i++;
                }else{
                    A[i+j] = C[j];
                    j++;
                }
            }
            while(i < lf){
                A[i+j] = B[i];
                i++;
            }

            delete[] B ;
            return;
        }

        void mergesort(Rank lo, Rank hi){
            Rank mi = (lo + hi) >> 1;
            if(hi - lo < 2){
                return;
            }
            mergesort(lo, mi);
            mergesort(mi, hi);

            merge(lo, mi, hi);
        }

        Rank partition(Rank lo, Rank hi) {
            // 简单起见，取首元素为枢轴；工程中常取随机位置
            int pivot = _elem[lo]; 
            hi--; // 转换为闭区间 [lo, hi]
            
            while (lo < hi) {
                // 从右向左找比 pivot 小的
                while (lo < hi && pivot <= _elem[hi]) hi--;
                if (lo < hi) _elem[lo++] = _elem[hi];
                
                // 从左向右找比 pivot 大的
                while (lo < hi && _elem[lo] <= pivot) lo++;
                if (lo < hi) _elem[hi--] = _elem[lo];
            }
            _elem[lo] = pivot; // 枢轴归位
            return lo; // 返回枢轴位置
        }

        void quicksort(Rank lo, Rank hi) {
            if (hi - lo < 2) return; // 单元素或空区间
            Rank mi = partition(lo, hi);
            quicksort(lo, mi);       // 前半段
            quicksort(mi + 1, hi);   // 后半段
        }

        void shellSort(Rank lo, Rank hi) {
            int n = hi - lo;
            // 使用经典的 Shell 增量序列：n/2, n/4, ..., 1
            for (int gap = n / 2; gap > 0; gap /= 2) {
                for (int i = lo + gap; i < hi; i++) {
                    int temp = _elem[i];
                    int j = i;
                    // 对距离为 gap 的元素进行插入排序
                    while (j >= lo + gap && _elem[j - gap] > temp) {
                        _elem[j] = _elem[j - gap];
                        j -= gap;
                    }
                    _elem[j] = temp;
                }
            }
        }

        // 下滤操作：在 [lo, hi) 范围内对第 i 个节点进行下滤
        void percolateDown(Rank n, Rank i) {
            int j;
            while (i < (j = (i << 1) + 1)) { // j 为左孩子
                // 若右孩子存在且更大，则指向右孩子
                if (j + 1 < n && _elem[j] < _elem[j + 1]) j++;
                // 若父节点已经不小于孩子，则下滤结束
                if (_elem[i] >= _elem[j]) break;
                swap(_elem[i], _elem[j]);
                i = j;
            }
        }

        void heapSort(Rank lo, Rank hi) {
            int n = hi - lo;
            int* A = _elem + lo; // 针对区间进行操作
            
            // 1. 建堆 (自底向上)
            for (int i = n / 2 - 1; i >= 0; i--) {
                percolateDown(n, i);
            }
            
            // 2. 逐一交换堆顶并调整
            while (n > 1) {
                swap(A[0], A[--n]); // 将最大元素移至末尾
                percolateDown(n, 0); // 对剩余部分重新调整
            }
        }

        void countingSort() {
            if (_size < 2) return;
            // 找出最大值和最小值确定范围
            int maxVal = _elem[0], minVal = _elem[0];
            for (int i = 1; i < _size; i++) {
                if (_elem[i] > maxVal) maxVal = _elem[i];
                if (_elem[i] < minVal) minVal = _elem[i];
            }
            
            int range = maxVal - minVal + 1;
            int* count = new int[range]{0}; // 记录每个数出现的次数
            
            for (int i = 0; i < _size; i++) count[_elem[i] - minVal]++;
            
            int k = 0;
            for (int i = 0; i < range; i++) {
                while (count[i]-- > 0) {
                    _elem[k++] = i + minVal;
                }
            }
            delete[] count;
        }
};