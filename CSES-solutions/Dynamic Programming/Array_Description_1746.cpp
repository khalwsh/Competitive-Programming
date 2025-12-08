/* problem statement text */
/*
CSES - Array Description

Time limit: 1.00 s
Memory limit: 512 MB

You know that an array has nnn integers between 111 and  mmm, and the absolute difference between two adjacent values is at most 111.
Given a description of the array where some values may be unknown, your task is to count the number of arrays that match the description.
Input
The first input line has two integers nnn and mmm: the array size and the upper bound for each value.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array. Value 000 denotes an unknown value.
Output
Print one integer: the number of arrays modulo 109+710^9+7109+7.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤1001 \le m \le 1001≤m≤100
0≤xi≤m0 \le x_i \le m0≤xi​≤m

Example
Input:
3 5
2 0 2

Output:
3

Explanation: The arrays [2,1,2][2,1,2][2,1,2], [2,2,2][2,2,2][2,2,2] and [2,3,2][2,3,2][2,3,2] match the description.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10 , mod = 1e9 + 7;
int n , m;
int v[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n>>m;
    vector<int>dp(m + 1);
    for(int i = 0;i < n;i++)cin>>v[i];
    if(v[0] == 0)for(int i = 1;i <= m;i++)dp[i] = 1;
    else dp[v[0]] = 1;
    for(int i = 1;i < n;i++) {
        vector<int>ndp(m + 1);
        if(!v[i]) {
            // wild card
            for(int j = 1;j <= m;j++) {
                ndp[j] += dp[j];
                if(ndp[j] >= mod)ndp[j] -= mod;
                if(j - 1 > 0)ndp[j] += dp[j - 1];
                if(ndp[j] >= mod)ndp[j] -= mod;
                if(j + 1 <= m)ndp[j] += dp[j + 1];
                if(ndp[j] >= mod)ndp[j] -= mod;
            }
        }else {
            int j = v[i];
            ndp[j] += dp[j];
            if(ndp[j] >= mod)ndp[j] -= mod;
            if(j - 1 > 0)ndp[j] += dp[j - 1];
            if(ndp[j] >= mod)ndp[j] -= mod;
            if(j + 1 <= m)ndp[j] += dp[j + 1];
            if(ndp[j] >= mod)ndp[j] -= mod;
        }
        swap(ndp , dp);
    }
    ll sum = 0;
    for(auto &val:dp)sum += val , sum %= mod;
    cout<<sum;
}