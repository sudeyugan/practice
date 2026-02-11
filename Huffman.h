#include "Tree.h"
#include "List.h"

#define INF 100000000 

struct HuffChar
{
    char ch;
    int weight;
    HuffChar(char c = ' ', int w = INF) : ch(c), weight(w){}
    bool operator>(const HuffChar& other) const {
        return weight > other.weight;
    }
    bool operator==(const HuffChar& other) const{
        return weight == other.weight;
    }
};


typedef BinTree<HuffChar> HuffTree;
typedef List<HuffTree*> HuffForest;

HuffTree* minHChar(HuffForest* forest){
    ListNode<HuffTree*>* p = forest->first();
    ListNode<HuffTree*>* minNode = p;
    int minWeight = p->data->root()->data.weight;

    for(int i = 0; i < forest->size(); i++){
        if(minWeight > p->data->root()->data.weight){
            minNode = p;
            minWeight = p->data->root()->data.weight;
        }
        p = p->succ;
    }

    return forest->remove(minNode);
}

HuffTree* generateTree(HuffForest* forest){
    while(forest->size() > 1){
        HuffTree* T1 = minHChar(forest);
        HuffTree* T2 = minHChar(forest);
        HuffTree* S = new HuffTree;
        S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
        S->attachAsLC(S->root(), T1);
        S->attachAsRC(S->root(), T2);
        forest->insertAsLast(S);
    }
    return forest->first()->data;
} 

