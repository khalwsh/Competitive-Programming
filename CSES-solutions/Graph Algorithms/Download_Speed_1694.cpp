/* problem statement text */
/*
CSES - Download Speed

Time limit: 1.00 s
Memory limit: 512 MB

Consider a network consisting of nnn computers and mmm connections. Each connection specifies how fast a computer can send data to another computer.
Kotivalo wants to download some data from a server. What is the maximum speed he can do this, using the connections in the network?
Input
The first input line has two integers nnn and mmm: the number of computers and connections. The computers are numbered 1,2,…,n1,2,\dots,n1,2,…,n. Computer 111 is the server and computer nnn is Kotivalo's computer.
After this, there are mmm lines describing the connections. Each line has three integers aaa, bbb and ccc: computer aaa can send data to computer bbb at speed ccc.
Output
Print one integer: the maximum speed Kotivalo can download data.
Constraints

1≤n≤5001 \le n \le 5001≤n≤500
1≤m≤10001 \le m \le 10001≤m≤1000
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3

Output:
6
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000;
ll capacity[N][N];
int n , m;
pair<ll, vector<int>> Get(int source, int sink) {
    vector<int> parent(n, -1);
    vector<ll> maxMinEdge(n, 0);
    maxMinEdge[source] = 2e9;
 
    priority_queue<pair<ll, int>> pq;
    pq.push({maxMinEdge[source], source});
 
    while (!pq.empty()) {
        ll currMaxMin = pq.top().first;
        int node = pq.top().second;
        pq.pop();
 
        if (currMaxMin < maxMinEdge[node]) continue;
 
        for (int next = 0; next < n; next++) {
            if (capacity[node][next] <= 0) continue;
            ll newMaxMin = min(maxMinEdge[node], capacity[node][next]);
 
            if (newMaxMin > maxMinEdge[next]) {
                maxMinEdge[next] = newMaxMin;
                parent[next] = node;
                pq.push({newMaxMin, next});
            }
        }
    }
 
    vector<int> path;
    if (maxMinEdge[sink] == 0) {
        return {0, path};
    }
 
    int current = sink;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    return {maxMinEdge[sink], path};
}
ll MaxFlow(int source , int sink) {
    ll flow = 0;
    while(true) {
        // get path
        auto [NewFlow , dist] = Get(source , sink);
        if(!NewFlow)break;
        flow += NewFlow;
        // ugment it
        for(int i = 1;i < dist.size();i++) {
            capacity[dist[i - 1]][dist[i]] -= NewFlow;
            capacity[dist[i]][dist[i - 1]] += NewFlow;
        }
    }
    return flow;
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i = 0;i < m;i++) {
        int u , v , c;cin>>u>>v>>c;
        u-- , v--;
        capacity[u][v] += c;
    }
    cout<<MaxFlow(0 , n - 1);
}