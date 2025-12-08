/* problem statement text */
/*
CSES - Coin Combinations II

Time limit: 1.00 s
Memory limit: 512 MB

Consider a money system consisting of nnn coins. Each coin has a positive integer value. Your task is to calculate the number of distinct ordered ways you can produce a money sum xxx using the available coins.
For example, if the coins are {2,3,5}\{2,3,5\}{2,3,5} and the desired sum is 999, there are 333 ways:

2+2+52+2+52+2+5
3+3+33+3+33+3+3
2+2+2+32+2+2+32+2+2+3

Input
The first input line has two integers nnn and xxx: the number of coins and the desired sum of money.
The second line has nnn distinct integers c1,c2,…,cnc_1,c_2,\dots,c_nc1​,c2​,…,cn​: the value of each coin.
Output
Print one integer: the number of ways modulo 109+710^9+7109+7.
Constraints

1≤n≤1001 \le n \le 1001≤n≤100
1≤x≤1061 \le x \le 10^61≤x≤106
1≤ci≤1061 \le c_i \le 10^61≤ci​≤106

Example
Input:
3 9
2 3 5

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7 , N = 1e6 + 10;
ll dp[N * 2];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n , x;cin>>n>>x;
    dp[0] = 1;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    for(int j = 0;j < n;j++) {
        for(int i = 0;i <= x;i++) {
            dp[i + v[j]] += dp[i];
            dp[i + v[j]] %= mod;
        }
    }
    cout<<dp[x]<<'\n';
}