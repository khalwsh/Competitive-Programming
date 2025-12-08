/* problem statement text */
/*
CSES - Labyrinth

Time limit: 1.00 s
Memory limit: 512 MB

You are given a map of a labyrinth, and your task is to find a path from start to end. You can walk left, right, up and down.
Input
The first input line has two integers nnn and mmm: the height and width of the map.
Then there are nnn lines of mmm characters describing the labyrinth. Each character is . (floor), # (wall), A (start), or B (end). There is exactly one A and one B in the input.
Output
First print "YES", if there is a path, and "NO" otherwise.
If there is a path, print the length of the shortest such path and its description as a string consisting of characters L (left), R (right), U (up), and D (down). You can print any valid solution.
Constraints

1≤n,m≤10001 \le n,m \le 10001≤n,m≤1000

Example
Input:
5 8
########
#.A#...#
#.##.#B#
#......#
########

Output:
YES
9
LDDRRRRRU
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
    int start1,start2,target1,target2;
    //cin>>start1>>start1>>target1>>start2;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(grid[i][j]=='A')
                start1=i,start2=j;
            else if(grid[i][j]=='B')
                target1=i,target2=j;
        }
    }
    bool work=false;
    queue<pair<int,int>>q;
    vector<vector<pair<int,int>>>parent(n,vector<pair<int,int>>(m));
    q.push(make_pair(start1,start2));
    parent[start1][start2]= make_pair(start1,start2);
    vis[start1][start2]=true;
    while(!q.empty())
    {
        int row=q.front().first;
        int col=q.front().second;
        q.pop();
        int dx[]{1,-1,0,0};
        int dy[]{0,0,1,-1};
        for(int i=0;i<4;i++)
        {
            int cur_row=row+dx[i];
            int cur_col=col+dy[i];
            if(valid(cur_row,cur_col,n,m)&&!vis[cur_row][cur_col]&&grid[cur_row][cur_col]!='#')
            {
                vis[cur_row][cur_col]=true;
                q.push({cur_row,cur_col});
                if(i==0)
                    grid[cur_row][cur_col]='D';
                else if(i==1)
                    grid[cur_row][cur_col]='U';
                else if(i==2)
                    grid[cur_row][cur_col]='R';
                else
                    grid[cur_row][cur_col]='L';
                parent[cur_row][cur_col]= make_pair(row,col);
            }
        }
    }
    if(!vis[target1][target2])
    {
        cout<<"NO";
    }
    else
    {
        cout<<"YES";
        vector<char>path;
        int r=target1,c=target2;
        while(parent[r][c]!= make_pair(r,c))
        {
            pair<int,int>p=parent[r][c];
            path.emplace_back(grid[r][c]);
            r=p.first;
            c=p.second;
        }
        reverse(path.begin(),path.end());
        cout<<line;
        cout<<path.size()<<line;
        for(auto &val:path)cout<<val;
    }
}