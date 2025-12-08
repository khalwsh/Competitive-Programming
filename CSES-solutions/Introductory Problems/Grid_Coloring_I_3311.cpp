/* problem statement text */
/*
CSES - Grid Coloring I

Time limit: 1.00 s
Memory limit: 512 MB

You are given an n×mn\times mn×m grid where each cell contains one character A, B, C or D.
For each cell, you must change the character to A, B, C or D. The new character must be different from the old one.
Your task is to change the characters in every cell such that no two adjacent cells have the same character.
Input
The first line has two integers nnn and mmm: the number of rows and columns.
The next nnn lines each have mmm characters: the description of the grid.
Output
Print nnn lines each with mmm characters: the description of the final grid.
You may print any valid solution.
If no solution exists, just print IMPOSSIBLE.
Constraints

1≤n,m≤5001 \le n, m \le 5001≤n,m≤500

Example
Input:
3 4
AAAA
BBBB
CCDD

Output:
CDCD
DCDC
ABAB
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
const int N = 501;
char v[N][N];
int n , m;
 
bool solve(int i , int j) {
    if (i == n) {
        return true;
    }
    for (auto &val : "ABCD") {
        if (val == v[i][j] || (i >= 1 && val == v[i - 1][j]) ||(j >= 1 && val == v[i][j - 1])) {
            continue;
        }
        char old = v[i][j];
        v[i][j] = val;
        if (solve(i + (j + 1 == m) , (j + 1) % m)) {
            return true;
        }
        v[i][j] = old;
    }
    return false;
}
int main() {
    PRE();
    cin >> n >> m;
    for (int i = 0;i < n;i++)
        for (int j = 0;j < m;j++)
            cin >> v[i][j];
    if (solve(0 , 0)) {
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++)
                cout << v[i][j];
            cout << '\n';
        }
    }else {
        cout << "IMPOSSIBLE";
    }
}