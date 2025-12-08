/* problem statement text */
/*
CSES - Counting Rooms

Time limit: 1.00 s
Memory limit: 512 MB

You are given a map of a building, and your task is to count the number of its rooms. The size of the map is n×mn \times mn×m squares, and each square is either floor or wall. You can walk left, right, up, and down through the floor squares.
Input
The first input line has two integers nnn and mmm: the height and width of the map.
Then there are nnn lines of mmm characters describing the map. Each character is either . (floor) or # (wall).
Output
Print one integer: the number of rooms.
Constraints

1≤n,m≤10001 \le n,m \le 10001≤n,m≤1000

Example
Input:
5 8
########
#..#...#
####.#.#
#..#...#
########

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(int i,int j,int n,int m)
{
    return i>=0&&j<m&&i<n&&j>=0;
}
void dfs(int row,int col,int n,int m,vector<vector<char>>&grid,vector<vector<bool>>&vis)
{
    vis[row][col]=true;
    int dx[]{1,-1,0,0};
    int dy[]{0,0,1,-1};
    for(int i=0;i<4;i++)
    {
        int cur_row=row+dx[i];
        int cur_col=col+dy[i];
        if(valid(cur_row,cur_col,n,m)&&!vis[cur_row][cur_col]&&grid[cur_row][cur_col]!='#')
            dfs(cur_row,cur_col,n,m,grid,vis);
    }
}
signed main() {
    khaled
    int n;
    int m;
    cin>>n>>m;
    vector<vector<char>>grid(n,vector<char>(m));
    for(auto &val:grid)for(auto &i:val)cin>>i;
    vector<vector<bool>>vis(n,vector<bool>(m));
    int counter=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(!vis[i][j]&&grid[i][j]!='#')
                dfs(i,j,n,m,grid,vis),counter++;
        }
    }
    cout<<counter<<line;
 
}