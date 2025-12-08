/* problem statement text */
/*
CSES - Elevator Rides

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn people who want to get to the top of a building which has only one elevator. You know the weight of each person and the maximum allowed weight in the elevator. What is the minimum number of elevator rides?
Input
The first input line has two integers nnn and xxx: the number of people and the maximum allowed weight in the elevator.
The second line has nnn integers w1,w2,…,wnw_1,w_2,\dots,w_nw1​,w2​,…,wn​: the weight of each person.
Output
Print one integer: the minimum number of rides.
Constraints

1≤n≤201 \le n \le 201≤n≤20
1≤x≤1091 \le x \le 10^91≤x≤109
1≤wi≤x1 \le w_i \le x1≤wi​≤x

Example
Input:
4 10
4 8 6 1

Output:
2
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n , m;cin>>n>>m;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    pair<int , ll>dp[1<<n];
    for(int i = 0;i < (1<<n);i++)dp[i] = make_pair(1e9 , 1e18);
    dp[0] = {1 , 0};
    for(int i = 1;i < (1<<n);i++) {
        for(int j = 0;j < n;j++) {
            if(i & (1<<j)){
                auto [x , y] = dp[i ^ (1<<j)];
                if(v[j] + y <= m) {
                    dp[i] = min(dp[i] , {x , y + v[j]});
                }else
                    dp[i] = min(dp[i]  , {x + 1 , v[j]});
            }
        }
    }
    cout<<dp[(1<<n) - 1].first;
}