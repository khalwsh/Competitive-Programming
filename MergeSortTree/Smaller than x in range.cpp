struct MergeSortTree{
    vector<vector<int>>tree;
    MergeSortTree(int n){
        tree.resize(4 * n);
    }
    void build(int node , int nl,int nr , vector<int>&a){
        if(nl == nr){
            tree[node].emplace_back(a[nl]);
            return;
        }
        int mid = nl + (nr - nl) / 2;
        build(2 * node + 1 , nl , mid , a);
        build(2 * node + 2 , mid + 1 , nr , a);
        merge(tree[2 * node + 1].begin(), tree[2 * node + 1].end(),tree[2 * node + 2].begin(), tree[2 * node + 2].end(),back_inserter(tree[node]));
    }
    int query(int node,int nl,int nr,int l ,int r,int value){
        // less than
        if(nl >=l && nr <= r){
            return (int)(lower_bound(tree[node].begin() , tree[node].end() , value) - tree[node].begin());
        }
        if(nl > r || nr < l)return 0;
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1 , nl , mid , l , r ,value) + query(2 * node + 2 , mid + 1 , nr , l , r , value);
    }
};