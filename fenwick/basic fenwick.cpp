template<class T>
struct Fenwick{
    int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
    int n;
    vector<T>tree;
    int N = 1;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
        N = log2_floor(n) + 1;
    }
    void add(int pos,T value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
    }
    T get(int pos) {
        T sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
        return sum;
    }
    T query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
    int lower_bound(T t){
        T sum = 0;
        int pos = 0;
        for(int i = N; i >= 0; i--){
            int next_pos = pos + (1 << i);
            if(next_pos <= n && sum + tree[next_pos - 1] < t){
                sum += tree[next_pos - 1];
                pos = next_pos;
            }
        }
        return pos; // zero-based index
    }
};