/* problem statement text */
/*
CSES - Parcel Delivery

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm routes through which parcels can be carried from one city to another city. For each route, you know the maximum number of parcels and the cost of a single parcel.
You want to send kkk parcels from Syrjälä to Lehmälä. What is the cheapest way to do that?
Input
The first input line has three integers nnn, mmm and kkk: the number of cities, routes and parcels. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n. City 111 is Syrjälä and city nnn is Lehmälä.
After this, there are mmm lines that describe the routes. Each line has four integers aaa, bbb, rrr and ccc: there is a route from city aaa to city bbb, at most rrr parcels can be carried through the route, and the cost of each parcel is ccc.
Output
Print one integer: the minimum total cost or −1-1−1 if there are no solutions.
Constraints

2≤n≤5002 \le n \le 5002≤n≤500
1≤m≤10001 \le m \le 10001≤m≤1000
1≤k≤1001 \le k \le 1001≤k≤100
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤r,c≤10001 \le r,c \le 10001≤r,c≤1000

Example
Input:
4 5 3
1 2 5 100
1 3 10 50
1 4 7 500
2 4 8 350
3 4 2 100

Output:
750

Explanation: One parcel is delivered through route 1→2→41 \rightarrow 2 \rightarrow 41→2→4 (cost 1⋅450=4501 \cdot 450=4501⋅450=450) and two parcels are delivered through route 1→3→41 \rightarrow 3 \rightarrow 41→3→4 (cost 2⋅150=3002 \cdot 150=3002⋅150=300).
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
 
struct Edge {
    int to;
    ll cost;
    int cap, flow, backEdge;
};
 
struct MCMF
{
    const int OO = 1e9 + 10;
    const int inf = 1000000010;
    int n;
    vector<vector<Edge>> g;
 
    MCMF(int _n) {
        n = _n + 1;
        g.resize(n);
    }
 
    void addEdge(int u, int v, int cap, ll cost) {
        Edge e1 = {v, cost, cap, 0, (int) g[v].size()};
        Edge e2 = {u, -cost, 0, 0, (int) g[u].size()};
        g[u].push_back(e1);
        g[v].push_back(e2);
    }
 
    pair<ll, int> minCostMaxFlow(int s, int t) {
        int flow = 0;
        ll cost = 0;
        vector<int> state(n), from(n), from_edge(n);
        vector<ll> d(n);
        deque<int> q;
        while (true) {
            for (int i = 0; i < n; i++)
                state[i] = 2, d[i] = OO, from[i] = -1;
            state[s] = 1;
            q.clear();
            q.push_back(s);
            d[s] = 0;
            while (!q.empty()) {
                int v = q.front();
                q.pop_front();
                state[v] = 0;
                for (int i = 0; i < (int) g[v].size(); i++) {
                    Edge e = g[v][i];
                    if (e.flow >= e.cap || (d[e.to] <= d[v] + e.cost))
                        continue;
                    int to = e.to;
                    d[to] = d[v] + e.cost;
                    from[to] = v;
                    from_edge[to] = i;
                    if (state[to] == 1) continue;
                    if (!state[to] || (!q.empty() && d[q.front()] > d[to]))
                        q.push_front(to);
                    else q.push_back(to);
                    state[to] = 1;
                }
            }
            if (d[t] == OO) break;
            int it = t, addflow = inf;
            while (it != s) {
                addflow = min(addflow,
                              g[from[it]][from_edge[it]].cap
                              - g[from[it]][from_edge[it]].flow);
                it = from[it];
            }
            it = t;
            while (it != s) {
                g[from[it]][from_edge[it]].flow += addflow;
                g[it][g[from[it]][from_edge[it]].backEdge].flow -= addflow;
                cost += g[from[it]][from_edge[it]].cost * addflow;
                it = from[it];
            }
            flow += addflow;
        }
        return {cost, flow};
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n , m , k;cin>>n>>m>>k;
    MCMF f(n + 1);
    int dummy_source = n;
    int source = 0;
    f.addEdge(dummy_source , source , k , 0);
    for(int i = 0;i < m;i++) {
        int u , v , w , c;cin>>u>>v>>w>>c;
        u-- , v--;
        f.addEdge(u , v , w , c);
    }
    auto x = f.minCostMaxFlow(dummy_source , n - 1);
    if(x.second == k)
        cout<<x.first;
    else
        cout<<-1;
}