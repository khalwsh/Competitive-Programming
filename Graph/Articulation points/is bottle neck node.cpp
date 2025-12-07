const int N = 1e5 + 10;
int dfn[N], LowLink[N], ndfn = 0, comp[N];
int ID = 1;
vector<int> adj[N];
bool IsArtPoints[N];
vector<int> ArtPoints;

int p[N];
int tin[N], tout[N];

vector<vector<pair<int,int>>> artIntervals;

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
    ArtPoints.clear();
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) Tarjan(i, -1), ID++;
    }
    for (int i = 0; i < n; i++) {
        if (IsArtPoints[i]) ArtPoints.emplace_back(i);
    }
    artIntervals.assign(n, {});
    for (int c : ArtPoints) {
        vector<pair<int,int>> intervals;
        for (int child : adj[c]) {
            if (p[child] != c) continue;
            if (LowLink[child] >= dfn[c]) {
                intervals.emplace_back(tin[child], tout[child]);
            }
        }
        sort(intervals.begin(), intervals.end());
        artIntervals[c] = std::move(intervals);
    }
}

bool is_bottle_neck(int a , int b , int c) {
    if (a == c || b == c || comp[a] != comp[b]) {
        return true;
    }
    if (!IsArtPoints[c]) {
        return false;
    }
    auto &v = artIntervals[c];
    auto find_idx = [&](int x)->int {
        if (v.empty()) return -1;
        int t = tin[x];
        auto it = upper_bound(v.begin(), v.end(), make_pair(t, INT_MAX));
        if (it == v.begin()) return -1;
        --it;
        if (it->first <= t && t <= it->second) return int(it - v.begin());
        return -1;
    };

    int ida = find_idx(a), idb = find_idx(b);
    if ((ida == -1 && idb == -1) || (ida != -1 && idb != -1 && ida == idb)) return false;
    else return true;
}