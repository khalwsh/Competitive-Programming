/* problem statement text */
/*
CSES - Bus Companies

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm bus companies. Each bus company operates in specific cities and sells tickets for a specific price. Buying a ticket from a bus company allows you to travel between any two cities that the company operates in.
Determine the cost of the cheapest route from Syrjälä to every city.
Input
The first line has two integers nnn and mmm: the number of cities and bus companies. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n, and city 111 is Syrjälä.
The next line has mmm integers c1,c2,…,cmc_1, c_2,\dots, c_mc1​,c2​,…,cm​: the ticket costs for each bus company.
After that, there are mmm pairs of lines describing the cities for each bus company.
The first line of each pair has a single integer kkk: the number of cities the bus company operates in.
The second line of each pair has kkk distinct integers a1,a2,…,aka_1, a_2,\dots, a_ka1​,a2​,…,ak​: the cities the bus company operates in.
You can assume that it is possible to travel from Syrjälä to all other cities.
Output
Print nnn integers: the cheapest route costs from Syrjälä to cities 1,2,…,n1,2,\dots, n1,2,…,n.
Constraints

1≤n,m≤1051 \le n, m \le 10^51≤n,m≤105
1≤c≤1091 \le c \le 10^91≤c≤109
2≤k≤n2 \le k \le n2≤k≤n
1≤a≤n1 \le a \le n1≤a≤n
the sum of all kkk is at most 2⋅1052 \cdot 10^52⋅105

Example
Input:
5 3
4 3 2
3
1 4 3
2
5 1
4
2 3 4 5

Output:
0 5 4 4 3
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
const int N = 5e5 + 10;
ll c[N] , dist[N];
vector<array<ll , 2>> adj[N];
int n , m;
void dijkstra() {
    memset(dist , '?' , sizeof dist);
    priority_queue<array<ll , 2> , vector<array<ll , 2>> , greater<>> pq;
    pq.push({0 , 1});
    dist[1] = 0;
    while (!pq.empty()) {
        auto [cost , u] = pq.top();
        pq.pop();
        if (cost != dist[u]) continue;
        for (auto &[v , w] : adj[u]) {
            if (dist[v] > w + cost) {
                dist[v] = w + cost;
                pq.push({dist[v] , v});
            }
        }
    }
}
int main() {
    PRE();
    cin >> n >> m;
    for (int i = 1;i <= m;i++)
        cin >> c[i];
    for (int i = 1;i <= m;i++) {
        int x; cin >> x;
        int u = n + i;
        while (x--) {
            int v;cin >> v;
            adj[u].emplace_back(array<ll , 2>{v , 0});
            adj[v].emplace_back(array<ll , 2>{u , c[i]});
        }
    }
    dijkstra();
    for (int i = 1;i <= n;i++) {
        cout << dist[i] << " ";
    }
}