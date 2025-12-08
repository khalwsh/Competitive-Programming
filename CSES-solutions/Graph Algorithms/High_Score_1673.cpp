/* problem statement text */
/*
CSES - High Score

Time limit: 1.00 s
Memory limit: 512 MB

You play a game consisting of nnn rooms and mmm tunnels. Your initial score is 000, and each tunnel increases your score by xxx where xxx may be both positive or negative. You may go through a tunnel several times.
Your task is to walk from room 111 to room nnn. What is the maximum score you can get?
Input
The first input line has two integers nnn and mmm: the number of rooms and tunnels. The rooms are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are mmm lines describing the tunnels. Each line has three integers aaa, bbb and xxx: the tunnel starts at room aaa, ends at room bbb, and it increases your score by xxx. All tunnels are one-way tunnels.
You can assume that it is possible to get from room 111 to room nnn.
Output
Print one integer: the maximum score you can get. However, if you can get an arbitrarily large score, print −1-1−1.
Constraints

1≤n≤25001 \le n \le 25001≤n≤2500
1≤m≤50001 \le m \le 50001≤m≤5000
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
−109≤x≤109-10^9 \le x \le 10^9−109≤x≤109

Example
Input:
4 5
1 2 3
2 4 -1
1 3 -2
3 4 7
1 4 4

Output:
5
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
const int N = 5001;
vector<int>adj[N];
int main() {
    PRE();
    int n , m;cin>>n>>m;
    vector<array<ll , 3>>edges(m);
    for (auto &[u ,  v , w] : edges) {
        cin>>u>>v>>w;
        w = -w;
        u-- , v--;
    }
    vector<ll>dist(n , inf);
    dist[0] = 0;
    for (int i = 0;i < n - 1;i++) {
        for (auto &[u , v , w] : edges) {
            if (dist[u] < inf) dist[v] = min(dist[u] + w , dist[v]);
        }
    }
    auto ref = dist;
    vector<int>cyclic(n , false);
    for (int i = 0;i < n;i++) {
        for (auto &[u , v , w] : edges) {
            if (dist[u] < inf && dist[v] > dist[u] + w) dist[v] = -inf , cyclic[v] = true;
        }
    }
    if (cyclic[n - 1]) {
        cout<<-1;
    }else
        cout<<-dist[n - 1];
}