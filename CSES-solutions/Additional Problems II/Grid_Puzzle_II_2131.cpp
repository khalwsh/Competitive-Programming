/* problem statement text */
/*
CSES - Grid Puzzle II

Time limit: 1.00 s
Memory limit: 512 MB

There is an n×nn \times nn×n grid whose each square has some number of coins in it.
You know for each row and column how many squares you must choose from that row or column. You get all coins from every square you choose. What is the maximum number of coins you can collect and how could you choose the squares so that the given conditions are satisfied?
Input
The first input line has an integer nnn: the size of the grid. The rows and columns are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The next line has nnn integers a1,a2,…,ana_1,a_2,\ldots,a_na1​,a2​,…,an​: You must choose exactly aia_iai​ squares from the iiith row.
The next line has nnn integers b1,b2,…,bnb_1,b_2,\ldots,b_nb1​,b2​,…,bn​: You must choose exactly bjb_jbj​ squares from the jjjth column.
Finally, there are nnn lines describing the grid. You can assume that the sums of a1,a2,…,ana_1,a_2,\ldots,a_na1​,a2​,…,an​ and b1,b2,…,bnb_1,b_2,\ldots,b_nb1​,b2​,…,bn​ are equal.
Output
First print an integer kkk: the maximum number of coins you can collect. After this print nnn lines describing which squares you choose (X means that you choose a square, . means that you don't choose it).
If it is not possible to satisfy the conditions print only −1-1−1.
Constraints

1≤n≤501 \le n \le 501≤n≤50
0≤ai≤n0 \le a_i \le n0≤ai​≤n
0≤bj≤n0 \le b_j \le n0≤bj​≤n
0≤cij≤10000 \le c_{ij} \le 10000≤cij​≤1000

Example
Input:
5
0 1 3 2 0
1 2 2 0 1
2 5 1 5 1
0 2 5 1 2
3 8 9 3 5
1 4 3 7 3
0 3 6 2 8

Output:
32
.....
..X..
.XX.X
XX...
.....
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
 
template<class T>
struct MCMF {
    struct edge {
        int u, v;
        T cap, cost;
 
        edge(int _u, int _v, T _cap, T _cost) : u(_u), v(_v), cap(_cap), cost(_cost) {
        }
    };
 
    int n, s, t;
    T flow, cost;
    vector<vector<int> > g;
    vector<edge> e;
    vector<T> d, potential;
    vector<int> par;
    bool neg;
 
    MCMF(int _n = 0) {
        n = _n + 5;
        g.assign(n, {});
        neg = false;
    }
 
    void add_edge(int u, int v, T cap, T cost) {
        assert(u >= 0 && u < n && v >= 0 && v < n);
        if (cost < 0) neg = true;
        g[u].push_back((int) e.size());
        e.emplace_back(u, v, cap, cost);
        g[v].push_back((int) e.size());
        e.emplace_back(v, u, 0, -cost);
    }
 
    bool dijkstra() {
        T INF = numeric_limits<T>::max() / 4;
        par.assign(n, -1);
        d.assign(n, INF);
        priority_queue<pair<T, int>, vector<pair<T, int> >, greater<> > pq;
        d[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();
            if (dist != d[u]) continue;
            for (int id: g[u]) {
                int v = e[id].v;
                T cap = e[id].cap;
                T w = e[id].cost + potential[u] - potential[v];
                if (cap > 0 && d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    par[v] = id;
                    pq.emplace(d[v], v);
                }
            }
        }
        for (int i = 0; i < n; ++i) if (d[i] < numeric_limits<T>::max() / 4) d[i] += (potential[i] - potential[s]);
        for (int i = 0; i < n; ++i) if (d[i] < numeric_limits<T>::max() / 4) potential[i] = d[i];
        return d[t] < numeric_limits<T>::max() / 4;
    }
 
    T send_flow(int v, T cur) {
        if (par[v] == -1) return cur;
        int id = par[v];
        int u = e[id].u;
        T f = send_flow(u, min(cur, e[id].cap));
        cost += f * e[id].cost;
        e[id].cap -= f;
        e[id ^ 1].cap += f;
        return f;
    }
 
    pair<T, T> solve(int _s, int _t, T goal = numeric_limits<T>::max() / 4) {
        s = _s;
        t = _t;
        flow = 0;
        cost = 0;
        potential.assign(n, 0);
        if (neg) {
            T INF = numeric_limits<T>::max() / 4;
            d.assign(n, INF);
            deque<int> q;
            vector<char> inq(n, 0);
            d[s] = 0;
            q.push_back(s);
            inq[s] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop_front();
                inq[u] = 0;
                for (int id: g[u]) {
                    int v = e[id].v;
                    T cap = e[id].cap;
                    T w = e[id].cost;
                    if (cap > 0 && d[u] < INF && d[v] > d[u] + w) {
                        d[v] = d[u] + w;
                        if (!inq[v]) {
                            inq[v] = 1;
                            q.push_back(v);
                        }
                    }
                }
            }
            for (int i = 0; i < n; ++i) if (d[i] < numeric_limits<T>::max() / 4) potential[i] = d[i];
        }
        while (flow < goal && dijkstra()) flow += send_flow(t, goal - flow);
        return {flow, cost};
    }
};
 
int main() {
    PRE();
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    vector<vector<int> > g(n, vector<int>(n));
    for (auto &val: a) cin >> val;
    for (auto &val: b) cin >> val;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    int src = 0, sink = 1;
    MCMF<ll> mf(12 + 2 * n);
    for (int i = 0; i < n; i++) {
        mf.add_edge(src, i + 2, a[i], 0);
        mf.add_edge(i + 2 + n, sink, b[i], 0);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mf.add_edge(i + 2, j + n + 2, 1, -g[i][j]);
        }
    }
    auto ans =  mf.solve(src, sink).second * -1;
    vector<vector<char> > res(n, vector<char>(n, '.'));
    bool fail = false;
    for (auto &e: mf.e) {
        if (e.u > 1 && e.u < 2 + n && e.v >= 2 + n && e.v < 2 + 2 * n && !e.cap) {
            res[e.u - 2][e.v - 2 - n] = 'X';
        }else if (e.u == 0) {
            // src
            fail = fail || e.cap != 0;
        }else if (e.v == 1) {
            fail = fail || e.cap != 0;
        }
    }
    if (fail) {
        cout << -1;
    }else {
        cout << ans << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j)
                cout << res[i][j];
            cout << '\n';
        }
    }
}