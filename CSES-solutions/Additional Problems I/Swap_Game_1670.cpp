/* problem statement text */
/*
CSES - Swap Game

Time limit: 1.00 s
Memory limit: 512 MB

You are given a 3×33 \times 33×3 grid containing the numbers 1,2,…,91,2,\dots,91,2,…,9. Your task is to perform a sequence of moves so that the grid will look like this:
123456789
\begin{matrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9 \\
\end{matrix}
147​258​369​
On each move, you can swap the numbers in any two adjacent squares (horizontally or vertically). What is the minimum number of moves required?
Input
The input has three lines, and each of them has three integers.
Output
Print one integer: the minimum number of moves.
Example
Input:
2 1 3
7 5 9
8 4 6

Output:
4
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
 
vector<vector<int>> adj = {
    {1,3}, {0,2,4}, {1,5},
    {0,4,6}, {1,3,5,7}, {2,4,8},
    {3,7}, {4,6,8}, {5,7}
};
 
string encode(const vector<int>& grid) {
    string s;
    for (int x : grid) s += char(x + '0');
    return s;
}
 
int main() {
 
    PRE();
    vector<int> start(9);
    for (int &x : start) cin >> x;
 
    string target = "123456789";
    string s = encode(start);
 
    queue<pair<string,int>> q;
    unordered_set<string> seen;
 
    q.push({s,0});
    seen.insert(s);
 
    while (!q.empty()) {
        auto [state, moves] = q.front(); q.pop();
        if (state == target) {
            cout << moves << "\n";
            return 0;
        }
 
        for (int i = 0; i < 9; i++) {
            for (int j : adj[i]) {
                if (i < j) {
                    string next = state;
                    swap(next[i], next[j]);
                    if (!seen.count(next)) {
                        seen.insert(next);
                        q.push({next, moves + 1});
                    }
                }
            }
        }
    }
}