/* problem statement text */
/*
CSES - Longest Flight Route

Time limit: 1.00 s
Memory limit: 512 MB

Uolevi has won a contest, and the prize is a free flight trip that can consist of one or more flights through cities. Of course, Uolevi wants to choose a trip that has as many cities as possible.
Uolevi wants to fly from Syrjälä to Lehmälä so that he visits the maximum number of cities. You are given the list of possible flights, and you know that there are no directed cycles in the flight network.
Input
The first input line has two integers nnn and mmm: the number of cities and flights. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n. City 111 is Syrjälä, and city nnn is Lehmälä.
After this, there are mmm lines describing the flights. Each line has two integers aaa and bbb: there is a flight from city aaa to city bbb. Each flight is a one-way flight.
Output
First print the maximum number of cities on the route. After this, print the cities in the order they will be visited. You can print any valid solution.
If there are no solutions, print "IMPOSSIBLE".
Constraints

2≤n≤1052 \le n \le 10^52≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 5
1 2
2 5
1 3
3 4
4 5

Output:
4
1 3 4 5
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 3e5 + 1;
vector<int>adj[N];
int in[N] , dp[N] , nxt[N];
int main() {
    PRE();
    int m;
    int n;cin>>n>>m;
    for (int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;u-- , v--;
        adj[u].emplace_back(v);
        in[v]++;
    }
    vector<int>topo;
    queue<int>q;
    for (int i = 0;i < n;i++) {
        if (!in[i]) {
            q.push(i);
        }
    }
    while (q.size()) {
        int node = q.front();q.pop();
        topo.push_back(node);
        for (auto &val:adj[node]) {
            if (--in[val] == 0) {
                q.push(val);
            }
        }
    }
    if (topo.size() != n) {
        cout<<"IMPOSSIBLE";
        exit(0);
    }
    for (auto &v : dp) v = -1e9;
    memset(nxt , -1 , sizeof nxt);
    dp[n - 1] = 0;
    for (int i = topo.size() - 1;i >= 0;i--) {
        for (auto &v : adj[topo[i]]) {
            if (dp[v] + 1 > dp[topo[i]]){
                dp[topo[i]] = 1 + dp[v];
                nxt[topo[i]] = v;
            }
        }
    }
    if (dp[0] < 0) {
        cout<<"IMPOSSIBLE";
        exit(0);
    }
    vector<int>path;
    int u = 0;
    do {
        path.push_back(u + 1);
        u = nxt[u];
    }while (~u);
    assert(dp[0] + 1 == path.size());
    cout<<dp[0] + 1<<'\n';
    for (auto &v : path)
        cout<<v<<" ";
}