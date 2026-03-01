#pragma once
#include "Tree.h"

template <typename T>
class BST : public BinTree<T>{
protected:
    BinNodePosi(T) _hot;
    
    BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));

    BinNodePosi(T) rotateAt(BinNodePosi(T) x);
public:
    virtual BinNodePosi(T)& search(const T& e);

    virtual BinNodePosi(T) insert(const T& e);
    
    virtual bool remove(const T& e); 

    static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot);
};

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e) {
    if (this->empty() || e == this->_root->data) {
        _hot = nullptr;
        return this->_root;
    }

    _hot = this->_root; 

    while (true) {
        BinNodePosi(T)& c = (e < _hot->data) ? _hot->lc : _hot->rc;
        
        if (!c || e == c->data) return c;
        
        _hot = c; 
    }
}

template <typename T>
BinNodePosi(T) BST<T>::insert(const T& e){
    BinNodePosi(T)& x = search(e);
    if(x){
        return x;
    }else{
        x = new BinNode<T>(e, _hot);
        this->_size++;
        this->updateHeightAbove(_hot);
        return x;
    }
}

template <typename T>
bool BST<T>::remove(const T& e){
    BinNodePosi(T)& x = search(e);
    if(!x){return false;}

    removeAt(x, _hot);
    this->_size--;
    updateHeightAbove(_hot);
    return true;
}

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot){
    BinNodePosi(T) w = x；
    BinNodePosi(T) succ = nullptr;

    if(!x->lc){
        succ = x = x->lc;
    }else if(!x->rc){
        succ = x = x->rc;
    }else{
        w = w->succ();

        T temp = x->data;
        x->data = w->data;
        w->data = temp;

        BinNodePosi(T) u = w->parent;
        if (u == x) {
            u->rc = succ = w->rc;
        } else {
            u->lc = succ = w->rc;
        }
    }

    hot = w->parent;
    if(succ){
        succ->parent = hot;
    }

    delete w;
    return succ;
}

template <typename T>
BinNodePosi(T) BST<T>::connect34(
    BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
    BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) {
    a->lc = T0; if (T0) T0->parent = a;
    a->rc = T1; if (T1) T1->parent = a;
    this->updateHeight(a); 

    c->lc = T2; if (T2) T2->parent = c;
    c->rc = T3; if (T3) T3->parent = c;
    this->updateHeight(c); 

    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b;
    this->updateHeight(b); 

    return b; 
}

template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v){
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;
    BinNodePosi(T) gg = g->parent;
    BinNodePosi(T) r =nullptr;

    if(v == p->lc && p == g->lc){
        r = connect34(v, p, g, v->lc, v->rc, p->lc, g->rc);
    }else if(v == p->rc && p == g->rc){
        r = connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
    }else if(v == p->rc && p == g->lc){
        r = connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
    }else if(v == p->lc && p == g->rc){
        r = connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
    }

    if(gg){
        if(g == gg->lc){
            gg->lc = r;
        }else{
            gg->rc = r;
        }
    }
    
    r->parent = gg;
    return r;
}