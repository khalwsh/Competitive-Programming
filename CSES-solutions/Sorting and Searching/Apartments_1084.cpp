/* problem statement text */
/*
CSES - Apartments

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn applicants and mmm free apartments. Your task is to distribute the apartments so that as many applicants as possible will get an apartment.
Each applicant has a desired apartment size, and they will accept any apartment whose size is close enough to the desired size.
Input
The first input line has three integers nnn, mmm, and kkk: the number of applicants, the number of apartments, and the maximum allowed difference.
The next line contains nnn integers a1,a2,…,ana_1, a_2, \ldots, a_na1​,a2​,…,an​: the desired apartment size of each applicant. If the desired size of an applicant is xxx, they will accept any apartment whose size is between x−kx-kx−k and x+kx+kx+k.
The last line contains mmm integers b1,b2,…,bmb_1, b_2, \ldots, b_mb1​,b2​,…,bm​: the size of each apartment.
Output
Print one integer: the number of applicants who will get an apartment.
Constraints

1≤n,m≤2⋅1051 \le n, m \le 2 \cdot 10^51≤n,m≤2⋅105
0≤k≤1090 \le k \le 10^90≤k≤109
1≤ai,bi≤1091 \le a_i, b_i \le 10^91≤ai​,bi​≤109

Example
Input:
4 3 5
60 45 80 60
30 60 75

Output:
2
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
    int m,d;
    cin>>m>>d;
    vector<int>v(n);
    for(auto &val:v)
        cin>>val;
    vector<int>app(m);
    for(auto &val:app)cin>>val;
    sort(v.begin(),v.end());
    int res=0;
    sort(app.begin(),app.end());
    int pointer1=0;
    for(int i=0;i<n;i++)
    {
        while(pointer1<m&&app[pointer1]+d<v[i])pointer1++;
        if(pointer1<m&&app[pointer1]>v[i])
        {
            if(v[i]+d>=app[pointer1])res++,pointer1++;
        }
        else if(pointer1<m)
        {
            if(app[pointer1]+d>=v[i])res++,pointer1++;
        }
    }
    cout<<res<<line;
}