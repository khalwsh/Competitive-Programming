/* problem statement text */
/*
CSES - Network Renovation

Time limit: 1.00 s
Memory limit: 512 MB

Syrjälä's network consists of nnn computers and n−1n-1n−1 connections between them. It is possible to send data between any two computers.
However, if any connection breaks down, it will no longer be possible to send data between some computers. Your task is to add the minimum number of new connections in such a way that you can still send data between any two computers even if any single connection breaks down.
Input
The first input line has an integer nnn: the number of computers. The computers are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are n−1n-1n−1 lines describing the connections. Each line has two integers aaa and bbb: there is a connection between computers aaa and bbb.
Output
First print an integer kkk: the minimum number of new connections. After this, print kkk lines describing the connections. You can print any valid solution.
Constraints

3≤n≤1053 \le n \le 10^53≤n≤105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5
1 2
1 3
3 4
3 5

Output:
2
2 4
4 5
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
vector<int> leafs;
void dfs(int u , int p) {
    if (adj[u].size() == 1) leafs.emplace_back(u);
    for (auto &v : adj[u]) {
        if (v == p) continue;
        dfs(v , u);
    }
}
int main() {
    PRE();
    int n;cin >> n;
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin >>  u >> v;
        u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0 , -1);
    vector<pair<int , int>> e;
    int i = 0 , j = leafs.size() / 2;
    while (i < leafs.size() / 2 && j < leafs.size()) {
        e.emplace_back(leafs[i] + 1 , leafs[j] + 1);
        i++ , j++;
    }
    if (leafs.size() & 1) {
        e.emplace_back(leafs.back() + 1 , leafs.front() + 1);
    }
    cout << e.size() << '\n';
    for (auto &val : e) cout << val.first << " " << val.second << '\n';
}