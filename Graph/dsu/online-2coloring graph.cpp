struct DSU {
    vector<int> parent, rank, parity;
    vector<bool> bipartite;
    bool whole_graph_bipartite = true;

    struct Change {
        int v;
        int parent, rnk, prt;
        bool bip;
        bool global_bip;
    };
    vector<Change> history;

    DSU(int n): parent(n), rank(n, 0), parity(n, 0), bipartite(n, true){
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    pair<int,int> find(int v) const {
        if (parent[v] == v)
            return {v, 0};
        auto pr = find(parent[v]);
        return { pr.first, pr.second ^ parity[v] };
    }

    void rollback_steps(int steps) {
        while (steps-- > 0 && !history.empty()) {
            auto &c = history.back();
            parent[c.v]     = c.parent;
            rank[c.v]       = c.rnk;
            parity[c.v]     = c.prt;
            bipartite[c.v] = c.bip;
            whole_graph_bipartite = c.global_bip;
            history.pop_back();
        }
    }

    bool unite(int a, int b , int &ops) {
        auto [ra, xa] = find(a);
        auto [rb, xb] = find(b);
        if (ra == rb) {
            if (xa == xb) {
                history.push_back({ra, parent[ra], rank[ra], parity[ra], bipartite[ra], whole_graph_bipartite});
                bipartite[ra] = false;
                whole_graph_bipartite = false;
            } else {
                history.push_back({ra, parent[ra], rank[ra], parity[ra], bipartite[ra], whole_graph_bipartite});
            }
            ops++;
            return bipartite[ra];
        }

        if (rank[ra] < rank[rb]) {
            std::swap(ra, rb);
            std::swap(xa, xb);
        }
        ops += 2;
        history.push_back({ra, parent[ra], rank[ra], parity[ra], bipartite[ra], whole_graph_bipartite});
        history.push_back({rb, parent[rb], rank[rb], parity[rb], bipartite[rb], whole_graph_bipartite});

        parent[rb] = ra;
        parity[rb] = xa ^ xb ^ 1;
        bipartite[ra] = bipartite[ra] & bipartite[rb];

        if (!bipartite[ra]) whole_graph_bipartite = false;

        if (rank[ra] == rank[rb])
            rank[ra]++;

        return bipartite[ra];
    }

    bool is_bipartite(int v) const {
        return bipartite[find(v).first];
    }

    bool is_whole_graph_bipartite() const {
        return whole_graph_bipartite;
    }
};