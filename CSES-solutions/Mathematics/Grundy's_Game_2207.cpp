/* problem statement text */
/*
CSES - Grundy's Game

Time limit: 1.00 s
Memory limit: 512 MB

There is a heap of nnn coins and two players who move alternately. On each move, a player chooses a heap and divides into two nonempty heaps that have a different number of coins. The player who makes the last move wins the game.
Your task is to find out who wins if both players play optimally.
Input
The first input line contains an integer ttt: the number of tests.
After this, there are ttt lines that describe the tests. Each line has an integer nnn: the number of coins in the initial heap.
Output
For each test case, print "first" if the first player wins the game and "second" if the second player wins the game.
Constraints

1≤t≤1051 \le t \le 10^51≤t≤105
1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
3
6
7
8

Output:
first
second
first
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
 
int dp[2001];
 
int grundy(int x) {
    if (x == 0) return 0;
    int &ret = dp[x];
    if (~ret) return ret;
    vector<int> v;
    for (int a = 1; a <= x / 2; ++a) {
        int b = x - a;
        if (a == b) continue;
        int ga = grundy(a);
        int gb = grundy(b);
        v.emplace_back(ga ^ gb);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int mex = 0;
    while (mex < v.size() && v[mex] == mex) ++mex;
    return ret = mex;
}
 
int main() {
    PRE();
    memset(dp, -1, sizeof dp);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n >= 2000 || grundy(n)) cout << "first\n";
        else cout << "second\n";
    }
}