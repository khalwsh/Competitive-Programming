struct DiffConstraintsMax {
    std::vector<std::array<int,3>> constraints;  // {u, v, C} for X_u - X_v >= C
    int num_vars = 0;

    void setNumVariables(int n) {
        num_vars = n;
    }

    void addConstraint(int u, int v, ll C) {
        constraints.push_back({u, v, static_cast<int>(C)});
    }

    // Check feasibility (no negative cycle) by transforming variables Y = -X
    bool isSolvable() const {
        std::vector<ll> dist(num_vars, 0);
        int m = constraints.size();
        for (int i = 0; i < num_vars; ++i) {
            bool updated = false;
            for (int j = 0; j < m; ++j) {
                int u = constraints[j][0];
                int v = constraints[j][1];
                ll C  = constraints[j][2];
                if (dist[v] < dist[u] + C) {
                    dist[v] = dist[u] + C;
                    updated = true;
                }
            }
            if (!updated) return true;
            if (i == num_vars - 1) return false;
        }
        return true;
    }

    vector<ll> getMaxValues() const {
        std::vector<ll> dist(num_vars, 0);
        int m = constraints.size();
        for (int i = 0; i < num_vars - 1; ++i) {
            for (int j = 0; j < m; ++j) {
                int u = constraints[j][0];
                int v = constraints[j][1];
                ll C  = constraints[j][2];
                dist[v] = max(dist[v], dist[u] + C);
            }
        }
        vector<ll> result(num_vars);
        for (int i = 0; i < num_vars; ++i) result[i] = -dist[i];
        return result;
    }
};