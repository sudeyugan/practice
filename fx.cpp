#include <iostream>

using namespace std;

typedef int Rank;

// 列表节点结构
struct ListNode {
    int data;            // 数据
    ListNode* pred;      // 前驱
    ListNode* succ;      // 后继

    // 构造函数：默认值为0，指针默认为空
    ListNode(int d = 0, ListNode* p = nullptr, ListNode* s = nullptr)
        : data(d), pred(p), succ(s) {}

    // 操作接口
    ListNode* insertAsPred(int const& e);
    ListNode* insertAsSucc(int const& e);
};

// 在当前节点前插入新节点
ListNode* ListNode::insertAsPred(int const& e) {
    ListNode* x = new ListNode(e, pred, this);
    if (pred) pred->succ = x; // 确保前驱不为空
    this->pred = x;
    return x;
}

// 在当前节点后插入新节点
ListNode* ListNode::insertAsSucc(int const& e) {
    ListNode* x = new ListNode(e, this, succ);
    if (succ) succ->pred = x; // 确保后继不为空
    this->succ = x;
    return x;
}

// 列表类
class List {
private:
    int _size;           // 规模
    ListNode* header;    // 头哨兵
    ListNode* trailer;   // 尾哨兵

protected:
    // 初始化
    void init() {
        header = new ListNode();
        trailer = new ListNode();
        header->succ = trailer;
        trailer->pred = header;
        header->pred = nullptr;
        trailer->succ = nullptr;
        _size = 0;
    }

    // 复制节点
    void copyNodes(ListNode* p, int n) {
        init();
        while (n--) {
            insertAsLast(p->data);
            p = p->succ;
        }
    }

    // 在指定范围内查找最大节点
    ListNode* selectMax(ListNode* p, int n) {
        ListNode* max = p;
        ListNode* curr = p;
        for (int i = 1; i < n; i++) {
            curr = curr->succ;
            if (curr->data >= max->data) { // 后面优先，保证排序稳定性
                max = curr;
            }
        }
        return max;
    }

public:
    // 构造与析构
    List() { init(); }
    List(ListNode* p, int n) { copyNodes(p, n); }
    List(List const& L) { copyNodes(L.first(), L._size); }
    ~List() {
        clear();
        delete header;
        delete trailer;
    }

    // 只读接口
    int size() const { return _size; }
    bool empty() const { return _size <= 0; }
    ListNode* first() const { return header->succ; }
    ListNode* last() const { return trailer->pred; }

    // 查找
    ListNode* find(int const& e, int n, ListNode* p) {
        while (n-- > 0) {
            p = p->pred;
            if (p->data == e) return p;
        }
        return nullptr;
    }

    // 插入接口
    ListNode* insertAsFirst(int const& e) {
        _size++;
        return header->insertAsSucc(e);
    }

    ListNode* insertAsLast(int const& e) {
        _size++;
        return trailer->insertAsPred(e);
    }

    ListNode* insert(ListNode* p, int const& e) {
        _size++;
        return p->insertAsPred(e);
    }

    // 删除
    int remove(ListNode* p) {
        int e = p->data;
        p->succ->pred = p->pred;
        p->pred->succ = p->succ;
        delete p;
        _size--;
        return e;
    }

    // 清空
    int clear() {
        int old_size = _size;
        while (_size > 0) {
            remove(header->succ);
        }
        return old_size;
    }

    // 唯一化（无序）
    int deduplicate() {
        if (_size < 2) return 0;
        int old_size = _size;
        ListNode* p = header->succ;
        int r = 0;
        while (p != trailer) {
            ListNode* q = p->succ;
            if (find(p->data, r, p)) {
                remove(p);
            } else {
                r++;
            }
            p = q;
        }
        return old_size - _size;
    }

    // 唯一化（有序）
    int uniquify() {
        if (_size < 2) return 0;
        int old_size = _size;
        ListNode* p = header->succ;
        while (p->succ != trailer) {
            ListNode* q = p->succ;
            if (q->data == p->data) {
                remove(q);
            } else {
                p = q;
            }
        }
        return old_size - _size;
    }

