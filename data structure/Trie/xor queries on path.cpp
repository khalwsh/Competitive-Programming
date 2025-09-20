#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}

const int N = 100000 + 5;
const int MAXTR = 32 * N;
const int K = 20;
const int MAXBIT = 29;

int n, q;
vector<pair<int, int> > g[N];
int parentArr[N], depthArr[N], heavy[N], sz[N];
int headArr[N], pos[N], curPos;
int xorRoot[N];
int baseVal[N];

int lc[MAXTR], rc[MAXTR], cntT[MAXTR], totT;
int rootTrie[N];

int newNode() {
    ++totT;
    lc[totT] = rc[totT] = cntT[totT] = 0;
    return totT;
}

int insertTrie(int prev, int val) {
    int cur = newNode();
    lc[cur] = lc[prev];
    rc[cur] = rc[prev];
    cntT[cur] = cntT[prev] + 1;
    int curPrev = prev;
    int curNew = cur;
    for (int b = MAXBIT; b >= 0; --b) {
        int bit = (val >> b) & 1;
        int prevChild = bit ? rc[curPrev] : lc[curPrev];
        int newChild = newNode();
        lc[newChild] = lc[prevChild];
        rc[newChild] = rc[prevChild];
        cntT[newChild] = cntT[prevChild] + 1;
        if (bit) rc[curNew] = newChild;
        else lc[curNew] = newChild;
        curPrev = prevChild;
        curNew = newChild;
    }
    return cur;
}

int queryTrie(int oldR, int newR, int x) {
    int res = 0;
    int curOld = oldR, curNew = newR;
    for (int b = MAXBIT; b >= 0; --b) {
        int bit = (x >> b) & 1;
        int want = !bit;
        int newChild = want ? rc[curNew] : lc[curNew];
        int oldChild = want ? rc[curOld] : lc[curOld];
        int have = cntT[newChild] - cntT[oldChild];
        if (have > 0) {
            res |= (1 << b);
            curNew = newChild;
            curOld = oldChild;
        } else {
            curNew = bit ? rc[curNew] : lc[curNew];
            curOld = bit ? rc[curOld] : lc[curOld];
        }
        if (!curNew && !curOld) break;
    }
    return res;
}

void dfs1(int u, int p) {
    parentArr[u] = p;
    depthArr[u] = (p ? depthArr[p] + 1 : 0);
    sz[u] = 1;
    heavy[u] = -1;
    for (auto &e: g[u]) {
        int v = e.first, w = e.second;
        if (v == p) continue;
        xorRoot[v] = xorRoot[u] ^ w;
        dfs1(v, u);
        if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) heavy[u] = v;
        sz[u] += sz[v];
    }
}

void dfs2(int u, int h) {
    headArr[u] = h;
    pos[u] = ++curPos;
    baseVal[curPos] = xorRoot[u];
    if (heavy[u] != -1) dfs2(heavy[u], h);
    for (auto &e: g[u]) {
        int v = e.first;
        if (v == parentArr[u] || v == heavy[u]) continue;
        dfs2(v, v);
    }
}

int pathQuery(int u, int v) {
    int constVal = xorRoot[u];
    int ans = 0;
    while (headArr[u] != headArr[v]) {
        if (depthArr[headArr[u]] < depthArr[headArr[v]]) swap(u, v);
        int l = pos[headArr[u]], r = pos[u];
        ans = max(ans, queryTrie(rootTrie[l - 1], rootTrie[r], constVal));
        u = parentArr[headArr[u]];
    }
    if (depthArr[u] > depthArr[v]) swap(u, v);
    int l = pos[u], r = pos[v];
    ans = max(ans, queryTrie(rootTrie[l - 1], rootTrie[r], constVal));
    return ans;
}

int main() {
    PRE();
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        cin >> n >> q;
        for (int i = 1; i <= n; ++i) {
            g[i].clear();
            parentArr[i] = depthArr[i] = heavy[i] = sz[i] = headArr[i] = pos[i] = 0;
            xorRoot[i] = 0;
        }
        for (int i = 0; i < n - 1; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        curPos = 0;
        totT = 0;
        lc[0] = rc[0] = cntT[0] = 0;
        xorRoot[1] = 0;
        dfs1(1, 0);
        dfs2(1, 1);
        rootTrie[0] = 0;
        for (int i = 1; i <= n; ++i) {
            rootTrie[i] = insertTrie(rootTrie[i - 1], baseVal[i]);
        }
        while (q--) {
            int u, v;
            cin >> u >> v;
            cout << pathQuery(u, v) << '\n';
        }
    }
    return 0;
}