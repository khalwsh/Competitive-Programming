/* problem statement text */
/*
CSES - Chess Tournament

Time limit: 1.00 s
Memory limit: 512 MB

There will be a chess tournament of nnn players. Each player has announced the number of games they want to play.
Each pair of players can play at most one game. Your task is to determine which games will be played so that everybody will be happy.
Input
The first input line has an integer nnn: the number of players. The players are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: for each player, the number of games they want to play.
Output
First print an integer kkk: the number of games. Then, print kkk lines describing the games. You can print any valid solution.
If there are no solutions, print "IMPOSSIBLE".
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
∑i=1nxi≤2⋅105\sum_{i=1}^{n} x_i \le 2 \cdot 10^5∑i=1n​xi​≤2⋅105

Example
Input:
5
1 3 2 0 2

Output:
4
1 2
2 3
2 5
3 5
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
 
int main() {
    PRE();
    int n; cin >> n;
    priority_queue<pair<int , int>> pq;
    ll sum = 0;
    for (int i = 0;i < n;i++) {
        int x;cin >> x;
        if (x)
            pq.push({x , i + 1});
        sum += x;
    }
    int mx = pq.top().first;
    if ((sum & 1) || 2 * mx > sum) {
        cout << "IMPOSSIBLE";
        exit(0);
    }
    vector<pair<int , int>> res;
    while (pq.size()) {
        assert(pq.size() > 1);
        auto [x , i] = pq.top();
        pq.pop();
        auto [y , j] = pq.top();
        pq.pop();
        assert(x && y);
        res.emplace_back(i , j);
        if (x - 1)
            pq.push({x - 1 , i});
        if (y - 1)
            pq.push({y - 1 , j});
    }
    cout << res.size() << "\n";
    for (auto &val : res) cout << val.first << " " << val.second << '\n';
}