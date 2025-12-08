/* problem statement text */
/*
CSES - Cycle Finding

Time limit: 1.00 s
Memory limit: 512 MB

You are given a directed graph, and your task is to find out if it contains a negative cycle, and also give an example of such a cycle.
Input
The first input line has two integers nnn and mmm: the number of nodes and edges. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
After this, the input has mmm lines describing the edges. Each line has three integers aaa, bbb, and ccc: there is an edge from node aaa to node bbb whose length is ccc.
Output
If the graph contains a negative cycle, print first "YES", and then the nodes in the cycle in their correct order. If there are several negative cycles, you can print any of them. If there are no negative cycles, print "NO".
Constraints

1≤n≤25001 \le n \le 25001≤n≤2500
1≤m≤50001 \le m \le 50001≤m≤5000
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
−109≤c≤109-10^9 \le c \le 10^9−109≤c≤109

Example
Input:
4 5
1 2 1
2 4 1
3 1 1
4 1 -3
4 3 -2

Output:
YES
1 2 4 1
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
const ll inf = 1e18;
int main() {
    PRE();
    int n , m;cin>>n>>m;
    vector<array<ll , 3>>edges(m);
    for (auto &[u , v , w] : edges) {
        cin >> u >> v >> w;
        u-- , v--;
    }
    vector<ll>dist(n , inf) , prev(n , -1);
    int cyclic_node = -1;
    for (int i = 0;i < n;i++) {
        for (auto &[u , v , w] : edges) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (i == n - 1)
                    cyclic_node = (int)v;
                prev[v] = u;
            }
        }
    }
    if (cyclic_node == -1) {
        cout<<"NO";
    }else {
        for (int i = 0;i < n;i++) {
            cyclic_node = prev[cyclic_node];
        }
        cout<<"YES\n";
        vector<int>cycle;
        for (int i = cyclic_node;i != cyclic_node || cycle.size() == 0; i = prev[i]) {
            cycle.emplace_back(i);
        }
        cycle.emplace_back(cyclic_node);
        reverse(cycle.begin() , cycle.end());
        for (auto &v : cycle)
            cout<<v + 1<<" ";
    }
}