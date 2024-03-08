struct dsu {
    vector<int>rank,bipartite;
    vector<pair<int,int>>parent;
    dsu(int _n){
        rank.resize(_n),bipartite.resize(_n);
        parent.resize(_n);
        for(int i=0;i<_n;i++)make_set(i);
    }
    void make_set(int v) {
        parent[v] = make_pair(v, 0);
        rank[v] = 0;
        bipartite[v] = true;
    }

    pair<int, int> find(int v) {
        if (v != parent[v].first) {
            int parity = parent[v].second;
            parent[v] = find(parent[v].first);
            parent[v].second ^= parity;
        }
        return parent[v];
    }

    void add_edge(int a, int b) {
        pair<int, int> pa = find(a);
        a = pa.first;
        int x = pa.second;

        pair<int, int> pb = find(b);
        b = pb.first;
        int y = pb.second;

        if (a == b) {
            if (x == y)
                bipartite[a] = false;
        } else {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = make_pair(a, x ^ y ^ 1);
            bipartite[a] &= bipartite[b];
            if (rank[a] == rank[b])
                ++rank[a];
        }
    }

    bool is_bipartite(int v) {
        return bipartite[find(v).first];
    }
};
