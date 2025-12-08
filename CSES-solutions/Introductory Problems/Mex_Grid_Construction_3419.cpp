/* problem statement text */
/*
CSES - Mex Grid Construction

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to construct an n×nn \times nn×n grid where each square has the smallest nonnegative integer that does not appear to the left on the same row or above on the same column.
Input
The only line has an integer nnn.
Output
Print the grid according to the example.
Constraints

1≤n≤1001 \le n \le 1001≤n≤100

Example
Input:
5

Output:
0 1 2 3 4
1 0 3 2 5
2 3 0 1 6
3 2 1 0 7
4 5 6 7 0
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
int v[101][101];
 
int get(int i , int j) {
    vector<int>all;
    for (int k = 0;k < j;k++) all.emplace_back(v[i][k]);
    for (int k = 0;k < i;k++) all.emplace_back(v[k][j]);
    sort(all.begin() , all.end());
    all.erase(unique(all.begin() , all.end()) , all.end());
    int mex = 0;
    for (auto &val : all) {
        if (val == mex) mex++;
    }
    return v[i][j] = mex;
}
int main() {
    PRE();
    int n;cin >> n;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            cout << get(i , j) << " ";
        }
        cout << '\n';
    }
}