    // 插入排序
    void insertionSort(ListNode* p, int n) {
        for (int r = 0; r < n; r++) {
            // 查找合适的插入位置
            ListNode* low = p->pred;
            while (low != header && p->data < low->data) {
                low = low->pred;
            }
            insert(low->succ, p->data); // 插入
            p = p->succ;
            remove(p->pred); // 删除原节点
        }
    }

    void List::insertionSort(ListNode* p, int n) {
    if (n < 2) return; // 规模小于2自然有序

    // 默认第一个节点（p）已经是有序序列
    ListNode* curr = p->succ; 
        for (int r = 1; r < n; r++) {
            ListNode* nextNode = curr->succ; // 预存下一个待处理节点
            ListNode* low = curr->pred;      // 从当前节点的前驱开始向左寻找插入点

            // 在左侧已排序区间中，寻找第一个不大于 curr->data 的节点
            // 只要 low 还没到头哨兵，且数据依然比 curr 大，就继续向左找
            while (low != header && curr->data < low->data) {
                low = low->pred;
            }

            // 如果 low 恰好就是 curr 的前驱，说明 curr 已经在正确位置，无需移动
            if (low != curr->pred) {
                // --- 1. 脱钩 (Detach) ---
                // 将 curr 从当前位置取下，接通其前后的邻居
                curr->pred->succ = curr->succ;
                curr->succ->pred = curr->pred;

                // --- 2. 嫁接 (Attach) ---
                // 将 curr 插入到 low 之后，low->succ 之前
                curr->succ = low->succ;
                curr->pred = low;
                low->succ->pred = curr;
                low->succ = curr;
            }
            
            curr = nextNode; // 转向原序列中的下一个节点
        }
    }

    // 选择排序
    void selectionSort(ListNode* p, int n) {
        ListNode* head = p->pred;
        ListNode* tail = p;
        for (int i = 0; i < n; i++) tail = tail->succ;

        while (n > 1) {
            ListNode* max = selectMax(head->succ, n);
            insert(tail, remove(max));
            tail = tail->pred;
            n--;
        }
    }

    void selectionSort(ListNode* p, int n) {
        ListNode* head = p->pred; // 定位待排序区间的前驱
        ListNode* tail = p;
        for (int i = 0; i < n; i++) tail = tail->succ; // 定位待排序区间的后继

        while (n > 1) {
            ListNode* max = selectMax(head->succ, n); // 找出当前区间最大者

            // 如果 max 已经在区间末尾，则无需移动
            if (max != tail->pred) {
                // 1. 将 max 节点从当前位置脱离 (类似 remove 的逻辑，但不 delete)
                max->pred->succ = max->succ;
                max->succ->pred = max->pred;

                // 2. 将 max 节点插入到 tail 之前 (类似 insertAsPred 的逻辑，但不 new)
                max->pred = tail->pred;
                max->succ = tail;
                max->pred->succ = max;
                tail->pred = max;
            }

            // 范围缩减：tail 像左移动，待排数量减 1
            tail = max; 
            n--;
        }
    }

    // 倒置
    void reverse() {
        if (_size < 2) return;
        ListNode* curr = header;
        while (curr != nullptr) {
            ListNode* tempNode = curr->pred;
            curr->pred = curr->succ;
            curr->succ = tempNode;
            curr = curr->pred; 
        }
        ListNode* tempNode = header;
        header = trailer;
        trailer = tempNode;
    }

    // 赋值运算符重载
    List& operator=(List const& L) {
        if (this != &L) {
            clear();
            copyNodes(L.first(), L._size);
        }
        return *this;
    }    
    // 供 main 调用
    int size() { return _size; }

    ~List() {
        while (_size > 0) remove(header->succ);
        delete header;
        delete trailer;
    };
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    List mylist;

    return 0; 
}