/* problem statement text */
/*
CSES - Ferris Wheel

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn children who want to go to a Ferris wheel, and your task is to find a gondola for each child.
Each gondola may have one or two children in it, and in addition, the total weight in a gondola may not exceed xxx. You know the weight of every child.
What is the minimum number of gondolas needed for the children?
Input
The first input line contains two integers nnn and xxx: the number of children and the maximum allowed weight.
The next line contains nnn integers p1,p2,…,pnp_1,p_2,\ldots,p_np1​,p2​,…,pn​: the weight of each child.
Output
Print one integer: the minimum number of gondolas.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤x≤1091 \le x \le 10^91≤x≤109
1≤pi≤x1 \le p_i \le x1≤pi​≤x

Example
Input:
4 10
7 2 3 9

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(int i,int j,int n,int m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const int&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const int&mod){return (((x%mod)+(y%mod))+mod)%mod;}
int dx[]{1,-1,0,0};
int dy[]{0,0,1,-1};
#define int long long
/*--------------------------------------------------------------------------------------------------------------------*/
class dsu{
private:
public:
    vector<int>parent;
    vector<int>siz;
    dsu()=default;
    dsu(int n)
    {
        //intializing the parent and rank
        parent.resize(n+1);
        siz.resize(n+1,1);
        for(int i=0;i<=n;i++)
            parent[i]=i;
    }
    int find_parent(int child)
    {
        //this function find the ultimate parent of certain child and make a update the parent
        if(parent[child]==child)
            return child;
        return parent[child]=find_parent(parent[child]);
    }
    void union_by_size(int a,int b)
    {
        int pa= find_parent(a);
        int pb= find_parent(b);
        if(pa==pb)return;
        if(siz[pa]>=siz[pb])
            siz[pa]+=siz[pb],parent[pb]=pa;
        else if(siz[pb]>siz[pa])
            siz[pb]+=siz[pa],parent[pa]=pb;
    }
    bool same_component(int a,int b)
    {
        return find_parent(a)==find_parent(b);
    }
};
long long nc2(long long res)
{
    return res*(res-1)/2;
}
bool comp(pair<int,pair<int,int>>&a,pair<int,pair<int,int>>&b)
{
    return a.second.second<b.second.second;
}
signed main() {
    khaled
    int n;
    cin>>n;
    int x;
    cin>>x;
    vector<int>v(n);
    for(auto &val:v)
        cin>>val;
    sort(v.begin(),v.end());
    int left=0,right=n-1;
    int res=0;
    while(left<=right)
    {
        if(left==right)res++,left++;
        else if(v[right]+v[left]<=x)
            res++,left++,right--;
        else
            res++,right--;
    }
    cout<<res<<line;
}