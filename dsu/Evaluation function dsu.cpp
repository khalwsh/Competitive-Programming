struct EvalDsu{
    vector<int>parent,lazy;
    EvalDsu(int _n){
        parent.resize(_n);
        lazy.resize(_n);
        iota(parent.begin(),parent.end(),0ll);
    }
    int find(int u){
        if(u != parent[u]){
            int leader = find(parent[u]);
            lazy[u] += lazy[parent[u]];
            parent[u] = leader;
        }
        return parent[u];
    }
    bool same(int u,int v){
        return find(u) == find(v);
    }
    bool merge(int u,int v){
        //u is the parent , v = leader of the set must be like that
        if(same(u,v))return false;
        lazy[u] += f(u,v);
        parent[v] = u;
        return true;
    }
    int eval(int u){
        find(u);
        //evaluate function from u to leader of u
        //work in this path
        return lazy[u];
    }
    int f(int x,int y){
        //write your work here and f must be asscioative   f(a,f(b,c)) == f(f(a,b),c)
        return 0;
    }
};