/* problem statement text */
/*
CSES - Subarray Squares

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn elements, your task is to divide into kkk subarrays. The cost of each subarray is the square of the sum of the values in the subarray. What is the minimum total cost if you act optimally?
Input
The first input line has two integers nnn and kkk: the array elements and the number of subarrays. The array elements are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print one integer: the minimum total cost.
Constraints

1≤k≤n≤30001 \le k \le n \le 30001≤k≤n≤3000
1≤xi≤1051 \le x_i \le 10^51≤xi​≤105

Example
Input:
8 3
2 3 1 2 2 3 4 1

Output:
110

Explanation: An optimal solution is [2,3,1][2,3,1][2,3,1], [2,2,3][2,2,3][2,2,3], [4,1][4,1][4,1], whose cost is (2+3+1)2+(2+2+3)2+(4+1)2=110(2+3+1)^2+(2+2+3)^2+(4+1)^2=110(2+3+1)2+(2+2+3)2+(4+1)2=110.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 3001;
ll dp[N][N];
int n , k;
ll a[N];
 
void dnc(int i , int L , int R , int opt_L , int opt_R) {
    if (L > R) return;
    int mid = L + (R - L) / 2;
    int best = opt_L;
    for (int j = opt_L; j < min(opt_R + 1 , mid); j++) {
        ll cost = (a[mid] - a[j]) * (a[mid] - a[j]);
        if (dp[j][i - 1] + cost < dp[mid][i]) {
            dp[mid][i] = dp[j][i - 1] + cost;
            best = j;
        }
    }
    dnc(i , L , mid - 1 , opt_L , best);
    dnc(i , mid + 1 , R , best , opt_R);
}
 
int main() {
    PRE();
    cin >> n >> k;
    for (int i = 1;i <= n;i++) cin >> a[i];
    for (int i = 1;i <= n;i++) a[i] += a[i - 1];
    memset(dp , '?' , sizeof dp);
    dp[0][0] = 0;
    for (int i = 1;i <= k;i++) {
        dnc(i , 1 , n , 0 , n - 1);
    }
    cout << dp[n][k] << '\n';
}