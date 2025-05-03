struct DiffConstraintsMin {
    vector<array<ll,3>> constraints;  // {u, v, C} for X_u - X_v >= C
    int num_vars = 0;

    void setNumVariables(int n) {
        num_vars = n;
    }

    void addConstraint(int u, int v, ll C) {
        constraints.push_back({u, v, C});
    }

    bool isSolvableMin() {
        int n = num_vars;
        vector<ll> dist(n, 0);
        int m = constraints.size();
        for (int i = 0; i < n; ++i) {
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
            if (i == n - 1) return false;
        }
        return true;
    }

    vector<ll> getMinValues() const {
        int n = num_vars;
        vector<ll> dist(n, 0);
        int m = constraints.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < m; ++j) {
                int u = constraints[j][0];
                int v = constraints[j][1];
                ll C  = constraints[j][2];
                dist[u] = max(dist[u], dist[v] + C);
            }
        }
        return dist;
    }
};