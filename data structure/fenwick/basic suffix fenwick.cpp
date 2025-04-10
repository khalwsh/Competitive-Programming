template<class T>
struct Fenwick {
    int n;
    vector<T> tree;
    
    void init(int _n) {
        n = _n;
        tree.resize(n);
    }

    void add(int pos, T value) {
        for (int i = pos + 1; i; i -= i & -i) tree[i - 1] += value;
    }

    T get(int pos) {
        T sum = 0;
        for (int i = pos + 1; i <= n; i += i & -i) sum += tree[i - 1];
        return sum;
    }

    T query(int l, int r) {
        return get(l) - get(r + 1);
    }
};
