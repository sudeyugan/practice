#pragma once

#include"Vector.h"
#include"Tree.h"

#define Parent(i) ((i - 1) >> 1)
#define LChild(i) (1 + ((i) << 1))
#define RChild(i) ((1 + (i)) << 1)

template <typename T>
class Heap{
private:
    Vector<T> _elem;
protected:
    void percolateUp(int i);
    int percolateDown(int n, int i);
public:
    Heap(Vector<T> v){_elem = v;}
    void insert(T const& e);
    T getMax();
    T delMax();
    void makeHeap();
    void heapSort();
};

template <typename T>
void Heap<T>::insert(T const& e){
    _elem.insert(_elem.size(), e);
    percolateUp(_elem.size() - 1);
}

template <typename T>
void Heap<T>::percolateUp(int i){
    if(i > 0 && _elem[i] > _elem[Parent(i)]){
        T temp = _elem[i];
        while(i > 0 && temp > _elem[Parent(i)]){
            _elem[i] = _elem[Parent(i)];
            i = Parent(i);
        }
        _elem[i] = temp; 
    }
    return;
}

template <typename T>
T Heap<T>::delMax(){
    T max = _elem[0];
    _elem[0] = _elem.remove(_elem.size() - 1);
    if (_elem.size() > 1) {
        percolateDown(_elem.size(), 0); 
    }
    return max;
}

template <typename T>
int Heap<T>::percolateDown(int n, int i) {
    T temp = _elem[i]; 
    int j; 
    
    while ((j = LChild(i)) < n) {
        if (j + 1 < n && _elem[j] < _elem[j + 1]) {
            j++; 
        }
        
        if (!(temp < _elem[j])) break;
        
        _elem[i] = _elem[j];
        i = j;
    }
    
    _elem[i] = temp; 
    return i;
}

template <typename T>
void Heap<T>::makeHeap() {
    if(_elem.size() < 2){
    return;
    }
    int i = (_elem.size() / 2) - 1;
    while(true){
    percolateDown(_elem.size(), i);
    if(i == 0) break;
    i--;
    }
}

template <typename T>
void Heap<T>::heapSort(){
    makeHeap();
    int n = _elem.size();
    while(n > 1){
        _elem.swap(_elem[0], _elem[n-1]);
        n--;
        percolateDown(n, 0);
    }
}

