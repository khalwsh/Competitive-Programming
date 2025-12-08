/* problem statement text */
/*
CSES - Knight's Tour

Time limit: 1.00 s
Memory limit: 512 MB

Given a starting position of a knight on an 8×88 \times 88×8 chessboard, your task is to find a sequence of moves such that it visits every square exactly once.
On each move, the knight may either move two steps horizontally and one step vertically, or one step horizontally and two steps vertically.
Input
The only line has two integers xxx and yyy: the knight's starting position.
Output
Print a grid that shows how the knight moves (according to the example). You can print any valid solution.
Constraints

1≤x,y≤81 \le x,y \le 81≤x,y≤8

Example
Input:
2 1

Output:
8 1 10 13 6 3 20 17 
11 14 7 2 19 16 23 4 
26 9 12 15 24 5 18 21 
49 58 25 28 51 22 33 30 
40 27 50 59 32 29 52 35 
57 48 41 44 37 34 31 62 
42 39 46 55 60 63 36 53 
47 56 43 38 45 54 61 64
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
const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
ll board[8][8];
bool issafe(int x, int y){
    return (((0 <= x) && (x < 8)) && ((0 <= y) && (y < 8)));
}
int deg(ll x, ll y){
    int s = 0;
    for (ll i = 0; i < 8; i++){
        ll nx = x + dx[i];
        ll ny = y + dy[i];
        if ((((0 <= nx) && (nx < 8)) && ((0 <= ny) && (ny < 8))) && (board[nx][ny] != -1))
            s++;
    }
    return s;
}
bool dfs(int x, int y, int move){
    board[x][y] = move;
    if (move == 64){
        return true;
    }
    vector<vector<int>> vec;
    for (int i = 0; i < 8; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if ((((0 <= nx) && (nx < 8)) && ((0 <= ny) && (ny < 8))) && (board[nx][ny] == 0))
        {
            int d = deg(nx, ny);
            vec.push_back({d, nx, ny});
        }
    }
    sort(vec.begin(), vec.end());
    for (auto &i : vec){
        if (dfs(i[1], i[2], move + 1))
            return true;
    }
    board[x][y] = 0;
    return false;
}
int main() {
    PRE();
    ll x, y;
    cin >> y >> x;
    x--;
    y--;
    memset(board, 0, sizeof(board));
    bool res = dfs(x, y, 1);
    for (auto &i : board)
    {
        for (auto &j : i)
        {
            cout << j << " ";
        }
        cout << "\n";
    }
 
}