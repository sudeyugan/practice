#include "Stack.h"
#include "Queue.h"
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
template <typename T> 
struct BinNode{
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    int height;

    BinNode() : parent(nullptr), lc(nullptr), rc(nullptr), height(0){}
    BinNode(T e, BinNodePosi(T) p = nullptr) : data(e), parent(p), lc(nullptr), rc(nullptr), height(0){}

    BinNodePosi(T) insertAsLC(T const& e); 
    BinNodePosi(T) insertAsRC(T const& e);

    int size(){
        int s = 1;
        if(lc) s += lc->size();
        if(rc) s += rc->size();
        return s;
    }

    template <typename VST>
    void traversePre (VST& visit){
        visit(data);
        if(lc) lc->traversePre(visit);
        if(rc) rc->traversePre(visit);
        return;
    }

    template <typename VST>
    void traverseIn (VST& visit){
        if(lc) lc->traverseIn(visit);
        visit(data);
        if(rc) rc->traverseIn(visit);
        return;
    }

    template <typename VST>
    void traversePost (VST& visit){
        if(lc) lc->traversePost(visit);
        if(rc) rc->traversePost(visit);
        visit(data);
        return;
    }

    template <typename VST>
    void traversePre_Iterative (VST& visit){
        Stack<BinNodePosi(T)> S;
        if(this){S.push(this);}
        while(!S.empty()){
            BinNodePosi(T)  x = S.pop();
            visit(x->data);

            if(x->rc) S.push(x->rc);
            if(x->lc) S.push(x->lc);
        }
    }

    template <typename VST> 
    void traverseIn_Iterative(VST& visit){
        Stack<BinNodePosi(T)> S;
        BinNodePosi(T) x = this; 

        while (true) {
            while (x) {
                S.push(x);
                x = x->lc;
            }

            if (S.empty()) break;

            x = S.pop();
            visit(x->data);

            x = x->rc;
        }
    }

    template <typename VST>
    void traverseLevel(VST& visit) {
        Queue<BinNodePosi(T)> Q;
        if (this){
        Q.enqueue(this);
        }
        while(!Q.empty()){
            BinNodePosi(T) x = Q.dequeue();
            visit(x->data);
            if(x->lc) Q.enqueue(x->lc);
            if(x->rc) Q.enqueue(x->rc);
        }
    }

    BinNodePosi(T) succ(){
        if(this->rc){
            BinNodePosi(T) x = this->rc;
            while(x->lc){
                x = x->lc; 
            }
            return x;
        }else{
            BinNodePosi(T) x = this;
            while(x->parent && (x->parent->rc == x || x->parent->lc == nullptr)){
                x = x->parent;
            }
            return x->parent;
        }
    }
};

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e){
    return lc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e){
    return rc = new BinNode(e, this);
}

template<typename T>
class BinTree{
protected:
    int _size;
    BinNodePosi(T) _root;

    virtual int updateHeight(BinNodePosi(T) x){
        return x->height = 1 + std::max(stature(x->lc), stature(x->rc)); 
    }

    void updateHeightAbove(BinNodePosi(T) x){
        while(x){
            updateHeight(x);
            x = x->parent;
        }
    }

    static int removeAt(BinNodePosi(T) x){

    }
public:
    BinTree() : _size(0), _root(nullptr) {}
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodePosi(T) root() const { return _root; }

    BinNodePosi(T) insertAsRoot(T const& e){
        _size = 1;
        return _root = new BinNode<T>(e);
    }

    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e){
        _size++;
        BinNodePosi(T) newnode = x->insertAsLC(e);
        updateHeightAbove(x);
        return newnode;
    }
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e){
        _size++;
        BinNodePosi(T) newnode = x->insertAsRC(e);
        updateHeightAbove(x);
        return newnode;
    }

    int remove(BinNodePosi(T) x){
        if(x == x->parent-> 
        )

    }

    
};

