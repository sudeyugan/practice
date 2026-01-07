typedef int Rank;
template <typename T> struct ListNode{
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;

    ListNode(T d=T(), ListNode<T>* p = nullptr, ListNode<T>* s = nullptr):data(d), pred(p), succ(s){}

    ListNode<T>* insertAsPred(T const& e);
    ListNode<T>* insertAsSucc(T const& e);
};

template <typename T> 
    ListNode<T>* ListNode<T>::insertAsPred(T const& e){
        ListNode<T>* x = new ListNode(e, pred, this);
        x->pred->succ = x;
        this->pred = x;
        return x;
    }

template <typename T>
    ListNode<T>* ListNode<T>::insertAsSucc(T const& e){
        ListNode<T>* x = new ListNode(e, this, succ);
        x->succ->pred = x;
        this->succ = x; 
        return x;
    }


template <typename T> class List{
private:
    int _size;
    ListNode<T>* header;
    ListNode<T>* trailer;

protected:
    void init(){
        header = new ListNode<T>;
        trailer = new ListNode<T>;
        header->succ = trailer;
        trailer->pred = header;
        _size = 0;
    }

    void copyNodes(ListNode<T>* p, int n){
        init();
        int i = 0;
        while (i < n){
            insertAsLast(p->data);
            p = p->succ;
            i++;
        }
    }

    ListNode<T>* selectMax(ListNode<T>* p, int n){
        ListNode<T>* curr = p;
        curr = curr->succ;
        ListNode<T>* max = curr->pred; 
        int i = 1;
        while(curr != trailer && i < n){
            if (curr->data >= max->data){
                max = curr;
            }
            i++;
            curr = curr->succ;
        }
        return max;
    }

    // 将节点 p 移动到节点 target 之前
    void moveBefore(ListNode<T>* p, ListNode<T>* target) {
        if (p == target || p->succ == target) return; // 位置没变，直接返回

        // 1. 将 p 从当前位置“摘除”
        p->pred->succ = p->succ; //
        p->succ->pred = p->pred; //

        // 2. 将 p 插入到 target 之前
        p->pred = target->pred; //
        p->succ = target;       //
        
        // 3. 更新 target 原前驱和 target 本身的指向
        p->pred->succ = p;
        target->pred = p;
    }



public:
    List(){init();}

    List(ListNode<T>* p, int n){copyNodes(p, n);}
    List(List<T> const& L){copyNodes(L.first(), L.size());}

    int size(){return _size;}
    bool empty(){return _size <= 0;}

    ListNode<T>* first() const { return header->succ; }
    ListNode<T>* last() const { return trailer->pred; }

    ListNode<T>* find(T const&e, int n, ListNode<T>* p){
        int i = 0;
        while(i < n){
            p = p->pred;
            if (p->data == e){
                return p;
            }
            i++;
        }
        return nullptr;
    }

    ListNode<T>* insertAsFirst(T const& e) {
        _size++;
        return header-> insertAsSucc(e);
    }

    ListNode<T>* insertAsLast(T const& e) {
        _size++;
        return trailer-> insertAsPred(e);
    }

    ListNode<T>* insert(ListNode<T>* p, T const& e) {
        _size++;
        return p-> insertAsPred(e);
    }

    T remove(ListNode<T>* p){
        T e = p->data;
        p->succ->pred = p->pred;
        p->pred->succ = p->succ;
        delete p;
        _size--;
        return e; 
    }

    int deduplicate(){
        if(_size < 2) return 0;
        int old_size = _size;
        ListNode<T>* p = header->succ;
        int r = 0;
        while (p != trailer){

            ListNode<T>* q = p->succ;

            if (find(p->data, r, p)){
                remove(p);
            }else{
                r++;
            }

            p = q;
        }
        return old_size - _size;
    }

    int uniquify(){
        if(_size < 2) return 0;
        int old_size = _size;
        ListNode<T>* p = header->succ;
        while (p->succ != trailer){
            ListNode<T>* q =p->succ;
            if (q->data == p->data){
                remove(q);
            }else{
                p = q;
            }
        }
        return old_size -_size;
    }

    void bubbleSort(ListNode<T>* p, int n) {
        ListNode<T>* head = p->pred; // 确定排序区间的左边界
        ListNode<T>* tail = p;
        for (int i = 0; i < n; i++) tail = tail->succ; // 确定排序区间的右边界

        bool swapped = true;
        while (swapped) {
            swapped = false;
            ListNode<T>* curr = head->succ; // 从区间第一个元素开始
            
            // 在当前区间内对比相邻节点
            // 注意：n-1 次比较，且不要越过 tail
            for (int i = 1; i < n; i++) {
                ListNode<T>* nextNode = curr->succ;
                
                if (curr->data > nextNode->data) {
                    // 如果逆序，将 nextNode 移到 curr 之前
                    moveBefore(nextNode, curr);
                    swapped = true;
                    // 移动后，curr 依然指向那个较大的元素，无需更新 curr 指针
                    // 这样下一轮循环会继续用这个较大的元素跟它新的后继对比
                } else {
                    // 如果顺序正确，则前进到下一个节点
                    curr = nextNode;
                }
            }
            n--; // 每一轮冒泡后，末尾已就绪，缩减待排区间
        }
    }

    void insertionSort(ListNode<T>* p, int n){
        ListNode<T>* start = p;
        p = p->succ;
        int i = 1; 
        while(p != trailer && i < n){
            ListNode<T>* curr = p;
            p = p->succ;
            i++;
            T e = curr->data;
            ListNode<T>* low =curr->pred;
            while ( low!= p->pred && e < low->data){
                low = low->pred;
            } 
            if(low != curr->pred){
                curr->pred->succ = curr->succ;
                curr->succ->pred = curr->pred;
                curr->succ = low->succ;
                low->succ->pred = curr;
                low->succ = curr;
                curr->pred = low;
            }
        } 
        return;
    }


    // 优化后的插入排序
    void insertionSort(ListNode<T>* p, int n) {
        for (int r = 0; r < n; r++) {
            // 在 p 的前 r 个节点中寻找不大于 p->data 的最后者
            ListNode<T>* target = find(p->data, r, p);
            
            ListNode<T>* nextNode = p->succ; // 记录下一个要处理的节点
            
            // 如果 find 返回 nullptr，说明 p 比前面所有都小，移到最前面
            // 否则移到 target 的后面，即 target->succ 之前
            moveBefore(p, (target ? target->succ : first()));
            
            p = nextNode; // 转向下一节点
        }
    }

    void selectionSort(ListNode<T>* p, int n) {
        ListNode<T>* head = p->pred; // 保持前边界
        ListNode<T>* tail = p; 
        for (int i = 0; i < n; i++) tail = tail->succ; // 找到后边界

        while (n > 1) {
            // 在 head->succ 及其后 n 个节点中找最大者
            ListNode<T>* max = selectMax(head->succ, n); 
            
            // 将 max 移动到 tail 之前（即当前有序部分的头部）
            moveBefore(max, tail); 
            
            // tail 指向刚刚移动过来的 max，范围缩小
            tail = max; 
            n--;
        }
    }
    List<T>& operator=(List<T> const& L) {
        if (this != &L) { // 防止自我赋值
            clear(); // 先清空现有元素
            copyNodes(L.first(), L.size()); // 再拷贝新元素
        }
        return *this;
    }

    void reverse() {
        if (_size < 2) return;
        ListNode<T>* curr = header;
        while (curr != nullptr) {
            ListNode<T>* temp = curr->pred;
            curr->pred = curr->succ;
            curr->succ = temp;
            curr = curr->pred; 
        }
        ListNode<T>* temp = header;
        header = trailer;
        trailer = temp;
    }

    int clear(){
        int old_size = _size;
        while (_size > 0){
            remove(header->succ);
        }
        return  old_size - _size;
    }

    ~List(){
        clear();
        delete header;
        delete trailer;
    };


};


