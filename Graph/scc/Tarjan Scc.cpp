struct SCC {
    int n;
    vector<vector<int>> adj;
    vector<ll> origWeight;
    vector<int> dag_in_degree;
    vector<int> dfn, lowLink, comp;
    vector<bool> inStack;
    stack<int> st;
    int timer;

    vector<vector<int>> components;
    vector<vector<int>> dag;
    vector<ll> compWeight;

    SCC(const vector<vector<int>>& graph, const vector<ll>& weight = {})
        : n(graph.size()), adj(graph) {
        if (weight.empty()) {
            origWeight.assign(n, 1);
        } else {
            if ((int)weight.size() != n)
                throw invalid_argument("Weight array size must match number of nodes");
            origWeight = weight;
        }
        dag_in_degree.resize(n);
        dfn.assign(n, -1);
        lowLink.assign(n, 0);
        comp.assign(n, -1);
        inStack.assign(n, false);
        timer = 0;

        for (int u = 0; u < n; u++) {
            if (dfn[u] == -1)
                tarjan(u);
        }

        buildDag();

        compWeight.assign(components.size(), 0);
        for (int u = 0; u < n; u++) {
            compWeight[ comp[u] ] += origWeight[u];
        }
    }
    const vector<vector<int>>& getSCCs() const {
        return components;
    }
    const vector<vector<int>>& getDAG() const {
        return dag;
    }
    const vector<ll>& getComponentWeights() const {
        return compWeight;
    }
    const vector<int>& getInDegree()const {
        return dag_in_degree;
    }

private:
    void tarjan(int u) {
        dfn[u] = lowLink[u] = timer++;
        inStack[u] = true;
        st.push(u);

        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                lowLink[u] = min(lowLink[u], lowLink[v]);
            } else if (inStack[v]) {
                lowLink[u] = min(lowLink[u], dfn[v]);
            }
        }

        if (lowLink[u] == dfn[u]) {
            components.emplace_back();
            while (true) {
                int x = st.top(); st.pop();
                inStack[x] = false;
                comp[x] = (int)components.size() - 1;
                components.back().push_back(x);
                if (x == u) break;
            }
        }
    }

    void buildDag() {
        int csz = components.size();
        dag.assign(csz, {});
        unordered_set<long long> seen;

        for (int u = 0; u < n; u++) {
            int cu = comp[u];
            for (int v : adj[u]) {
                int cv = comp[v];
                if (cu != cv) {
                    long long code = (long long)cu << 32 | (unsigned)cv;
                    if (seen.insert(code).second) {
                        dag_in_degree[cv]++;
                        dag[cu].push_back(cv);
                    }
                }
            }
        }
    }
};