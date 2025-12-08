/* problem statement text */
/*
CSES - Building Roads

Time limit: 1.00 s
Memory limit: 512 MB

Byteland has nnn cities, and mmm roads between them. The goal is to construct new roads so that there is a route between any two cities.
Your task is to find out the minimum number of roads required, and also determine which roads should be built.
Input
The first input line has two integers nnn and mmm: the number of cities and roads. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After that, there are mmm lines describing the roads. Each line has two integers aaa and bbb: there is a road between those cities.
A road always connects two different cities, and there is at most one road between any two cities.
Output
First print an integer kkk: the number of required roads.
Then, print kkk lines that describe the new roads. You can print any valid solution.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
4 2
1 2
3 4

Output:
1
2 3
*/
#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(int i,int j,int n,int m)
{
    return i>=0&&i<n&&j>=0&&j<m;
}
int dx[]{1,-1,0,0};
int dy[]{0,0,1,-1};
/*--------------------------------------------------------------------------------------------------------------------*/
class dsu{
public:
    vector<int>parent,siz;
 
    dsu(int n)
    {
        parent.resize(n+1);
        siz.resize(n,1);
        for(int i=0;i<=n;i++)
            parent[i]=i;
    }
    int find_parent(int child)
    {
        if(parent[child]==child)return child;
        return parent[child]= find_parent(parent[child]);
    }
    void union_by_size(int a,int b)
    {
        int pa= find_parent(a);
        int pb= find_parent(b);
        if(pa==pb)return;
        if(siz[pa]>siz[pb])
        {
            siz[pa]+=siz[pb];
            parent[pb]=pa;
        }
        else
        {
            swap(pa,pb);
            siz[pa]+=siz[pb];
            parent[pb]=pa;
        }
    }
    int how_many_comp()
    {
        int counter=0;
        for(int i=1;i<parent.size();i++)
        {
            if(parent[i]==i)
                counter++;
        }
        return counter;
    }
};
signed main() {
    khaled
    int n;
    cin>>n;
    dsu d(n);
    int m;
    cin>>m;
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        d.union_by_size(a,b);
    }
    vector<pair<int,int>>v;
    vector<int>g;
    for(int i=1;i<d.parent.size();i++)
    {
        if(d.find_parent(i)==i)
            g.emplace_back(i);
    }
    for(int i=1;i<g.size();i++)
        v.emplace_back(g[0],g[i]);
    cout<<d.how_many_comp()-1<<line;
    for(auto &val:v)
        cout<<val.first<<" "<<val.second<<line;
}