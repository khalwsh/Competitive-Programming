/* problem statement text */
/*
CSES - Monsters

Time limit: 1.00 s
Memory limit: 512 MB

You and some monsters are in a labyrinth. When taking a step to some direction in the labyrinth, each monster may simultaneously take one as well. Your goal is to reach one of the boundary squares without ever sharing a square with a monster.
Your task is to find out if your goal is possible, and if it is, print a path that you can follow. Your plan has to work in any situation; even if the monsters know your path beforehand.
Input
The first input line has two integers nnn and mmm: the height and width of the map.
After this there are nnn lines of mmm characters describing the map. Each character is . (floor), # (wall), A (start), or M (monster). There is exactly one A in the input.
Output
First print "YES" if your goal is possible, and "NO" otherwise.
If your goal is possible, also print an example of a valid path (the length of the path and its description using characters D, U, L, and R). You can print any path, as long as its length is at most n⋅mn \cdot mn⋅m steps.
Constraints

1≤n,m≤10001 \le n,m \le 10001≤n,m≤1000

Example
Input:
5 8
########
#M..A..#
#.#.M#.#
#M#..#..
#.######

Output:
YES
5
RRDDR
*/
#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int dx[]{1,-1,0,0};
int dy[]{0,0,1,-1};
bool valid(int i,int j,int n,int m)
{
    return i>=0&&j<m&&i<n&&j>=0;
}
string solve(int start1,int start2,vector<vector<char>>&grid,int n,int m,int target1,int target2)
{
    vector<vector<bool>>vis(n,vector<bool>(m));
    //cin>>start1>>start1>>target1>>start2;
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
        string s;
        for(auto &val:path)s+=val;
        return s;
    }
}
vector<vector<int>>bfs(vector<vector<char>>&v,int n,int m,char ch)
{
    vector<vector<int>>dist(n,vector<int>(m,INT_MAX));
    queue<pair<int,int>>q;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(v[i][j]==ch)
            {
                dist[i][j]=0;
                q.push({i,j});
            }
        }
    }
    if(q.empty())
        return dist;
    while(!q.empty())
    {
        int row=q.front().first;
        int col=q.front().second;
        q.pop();
        for(int i=0;i<4;i++)
        {
            int cur_row=row+dx[i];
            int cur_col=col+dy[i];
            if(valid(cur_row,cur_col,n,m)&&v[cur_row][cur_col]!='#'&&dist[cur_row][cur_col]==INT_MAX)
            {
                dist[cur_row][cur_col]=dist[row][col]+1;
                q.push({cur_row,cur_col});
            }
        }
    }
    return dist;
}
signed main() {
    khaled
    int n;
    int m;
    cin>>n>>m;
    vector<vector<char>>v(n,vector<char>(m));
    for(auto &val:v)for(auto &i:val)cin>>i;
    vector<vector<int>>dist1=bfs(v,n,m,'A');
    vector<vector<int>>dist2=bfs(v,n,m,'M');
    int start1=-1,start2=-1;
    int target1=-1,target2=-1;
    for(int i=0;i<n;i++)
    {
        if(dist1[i][0]<dist2[i][0])
        {
           target1=i,target2=0;
           break;
        }
        if(dist1[i][m-1]<dist2[i][m-1])
        {
            target1=i;
            target2=m-1;
            break;
        }
    }
    for(int i=0;i<m;i++)
    {
        if(dist1[0][i]<dist2[0][i])
        {
            target2=i,target1=0;
            break;
        }
        if(dist1[n-1][i]<dist2[n-1][i])
        {
            target2=i,target1=n-1;
            break;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(v[i][j]=='A')
                start1=i,start2=j;
        }
    }
    if(target1==-1||start1==-1)
        cout<<"NO";
    else
    {
        cout<<"YES";
        cout<<line;
        string path=solve(start1,start2,v,n,m,target1,target2);
        cout<<path.size()<<line;
        cout<<path<<line;
    }
}