typedef int Rank;
template <typename T> struct ListNode{
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;

    ListNode(T d = 0, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr):data(d), pred(p), succ(s){}

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
            while ( low!= start->pred && e < low->data){
                low = low->pred;
            } 
            if(low != curr->pred){
                remove(curr);
                insert(low->succ, e);
            }
        } 
        return;
    }

    void selectionSort(ListNode<T>* p, int n){
        ListNode<T>* back = p;
        for(int i =0; i < n; i++){
            back = back->succ;
        }
        ListNode<T>* head = p;

        while(n > 0) {
            ListNode<T>* max = selectMax(head, n);
            insert(back, max->data);
            if(max == head){
                head = head->succ;
            }
            remove(max);
            back = back->pred;
            n--;
        }
        return;
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


