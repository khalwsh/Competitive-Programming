const ll inf = 1e18
template <class T>
struct MCMF {
    struct edge {
        int u, v;
        T cap, cost;
        int id;

        edge(int _u, int _v, T _cap, T _cost, int _id)
                : u(_u), v(_v), cap(_cap), cost(_cost), id(_id) {}
    };

    int n, s, t, mxid;
    T flow, cost;
    vector<vector<int>> g;
    vector<edge> e;
    vector<T> d, potential, flow_through;
    vector<int> par;
    bool neg;

    MCMF() {}

    MCMF(int _n) {
        n = _n + 10;
        g.assign(n, {});
        neg = false;
        mxid = 0;
    }

    void add_edge(int u, int v, T cap, T cost, int id = -1, bool directed = true) {
        if (cost < 0) neg = true;
        g[u].push_back(e.size());
        e.emplace_back(u, v, cap, cost, id);
        g[v].push_back(e.size());
        e.emplace_back(v, u, 0, -cost, -1);
        mxid = max(mxid, id);
        if (!directed) add_edge(v, u, cap, cost, -1, true);
    }

    bool dijkstra() {
        par.assign(n, -1);
        d.assign(n, inf);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;

        d[s] = 0;
        q.emplace(0, s);

        while (!q.empty()) {
            int u = q.top().second;
            T nw = q.top().first;
            q.pop();

            if (nw != d[u]) continue;

            for (int i = 0; i < (int) g[u].size(); i++) {
                int id = g[u][i];
                int v = e[id].v;
                T cap = e[id].cap;
                T w = e[id].cost + potential[u] - potential[v];

                if (d[u] + w < d[v] && cap > 0) {
                    d[v] = d[u] + w;
                    par[v] = id;
                    q.emplace(d[v], v);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (d[i] < inf) d[i] += (potential[i] - potential[s]);
        }

        for (int i = 0; i < n; i++) {
            if (d[i] < inf) potential[i] = d[i];
        }

        return d[t] != inf;  // for max flow min cost
        // return d[t] <= 0; // for min cost flow
    }

    T send_flow(int v, T cur) {
        if (par[v] == -1) return cur;
        int id = par[v];
        int u = e[id].u;
        T w = e[id].cost;
        T f = send_flow(u, min(cur, e[id].cap));

        cost += f * w;
        e[id].cap -= f;
        e[id ^ 1].cap += f;

        return f;
    }

    // Returns {maxflow, mincost}
    pair<T, T> solve(int _s, int _t, T goal = inf) {
        s = _s;
        t = _t;
        flow = 0;
        cost = 0;
        potential.assign(n, 0);

        if (neg) {
            d.assign(n, inf);
            d[s] = 0;
            bool relax = true;

            for (int i = 0; i < n && relax; i++) {
                relax = false;
                for (int u = 0; u < n; u++) {
                    for (int k = 0; k < (int) g[u].size(); k++) {
                        int id = g[u][k];
                        int v = e[id].v;
                        T cap = e[id].cap;
                        T w = e[id].cost;

                        if (d[v] > d[u] + w && cap > 0) {
                            d[v] = d[u] + w;
                            relax = true;
                        }
                    }
                }
            }

            for (int i = 0; i < n; i++) {
                if (d[i] < inf) potential[i] = d[i];
            }
        }

        while (flow < goal && dijkstra()) {
            flow += send_flow(t, goal - flow);
        }

        flow_through.assign(mxid + 10, 0);

        for (int u = 0; u < n; u++) {
            for (auto id : g[u]) {
                if (e[id].id >= 0) {
                    flow_through[e[id].id] = e[id ^ 1].cap;
                }
            }
        }

        return {flow, cost};
    }
};