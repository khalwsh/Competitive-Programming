const int N = 1e5 + 10;
int dfn[N], LowLink[N], ndfn = 0, comp[N];
int ID = 1;
vector<int> adj[N];
bool IsArtPoints[N];
vector<int> ArtPoints;

int p[N];
int tin[N], tout[N];

void Tarjan(int node, int parent){
    p[node] = parent;
    dfn[node] = LowLink[node] = ndfn++;
    tin[node] = dfn[node];
    tout[node] = dfn[node];
    comp[node] = ID;
    int child = 0;
    for (auto &val : adj[node]) {
        if (dfn[val] == -1) {
            child++;
            Tarjan(val, node);
            LowLink[node] = min(LowLink[node], LowLink[val]);
            tout[node] = max(tout[node], tout[val]);
            if (LowLink[val] >= dfn[node]) {
                if (parent == -1 && child <= 1) continue;
                IsArtPoints[node] = true;
            }
        } else if (parent != val) {
            LowLink[node] = min(LowLink[node], dfn[val]);
        }
    }
}

void Art(int n){
    ndfn = 0;
    for (int i = 0; i < n; i++) {
        dfn[i] = -1;
        IsArtPoints[i] = false;
        LowLink[i] = 0;
        tin[i] = tout[i] = 0;
        p[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) Tarjan(i, -1), ID++;
    }
    for (int i = 0; i < n; i++) {
        if (IsArtPoints[i]) ArtPoints.emplace_back(i);
    }
}

// calculate art points and send 0 base
bool is_bottle_neck(int a , int b , int c) {
    if (a == c || b == c || comp[a] != comp[b]) {
        return true;
    }
    if (!IsArtPoints[c]) {
        return false;
    }
    int ida = -1, idb = -1;
    int idx = 0;
    for (auto child : adj[c]) {
        if (p[child] != c) continue;
        if (LowLink[child] >= dfn[c]) {
            if (tin[child] <= tin[a] && tin[a] <= tout[child]) ida = idx;
            if (tin[child] <= tin[b] && tin[b] <= tout[child]) idb = idx;
            idx++;
        }
    }
    if (ida == -1 && idb == -1 || ida != -1 && idb != -1 && ida == idb) return false;
    else return true;
}