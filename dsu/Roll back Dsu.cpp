struct RollBackDsu{
    vector<int>parent,size;
    stack<pair<pair<int,int>,pair<int,int>>>sk;
    RollBackDsu(int _n){
        parent.resize(_n);
        iota(parent.begin(),parent.end(),0ll);
        size.resize(_n,1);
    }
    int find(int child){
        return (child == parent[child]?child:find(parent[child]));
    }
    bool Merge(int a,int b){
        a = find(a);
        b = find(b);
        if(a==b)return false;
        if(size[a]>size[b])swap(a,b);
        sk.push({{a,parent[a]},{b,size[b]}});
        parent[a] = b;
        size[b] += size[a];
        return true;
    }
    void RollBack(int cnt){
        assert(cnt <= sk.size());
        while(cnt--){
            auto it = sk.top();
            sk.pop();
            parent[it.first.first] = it.first.second;
            size[it.second.first] = it.second.second;
        }
    }
};
