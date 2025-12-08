/* problem statement text */
/*
CSES - Removing Digits

Time limit: 1.00 s
Memory limit: 512 MB

You are given an integer nnn. On each step, you may subtract one of the digits from the number.
How many steps are required to make the number equal to 000?
Input
The only input line has an integer nnn.
Output
Print one integer: the minimum number of steps.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
27

Output:
5

Explanation: An optimal solution is 27→20→18→10→9→027 \rightarrow 20 \rightarrow 18 \rightarrow 10 \rightarrow 9 \rightarrow 027→20→18→10→9→0.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7 , N = 1e6 + 10;
ll dp[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n;cin>>n;
    memset(dp , '?' , sizeof dp);
    dp[0] = 0;
    for(int i = 1;i <= n;i++) {
        int temp = i;
        while(temp) {
            if(i - temp % 10 >= 0) dp[i] = min(dp[i] , 1 + dp[i - temp % 10]);
            temp /= 10;
        }
    }
    cout<<dp[n];
}