#pragma once

#include "Vector.h" 
#include "Tree.h"

#define BTNodePosi(T) BTNode<T>*

template <typename T>
struct BTNode {
    BTNodePosi(T) parent; 
    Vector<T> key;
    Vector<BTNodePosi(T)> child;

    BTNode() {
        parent = nullptr;
        child.insert(0, nullptr); 
    }

    BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr) {
        parent = nullptr;
        key.insert(0, e);         
        child.insert(0, lc);      
        child.insert(1, rc);     
        if (lc) { lc->parent = this; }
        if (rc) { rc->parent = this; }
    }
};

template <typename T>
class BTree{
protected:
    int _size;
    int _order;
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;
    void solveOverflow(BTNodePosi(T) v);
    void solveUnderflow(BTNodePosi(T) v);
public:
    BTNodePosi(T) search(const T& e);
    bool insert(const T& e);
    bool remove(const T& e);
    BTree(int order=3){
        _size = 0;
        _order = order;
        _root = new BTNode<T>();
    }
};

template <typename T>
BTNodePosi(T) BTree<T>::search(const T& e){
    BTNodePosi(T) v = _root;
    _hot = nullptr;
    while(v){
        Rank r = v->key.search(e);
        if(r >= 0 && e == v->key[r]){
            return v;
        }else{
            _hot = v;
            v = v->child[r+1];
        }
    }
    return nullptr;
}

template <typename T>
bool BTree<T>::insert(const T& e){
    if(search(e)){
        return false;
    }else{
        Rank r = _hot->key.search(e);
        _hot->key.insert(r+1, e);
        _hot->child.insert(r+2, nullptr);
        _size ++;
        solveOverflow(_hot);
        return true;
    }
}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v){
    if(v->child.size() <= _order){
        return;
    }else{
        int s = _order / 2;
        BTNodePosi(T) u = new BTNode<T>();
        u->child.remove(0);

        for (int i = s + 1; i < v->child.size(); i++) {
            u->child.insert(u->child.size(), v->child[i]); 
            if (v->child[i]) { 
                v->child[i]->parent = u; 
            }
        }

        for (int i = s + 1; i < v->key.size(); i++) {
            u->key.insert(u->key.size(), v->key[i]);
        }

        while (v->child.size() > s + 1) v->child.remove(v->child.size() - 1);
        while (v->key.size() > s + 1) v->key.remove(v->key.size() - 1);

        T tempkey = v->key[s];
        v->key.remove(s);

        BTNodePosi(T) p = v->parent;
        if(!p){
            BTNodePosi(T) r = new BTNode<T>*(tempkey, v, u);
            _root = r;
            v->parent = r;
            u->parent = r;
            return;
        }else{
            Rank r = p->key.search(tempkey);
            p->key.insert(r+1, tempkey);
            p->child.insert(r+2, u);
            u->parent = p;
            solveOverflow(p);
        }
    }  
}

template <typename T>
bool BTree<T>::remove(const T& e){
    BTNodePosi(T) v = search(e);
    if(!v){
        return false;
    }else{
        Rank r = v->key.search(e);
        if(v->child[0]){
            BTNodePosi(T) u = v->child[r+1];
            while(u->child[0]){
                u = u->child[0];
            }
            v->key[r] = u->key[0];

            v = u;
            r = 0;
        }
        v->key.remove(r);
        v->child.remove(r+1);
        _size --;
        solveUnderflow(v);
    }
    return true;
}

template <typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v){
    int _lower_bound = (_order + 1) / 2;
    if(v->child.size() >= _lower_bound){
        return;
    }else{
        BTNodePosi(T) p = v->parent;
        if(!p){
            if(v->key.size() == 0 && v->child[0]){
                _root = v->child[0];
                _root->parent = nullptr;
                v->child[0] = nullptr;
                delete v;
            }
            return;
        }

        Rank r = 0;
        while(p->child[r] != v) r++;
        if(r > 0){
            BTNodePosi(T) L = p->child[r-1];
            if(L->child.size() > _lower_bound){
                v->key.insert(0, p->key[r-1]);
                p->key[r-1] = L->key.remove(L->key.size() -1);
                v->child.insert(0, L->child.remove(L->child.size() - 1));
                if(v.child[0]) v->child[0]->parent = v;
                return;
            }
        }

        if(r < p->child.size() - 1){
            BTNodePosi(T) R = p->child[r+1];
            if(R->child.size() > _lower_bound){
                v->key.insert(v->key.size(), p->key[r]);
                p->key[r] = R->key.remove(0);
                v->child.insert(v->child.size(), R->child.remove(0));
                if(v->child[v->child.size()-1]){ 
                    v->child[v->child.size()-1]->parent = v;
                }
                return;
            }
        }

        BTNodePosi(T) L = p->child[r-1];
        L->key.insert(L->key.size(), p->key.remove(r-1));

        L->child.insert(L->child.size(), v->child.remove(0)); 
        if (L->child[L->child.size() - 1]) 
            L->child[L->child.size() - 1]->parent = L;

        while (!v->key.empty()) {
            L->key.insert(L->key.size(), v->key.remove(0));
            L->child.insert(L->child.size(), v->child.remove(0));
            if (L->child[L->child.size() - 1]) 
                L->child[L->child.size() - 1]->parent = L;
        }

        delete v; 
        solveUnderflow(p); 
    }
}