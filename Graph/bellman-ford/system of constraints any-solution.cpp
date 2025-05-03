struct DiffConstraintsAny {
    std::vector<std::array<int,3>> constraints;  // {u, v, C} for X_u - X_v >= C
    int num_vars = 0;

    void setNumVariables(int n) {
        num_vars = n;
    }

    void addConstraint(int u, int v, ll C) {
        constraints.push_back({u, v, static_cast<int>(C)});
    }

    bool isSolvable() const {
        std::vector<ll> dist(num_vars, 0);
        int m = constraints.size();
        for (int i = 0; i < num_vars; ++i) {
            bool updated = false;
            for (int j = 0; j < m; ++j) {
                int u = constraints[j][0];
                int v = constraints[j][1];
                ll C  = constraints[j][2];
                if (dist[u] < dist[v] + C) {
                    dist[u] = dist[v] + C;
                    updated = true;
                }
            }
            if (!updated) return true;
            if (i == num_vars - 1) return false;
        }
        return true;
    }

    std::vector<ll> getAnyValues() const {
        std::vector<ll> dist(num_vars, 0);
        int m = constraints.size();
        for (int i = 0; i < num_vars - 1; ++i) {
            for (int j = 0; j < m; ++j) {
                int u = constraints[j][0];
                int v = constraints[j][1];
                ll C  = constraints[j][2];
                dist[u] = std::max(dist[u], dist[v] + C);
            }
        }
        return dist;
    }
};