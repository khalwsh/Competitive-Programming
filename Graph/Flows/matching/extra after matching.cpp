int n, m;                        // sizes: left = n, right = m
vector<vector<int>> g;           // adjacency: left u -> list of right vertices v
vector<int> matchL, matchR;      // matchL[u] = v (or -1), matchR[v] = u (or -1)
vector<int> seen;                // seen[v] holds timestamp when visited
int seen_id = 1;                 // increment per DFS call
 
void init(int _n, int _m) {
    n = _n; m = _m;
    g.assign(n, {});
    matchL.assign(n, -1);
    matchR.assign(m, -1);
    seen.assign(m, 0);
    seen_id = 1;
}
 
void add_edge(int u, int v) {
    g[u].push_back(v);
}
bool dfs(int u) {
        for (int v : g[u]) {
            if (seen[v] == seen_id) continue;
            seen[v] = seen_id;
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }
 
bool try_kuhn(int u) {
    if (matchL[u] != -1) return false; // already matched — no new augment
    ++seen_id;
    return dfs(u);
}
 
int max_matching(){
    int ans = 0;
    for(int i = 0; i < n; ++i) ans += try_kuhn(i);
    return ans;
}
 
int extra_matches_if_plugged(int u_left, int extra) {
    vector<int> lmatch = matchL;
    vector<int> rmatch = matchR;
    vector<int> seenR(m, 0);
    int cur_id = 0;
 
    function<bool(int)> dfs_local = [&](int u)->bool {
        for (int v : g[u]) {
            if (seenR[v] == cur_id) continue;
            seenR[v] = cur_id;
            if (rmatch[v] == -1 || dfs_local(rmatch[v])) {
                rmatch[v] = u;
                if (u < n) lmatch[u] = v;
                return true;
            }
        }
        return false;
    };
 
    int added = 0;
    for (int i = 0; i < extra; ++i) {
        cur_id++;
        if (dfs_local(u_left)) ++added;
        else break;
    }
    return added;
}