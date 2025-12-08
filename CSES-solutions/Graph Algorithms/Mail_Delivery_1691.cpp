/* problem statement text */
/*
CSES - Mail Delivery

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to deliver mail to the inhabitants of a city. For this reason, you want to find a route whose starting and ending point are the post office, and that goes through every street exactly once.
Input
The first input line has two integers nnn and mmm: the number of crossings and streets. The crossings are numbered 1, 2,…, n1,\,2,\ldots,\,n1,2,…,n, and the post office is located at crossing 111.
After that, there are m lines describing the streets. Each line has two integers aaa and bbb: there is a street between crossings aaa and bbb. All streets are two-way streets.
Every street is between two different crossings, and there is at most one street between two crossings.
Output
Print all the crossings on the route in the order you will visit them. You can print any valid solution.
If there are no solutions, print "IMPOSSIBLE".
Constraints
2≤n≤1052\leq n\leq 10^52≤n≤105
1≤m≤2⋅1051\leq m\leq 2 \cdot 10^51≤m≤2⋅105
1≤a, b≤n1\leq a,\,b\leq n1≤a,b≤n
Example
Input:
6 8
1 2
1 3
2 3
2 4
2 6
3 5
3 6
4 5

Output:
1 2 6 3 2 4 5 3 1
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
const int N = 2e5 + 10;
int n, m;
multiset<int> adj[N];
int deg[N];
vector<int> tour;
 
void dfs(int u) {
    while (!adj[u].empty()) {
        auto it = adj[u].begin();
        int v = *it;
        adj[u].erase(it);
        if (u != v) {
            auto it_rev = adj[v].find(u);
            if (it_rev != adj[v].end()) {
                adj[v].erase(it_rev);
            }
        }
        dfs(v);
    }
    tour.emplace_back(u);
}
 
bool check() {
    for (int i = 0; i < n; ++i) {
        if (deg[i] & 1) return false;
    }
    return true;
}
 
bool isConnected() {
    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (deg[i] > 0) { start = i; break; }
    }
    if (start == -1) return true;
 
    vector<char> vis(n, 0);
    stack<int> st;
    st.push(start);
    vis[start] = 1;
    while (!st.empty()) {
        int v = st.top(); st.pop();
        for (int u : adj[v]) {
            if (!vis[u]) {
                vis[u] = 1;
                st.push(u);
            }
        }
    }
 
    for (int i = 0; i < n; ++i) {
        if (deg[i] > 0 && !vis[i]) return false;
    }
    return true;
}
 
bool get() {
    if (!check()) return false;
    if (!isConnected()) return false;
 
    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (deg[i] > 0) { start = i; break; }
    }
    if (start == -1) {
        return (m == 0);
    }
 
    tour.clear();
    dfs(start);
    reverse(tour.begin(), tour.end());
    return (int)tour.size() == m + 1;
}
int main() {
    PRE();cin >> n >> m;
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        adj[u].insert(v);
        adj[v].insert(u);
        deg[u]++ , deg[v]++;
    }
    if (!get() || tour.front() != 0) {
        cout << "IMPOSSIBLE\n";
    }else {
        for (auto &val : tour) cout << ++val << " ";
    }
 
}