/* problem statement text */
/*
CSES - Forbidden Cities

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm roads between them. Kaaleppi is currently in city aaa and wants to travel to city bbb.
However, there is a problem: Kaaleppi has recently robbed a bank in city ccc and can't enter the city, because the local police would catch him. Your task is to find out if there is a route from city aaa to city bbb that does not visit city ccc.
As an additional challenge, you have to process qqq queries where aaa, bbb and ccc vary.
Input
The first input line has three integers nnn, mmm and qqq: the number of cities, roads and queries. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are mmm lines describing the roads. Each line has two integers aaa and bbb: there is a road between cities aaa and bbb. Each road is bidirectional.
Finally, there are qqq lines describing the queries. Each line has three integers aaa, bbb and ccc: is there a route from city aaa to city bbb that does not visit city ccc?
You can assume that there is a route between any two cities.
Output
For each query, print "YES", if there is such a route, and "NO" otherwise.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤q≤1051 \le q \le 10^51≤q≤105
1≤a,b,c≤n1 \le a,b,c \le n1≤a,b,c≤n

Example
Input:
5 6 3
1 2
1 3
2 3
2 4
3 4
4 5
1 4 2
3 5 4
3 5 2

Output:
YES
NO
YES
*/
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
int main() {
    PRE();
    int n, m, q; cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    Art(n);
    for (int i = 0; i < q; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--, c--;
        cout << (!is_bottle_neck(a , b , c) ? "YES" : "NO") << '\n';
    }
}