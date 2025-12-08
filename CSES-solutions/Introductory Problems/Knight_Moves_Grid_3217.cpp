/* problem statement text */
/*
CSES - Knight Moves Grid

Time limit: 1.00 s
Memory limit: 512 MB

There is a knight on an n×nn \times nn×n chessboard. For each square, print the minimum number of moves the knight needs to do to reach the top-left corner.
Input
The only line has an integer nnn.
Output
Print the number of moves for each square.
Constraints

4≤n≤10004 \le n \le 10004≤n≤1000

Example
Input:
8

Output:
0 3 2 3 2 3 4 5 
3 4 1 2 3 4 3 4 
2 1 4 3 2 3 4 5 
3 2 3 2 3 4 3 4 
2 3 2 3 4 3 4 5 
3 4 3 4 3 4 5 4 
4 3 4 3 4 5 4 5 
5 4 5 4 5 4 5 6
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
 
int dx[]{1 , -1 , 2 , -2 , 1 , -1 , 2 , -2};
int dy[]{2 , 2 , 1 , 1 , -2 , -2 , -1 , -1};
 
int dist[1001][1001];
int main() {
    PRE();
    int n;cin >> n;
    memset(dist , '?' , sizeof dist);
    queue<pair<int , int>> q;
    q.push({0 ,0});
    dist[0][0] = 0;
    while (!q.empty()) {
        auto [i , j] = q.front();
        q.pop();
        for (int k = 0;k < 8;k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if (ni >= 0 && nj >= 0 && ni < n && nj < n && dist[ni][nj] > 1 + dist[i][j]) {
                dist[ni][nj] = 1 + dist[i][j];
                q.push({ni , nj});
            }
        }
    }
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++)
            cout << dist[i][j] << " ";
        cout << '\n';
    }
}