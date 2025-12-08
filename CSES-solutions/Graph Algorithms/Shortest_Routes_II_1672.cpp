/* problem statement text */
/*
CSES - Shortest Routes II

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm roads between them. Your task is to process qqq queries where you have to determine the length of the shortest route between two given cities.
Input
The first input line has three integers nnn, mmm and qqq: the number of cities, roads, and queries.
Then, there are mmm lines describing the roads. Each line has three integers aaa, bbb and ccc: there is a road between cities aaa and bbb whose length is ccc. All roads are two-way roads.
Finally, there are qqq lines describing the queries. Each line has two integers aaa and bbb: determine the length of the shortest route between cities aaa and bbb.
Output
Print the length of the shortest route for each query. If there is no route, print −1-1−1 instead.
Constraints

1≤n≤5001 \le n \le 5001≤n≤500
1≤m≤n21 \le m \le n^21≤m≤n2
1≤q≤1051 \le q \le 10^51≤q≤105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
4 3 5
1 2 5
1 3 9
2 3 3
1 2
2 1
1 3
1 4
3 2

Output:
5
5
8
-1
3
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
const int N = 502;
ll cost[N][N];
const ll INF = 1e18;
ll dp[N][N];
int main() {
    PRE();
    int n , m , q;cin>>n>>m>>q;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            cost[i][j] = INF;
 
        }
        cost[i][i] = 0;
    }
    for (int i = 0;i < m;i++) {
        ll u , v , w;cin>>u>>v>>w;
        w = min(w , cost[u - 1][v - 1]);
        cost[u - 1][v - 1] = w;
        swap(u , v);
        cost[u - 1][v - 1] = w;
    }
    for (int j = 0;j < n;j++) {
        for (int k = 0;k < n;k++) {
            dp[j][k] = INF;
        }
    }
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            dp[i][j] = cost[i][j];
        }
    }
    for (int k = 0;k < n;k++) {
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < n;j++) {
                dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k][j]);
            }
        }
    }
    while (q--) {
        int u , v;cin>>u>>v;
        u-- , v--;
        cout<<(dp[u][v] == INF ? -1 : dp[u][v])<<'\n';
    }
}