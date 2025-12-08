/* problem statement text */
/*
CSES - Sliding Window Median

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the median of each window of kkk elements, from left to right.
The median is the middle element when the elements are sorted. If the number of elements is even, there are two possible medians and we assume that the median is the smaller of them.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
Then there are nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print n−k+1n-k+1n−k+1 values: the medians.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
8 3
2 4 3 5 8 1 2 1

Output:
3 4 5 5 2 1
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define int long long
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846;
const long double eps=1e-9;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
//const int N=2e6+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e17;
//__builtin_clzll(x): the number of zeros at the beginning of the number
//__builtin_ctzll(x): the number of zeros at the end of the number
//__builtin_popcountll(x): the number of ones in the number
//__builtin_parityll(x): the parity (even or odd) of the number of ones
/*=======================================================================================================*/
/*==============================================  KHALWSH  ==============================================*/
/*=======================================================================================================*/
struct BIT{
    int N;
    vector<int>tree;
    void init(int x){
        N=1<<x;
        tree.resize(this->N);
    }
    void add(int pos,int value){
        for(++pos;pos<=N;pos+=pos&-pos)tree[pos-1]+=value;
    }
    int get(int pos){
        int sum=0;
        for(++pos;pos>0;pos-=pos&-pos)sum+=tree[pos-1];
        return sum;
    }
    int find(int t){
        int st=0;
        for(int sz=N>>1;sz;sz>>=1){
            if(tree[st+sz-1]<t){
                t-=tree[(st+=sz)-1];
            }
        }
        return st;
    }
};
struct Multiset{
    BIT bit;
    Multiset(int x){
        bit.init(x);
        bit.add(0,-1);
    }
    int size(){
        return bit.get(bit.N-1)+1;
    }
    void insert(int value){
        bit.add(value,1);
    }
    void erase(int value){
        bit.add(value,-1);
    }
    int count(int x){
        return bit.get(x)-bit.get(x-1);
    }
    int at(int x){
        return bit.find(x);
    }
};
signed main() {
    khaled
    int n,k;
    cin>>n>>k;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    set<int>os(v.begin(),v.end());
    map<int,int>compress,rev;
    int num=0;
    for(auto &val:os)compress[num]=val,rev[val]=num,num++;
    swap(compress,rev);
    Multiset ms(18);
    for(int i=0;i<k;i++)ms.insert(compress[v[i]]);
    vector<int>res;
    for(int i=0;i<n;i++){
        if(res.size()==n-k+1)break;
        int sz=ms.size();
        //for(int j=0;j<sz;j++)cout<<ms.at(j)<<" ";
        //cout<<line;
        if(sz&1){
            res.emplace_back(ms.at((k+1)/2-1));
        }else{
            res.emplace_back(min(ms.at((k)/2),ms.at((k)/2-1)));//4 element 0,1,2,3
        }
        ms.erase(compress[v[i]]);
        ms.insert(compress[v[i+k]]);
    }
    for(auto &val:res)cout<<rev[val]<<" ";
}