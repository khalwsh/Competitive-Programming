/* problem statement text */
/*
CSES - Nearest Shops

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm roads. Each road is bidirectional and connects two cities. It is also known that kkk cities have an anime shop.
If you live in a city, you of course know the local anime shop well if there is one. You would like to find the nearest anime shop that is not in your city.
For each city, determine the minimum distance to another city that has an anime shop.
Input
The first line has three integers nnn, mmm and kkk: the number of cities, roads and anime shops. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The next line contains kkk integers: the cities that have an anime shop.
Finally, there are mmm lines that describe the roads. Each line has two integers aaa and bbb: there is a road between cities aaa and bbb.
Output
Print nnn integers: for each city, the minimum distance to another city with an anime shop. If there is no such city, print −1-1−1 instead.
Constraints

1≤k≤n≤1051 \le k \le n \le 10^51≤k≤n≤105
0≤m≤2⋅1050 \le m \le 2 \cdot 10^50≤m≤2⋅105

Example
Input:
9 6 4
2 4 5 7
1 2
1 3
1 8
2 4
3 4
5 6

Output:
1 1 1 1 -1 1 -1 2 -1
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
vector<int> adj[N];
int n , m , k;
bool is_shop[N];
int dist[2][N];
int src[N];
int main() {
    PRE();
    cin >> n >> m >> k;
    queue<array<int , 3>> q;
    memset(dist , -1 , sizeof dist);
    memset(src , -1 , sizeof src);
    for (int i = 0;i < k;i++) {
        int x;cin >> x;
        is_shop[x] = true;
        q.push({x , x , 0});
        dist[0][x] = 0;
        src[x] = x;
    }
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    while (!q.empty()) {
        auto [u , source , st] = q.front();
        q.pop();
        for (auto &v : adj[u]) {
            if (dist[0][v] == -1) {
                dist[0][v] = dist[st][u] + 1;
                src[v] = source;
                q.push({v , source , 0});
            }else if (dist[1][v] == -1 && source != src[v]) {
                dist[1][v] = dist[st][u] + 1;
                q.push({v , source , 1});
            }
        }
    }
    for (int i = 1;i <= n;i++) {
        if (is_shop[i]) cout << dist[1][i] << " ";
        else cout << dist[0][i] << " ";
    }
}