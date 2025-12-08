/* problem statement text */
/*
CSES - Maximum Manhattan Distances

Time limit: 1.00 s
Memory limit: 512 MB

A set is initially empty and nnn points are added to it. Calculate the maximum Manhattan distance of two points after each addition.
Input
The first line has an integer nnn: the number of points.
The following nnn lines describe the points. Each line has two integers xxx and yyy. You can assume that each point is distinct.
Output
After each addition, print the maximum distance.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
−109≤x,y≤109-10^9 \le x, y \le 10^9−109≤x,y≤109

Example
Input:
5
1 1
3 2
2 4
2 1
4 5

Output:
0
3
4
4
7
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
    freopen("out.txt", "w",stdout);
    freopen("error.txt", "w",stderr);
#endif
}
 
int main() {
    PRE();
    ll best[4];
    for (int i = 0; i < 4; i++) best[i] = -1e18;
    int n;
    cin >> n;
    vector<pair<ll, ll> > vp(n);
    for (auto &[x , y]: vp) cin >> x >> y;
    for (auto &[x , y]: vp) {
        best[0] = max(best[0], x + y);
        best[1] = max(best[1], x - y);
        best[2] = max(best[2], -x - y);
        best[3] = max(best[3], -x + y);
        cout << max(best[0] + best[2], best[1] + best[3]) << '\n';
    }
}