/* problem statement text */
/*
CSES - Money Sums

Time limit: 1.00 s
Memory limit: 512 MB

You have nnn coins with certain values. Your task is to find all money sums you can create using these coins.
Input
The first input line has an integer nnn: the number of coins.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the values of the coins.
Output
First print an integer kkk: the number of distinct money sums. After this, print all possible sums in increasing order.
Constraints

1≤n≤1001 \le n \le 1001≤n≤100
1≤xi≤10001 \le x_i \le 10001≤xi​≤1000

Example
Input:
4
4 2 5 2

Output:
9
2 4 5 6 7 8 9 11 13
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
bitset<N>dp;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    dp[0] = true;
    int n;cin>>n;
    for(int i = 0;i < n;i++) {
        int x;cin>>x;
        dp |= dp<<x;
    }
    cout<<dp.count() - 1<<"\n";
    for(int i = 1;i <= N;i++) {
        if(dp[i])cout<<i<<" ";
    }
}