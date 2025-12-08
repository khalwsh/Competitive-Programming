/* problem statement text */
/*
CSES - Projects

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn projects you can attend. For each project, you know its starting and ending days and the amount of money you would get as reward. You can only attend one project during a day.
What is the maximum amount of money you can earn?
Input
The first input line contains an integer nnn: the number of projects.
After this, there are nnn lines. Each such line has three integers aia_iai​, bib_ibi​, and pip_ipi​: the starting day, the ending day, and the reward.
Output
Print one integer: the maximum amount of money you can earn.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤ai≤bi≤1091 \le a_i \le b_i \le 10^91≤ai​≤bi​≤109
1≤pi≤1091 \le p_i \le 10^91≤pi​≤109

Example
Input:
4
2 4 4
3 6 6
6 8 2
5 7 3

Output:
7
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n;
ll dp[N];
array<ll , 3>v[N];
int nxt[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n;
    vector<ll>f;
    for(int i = 0;i < n;i++) {
        cin>>v[i][0]>>v[i][1]>>v[i][2];
        nxt[i] = n + 1;
        f.emplace_back(v[i][0]);
    }
    sort(f.begin() , f.end());
    sort(v , v + n );
    for(int i = 0;i < n;i++) {
        nxt[i] = upper_bound(f.begin() , f.end() , v[i][1]) - f.begin();
    }
    for(int i = 0;i < n;i++) {
        dp[i + 1] = max(dp[i + 1] , dp[i]);
        dp[nxt[i]] = max(v[i][2] + dp[i] , dp[nxt[i]]);
    }
    cout<<dp[n];
}