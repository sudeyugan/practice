#include "List.h"

template <typename T>
class Queue : public List<T>{
public:
    void enqueue(T const& e){
        this->insertAsLast(e);
        return;
    }

    T dequeue(){
        return this->remove(this->first());
    }

    T& front(){
        return this->first()->data;
    }

    bool empty(){
        return List<T>::empty();
    }

};