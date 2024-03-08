struct dsu {
    vector<pair<int,int>>parent;//parent and distant to the leader
    vector<int>rank;
    dsu(int n){
        parent.resize(n);
        rank.resize(n);
        for(int i=0;i<n;i++)make_set(i);
    }
    void make_set(int v) {
        parent[v] = make_pair(v, 0);
        rank[v] = 0;
    }

    pair<int, int> find(int v) {
        if (v != parent[v].first) {
            int len = parent[v].second;
            parent[v] = find(parent[v].first);
            parent[v].second += len;
        }
        return parent[v];
    }

    bool merge(int a, int b) {
        a = find(a).first;
        b = find(b).first;
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = make_pair(a, 1);
            if (rank[a] == rank[b])
                rank[a]++;
            return true;
        }
        return false;
    }
};