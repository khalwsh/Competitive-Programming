/* problem statement text */
/*
CSES - Concert Tickets

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn concert tickets available, each with a certain price. Then, mmm customers arrive, one after another.
Each customer announces the maximum price they are willing to pay for a ticket, and after this, they will get a ticket with the nearest possible price such that it does not exceed the maximum price.
Input
The first input line contains integers nnn and mmm: the number of tickets and the number of customers.
The next line contains nnn integers h1,h2,…,hnh_1,h_2,\ldots,h_nh1​,h2​,…,hn​: the price of each ticket.
The last line contains mmm integers t1,t2,…,tmt_1,t_2,\ldots,t_mt1​,t2​,…,tm​: the maximum price for each customer in the order they arrive.
Output
Print, for each customer, the price that they will pay for their ticket. After this, the ticket cannot be purchased again.
If a customer cannot get any ticket, print −1-1−1.
Constraints

1≤n,m≤2⋅1051 \le n, m \le 2 \cdot 10^51≤n,m≤2⋅105
1≤hi,ti≤1091 \le h_i, t_i \le 10^91≤hi​,ti​≤109

Example
Input:
5 3
5 3 7 8 5
4 8 3

Output:
3
8
-1
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
    int m;
    cin>>m;
    multiset<int>s;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        s.insert(x);
    }
    for(int i=0;i<m;i++)
    {
        int x;
        cin>>x;
        auto it=s.lower_bound(x);
        if(it==s.begin())
        {
            if(*it==x)
            {
                cout<<*it<<line;
                s.erase(it);
            }
            else
                cout<<-1<<line;
        }
        else
        {
            if(it==s.end())it--;
            if(*it<=x)
            {
                cout<<*it<<line;
                s.erase(it);
            }
            else
            {
                if(it==s.begin())cout<<-1<<line;
                else
                {
                    it--;
                    cout<<*it<<line;
                    s.erase(it);
                }
            }
        }
    }
}