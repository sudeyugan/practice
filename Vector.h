typedef int Rank;
const int DEFAULT_CAPACITY = 3;

template <typename T>
class Vector{
    protected:
        Rank _size;
        Rank _capacity;
        T* _elem;
        void copyFrom(T const* A, Rank lo, Rank hi) {
            _capacity = 2*(hi - lo);
            _elem = new T[_capacity];
            _size = 0;
            while (lo < hi){
                _elem[_size++] = A[lo++]; 
            }
        }

        void expand(){
            if (_size < _capacity){
                return;
            }else{
                T* old_elem = _elem;
                _capacity = _capacity * 2;
                _elem = new T[_capacity];
                for (int i = 0; i < _size; i++){
                    _elem[i] = old_elem[i];
                }
                delete []   old_elem;
            }
        }


    public:
        Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0){
            if (c < DEFAULT_CAPACITY){
                _capacity = DEFAULT_CAPACITY;
            }else{
                _capacity = c;
            }
            _elem = new T[_capacity];
            _size = s;
            for (int i =0; i < s; i++){
                _elem[i] = v;
            }
        }

        Vector(T const* A, Rank n){
            copyFrom(A, 0, n);
        }

        ~Vector(){
            if(_elem){
                delete[] _elem;
            }
        }

        Rank size() const{
            return _size;
        }

        Rank insert(Rank r, T const& e){
            expand();
            for (int i = _size; i > r; i--){
                _elem[i] = _elem[i-1];
            }
            _elem[r] = e;
            _size++;
            return r;
        }

        int remove(Rank lo,Rank hi){
            if(lo == hi){
                return 0;
            }else{
                while (hi < _size){
                    _elem[lo++] = _elem[hi++];
                } 
                _size = lo; 
                return hi - lo;
            }
        }

        T remove(Rank r){
            T e = _elem[r]; 
            remove(r, r+1);
            return e;
        }

        T& operator[](Rank r){
            return _elem[r];
        }

        Rank find(T const& e, Rank lo, Rank hi) const {
            for(int i = hi-1; i >= lo; i--){
                if(_elem[i] == e ){
                    return i;
                }
            }
            return -1;
        }

        Rank find(T const& e) const { return find(e, 0, _size); }

        int deduplicate(){
            int old_size = _size;
            int i = 1;
            while(i < _size){
                if(find(_elem[i],0,i) < 0){
                    i++;
                }else{
                    remove(i);
                }
            }
            return old_size - _size;
        }

        int disorder(){
            int n = 0;
            for(int i = 0; i< _size-1; i++){
                if(_elem[i] > _elem[i+1]){
                    n++;
                }
            }
            return n;
        }

        Rank search(T const& e, Rank lo, Rank hi) const {
            while (lo <hi){
                int mid = (lo + hi) >> 1;
                if(e < _elem[mid]){
                    hi = mid;
                }else{
                    lo = mid + 1;
                }
            }
            return lo-1;
        }

        int uniquify(){
            int old_size =_size;
            int i = 0, j = 1;
            while (j < _size){
                if (_elem[j] != _elem[i]){
                    i++;
                    _elem[i] = _elem[j];
                }
                j++;
            }
            _size = i + 1;
            return old_size - _size;
        }

};