struct MergeSortTree{
    vector<vector<int>>tree;
    int n;
    MergeSortTree(int _n){
        n = _n;
        tree.resize(4*n);
    }
    void build(int node,int nl,int nr){
        if(nl==nr){
            tree[node].emplace_back(arr[nl]);
            return;
        }
        int mid = nl + (nr - nl)/2;
        build(2*node+1,nl,mid);
        build(2*node+2,mid+1,nr);
        merge(tree[2*node+1].begin(), tree[2*node+1].end(),tree[2*node+2].begin(), tree[2*node+2].end(),inserter(tree[node], tree[node].end()));
    }
    int query(int node,int nl,int nr,int l,int r,int k){
        if(nl>=l && nr<= r){
            auto it = nr - nl + 1 - (upper_bound(tree[node].begin(),tree[node].end(),k) - tree[node].begin());
            return it;
        }
        if(nl>r||nr<l)return 0;
        int mid = nl + (nr - nl)/2;
        return query(2*node+1,nl,mid,l,r,k) + query(2*node+2,mid+1,nr,l,r,k);
    }
};