/* problem statement text */
/*
CSES - Minimal Grid Path

Time limit: 1.00 s
Memory limit: 512 MB

You are given an n×nn \times nn×n grid whose each square contains a letter.
You should move from the upper-left square to the lower-right square. You can only move right or down.
What is the lexicographically minimal string you can construct?
Input
The first line has an integer nnn: the size of the grid.
After this, there are nnn lines that describe the grid. Each line has nnn letters between A and Z.
Output
Print the lexicographically minimal string.
Constraints

1≤n≤30001 \le n \le 30001≤n≤3000

Example
Input:
4
AACA
BABC
ABDA
AACA

Output:
AAABACA
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
const int N = 3001;
char g[N][N];
vector<pair<int , int>> available_positions;
bool vis[N][N];
int dx[]{0 , 1};
int dy[]{1 , 0};
int main() {
    PRE();
    int n; cin >> n;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            cin >> g[i][j];
        }
    }
    string res;
    available_positions.emplace_back(0 , 0);
    vis[0][0] = true;
    while (res.size() != 2 * n - 1) {
        res += g[available_positions[0].first][available_positions[0].second];
        int mn = 'Z';
        vector<pair<int , int>> n_available;
        for (auto &[i , j] : available_positions) {
            for (int k = 0;k < 2;k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < n && nj >= 0 && nj < n && !vis[ni][nj]) {
                    vis[ni][nj] = true;
                    if (g[ni][nj] < mn) mn = g[ni][nj] , n_available.clear() , n_available.emplace_back(ni , nj);
                    else if (g[ni][nj] == mn) {
                        n_available.emplace_back(ni , nj);
                    }
                }
            }
        }
        available_positions.swap(n_available);
    }
    cout << res << '\n';
}