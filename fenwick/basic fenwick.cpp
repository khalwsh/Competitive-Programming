struct Fenwick{
    int n;
    vector<int>tree;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
    }
    void add(int pos,int value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
    }
    int get(int pos) {
        int sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
        return sum;
    }
    int query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
};
