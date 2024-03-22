struct MergeSortTree{
    vector<vector<int>>tree;
    MergeSortTree(int _n){
        tree.resize(4*_n);
    }
    void build(int node,int nl,int nr){
        if(nl==nr){
            tree[node].emplace_back(Label[LinearTree[nl]]);
            return;
        }
        int mid = nl + (nr - nl)/2;
        build(2*node+1,nl,mid);
        build(2*node+2,mid+1,nr);
        merge(tree[2*node+1].begin(),tree[2*node+1].end(),tree[2*node+2].begin(),tree[2*node+2].end(), inserter(tree[node],tree[node].end()));
    }
    int Query(int node,int nl,int nr,int l,int r,int k){
        if(nl>r||nr<l)return 0;
        if(nl>=l && nr<=r)return upper_bound(tree[node].begin(),tree[node].end(),k) - tree[node].begin()  ;
        int mid = nl + (nr - nl)/2;
        return Query(2*node+1,nl,mid,l,r,k) + Query(2*node+2,mid+1,nr,l,r,k);
    }
};
