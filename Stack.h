#include "Vector.h"

template <typename T> 
class Stack : public Vector <T> {
public:
    void push(T const& e){this->insert(this->size(), e);}
    T pop(){return this->remove(this->size()-1);}
    T& top(){return (*this)[this->size()-1];}
    bool empty(){return this->empty();}
};

void convert(Stack<char>& S, long long n, int base){
    static char digit[] = "0123456789ABCDEF";

    while(n > 0){
        S.push(digit[n % base]);
        n = n / base;
    }
    while(!S.empty()){
        S.pop();
    }
    return;
}

bool paren(const char exp[]) {
    Stack<char> S;
    for(int i = 0; exp[i] != '\0'; i++){
        if (exp[i] == '{' || exp[i] == '[' ||exp[i] == '(' ){
            S.push(exp[i]);
        }
        if (exp[i] == '}' || exp[i] == ']' ||exp[i] == ')' ){
            if(S.empty()){
                return false;
            }
            char top = S.top();
            if ((exp[i] == ')' && top != '(') ||
                (exp[i] == ']' && top != '[') ||
                (exp[i] == '}' && top != '{') ) {
                    return false;
                }
            S.pop();
        }
    }
    return S.empty();
}