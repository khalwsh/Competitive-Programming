/* problem statement text */
/*
CSES - Increasing Subsequence

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array containing nnn integers. Your task is to determine the longest increasing subsequence in the array, i.e., the longest subsequence where every element is larger than the previous one.
A subsequence is a sequence that can be derived from the array by deleting some elements without changing the order of the remaining elements.
Input
The first line contains an integer nnn: the size of the array.
After this there are nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print the length of the longest increasing subsequence.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
8
7 3 5 3 6 2 9 8

Output:
4
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int v[N] , comp[N] , n , dp[N];
template<class T>
struct Fenwick{
    int n;
    vector<T>tree;
    int N = 1;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
    }
    void add(int pos,T value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]=max(tree[i - 1] , value);
    }
    T get(int pos) {
        if(pos < 0)return 0;
        T sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum = max(sum , tree[i - 1]);
        return sum;
    }
    T query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
};
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n;
    for(int i = 0;i < n;i++)cin>>v[i] , comp[i] = v[i];
    sort(comp , comp + n);
    for(int i = 0;i < n;i++)v[i] = lower_bound(comp , comp + n , v[i]) - comp;
    Fenwick<int>fen;fen.init(n + 1);
    for(int i = 0;i < n;i++) {
        dp[i] = 1 + fen.get(v[i] - 1);
        fen.add(v[i] , -fen.query(v[i] , v[i]) + dp[i]);
        // cout<<dp[i]<<" ";
    }
    cout<<*max_element(dp , dp + n);
}