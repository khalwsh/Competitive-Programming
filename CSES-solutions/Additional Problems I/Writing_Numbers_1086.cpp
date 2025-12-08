/* problem statement text */
/*
CSES - Writing Numbers

Time limit: 1.00 s
Memory limit: 512 MB

You would like to write a list of positive integers 1,2,3,…1,2,3,\ldots1,2,3,… using your computer. However, you can press each key 000–999 at most nnn times during the process.
What is the last number you can write?
Input
The only input line contains the value of nnn.
Output
Print the last number you can write.
Constraints

1≤n≤10181 \le n \le 10^{18}1≤n≤1018

Example
Input:
5

Output:
12

Explanation: You can write the numbers 1,2,…,121,2,\ldots,121,2,…,12. This requires that you press key 111 five times, so you cannot write the number 131313.
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
string s;
pair<ll , ll> dp[20][2][2][10];
int vis[20][2][2][10] , tx = 1;
pair<ll , ll> solve(int i , bool t , bool p , int key) {
    if (i == s.size()) {
        return {!p , 0}; // count , value
    }
    auto &x = vis[i][t][p][key];
    if (x == tx && t) return dp[i][t][p][key];
    x = tx;
    int lim = (t ? 9 : s[i] - '0');
    pair<ll , ll> res = {0 , 0};
    for (int j = 0;j <= lim;j++) {
        auto tmp = solve(i + 1 , t || j != lim , p && j == 0 , key);
        res.first += tmp.first;
        res.second += tmp.second;
        if (j == key && !(key == 0 && p)) {
            res.second += tmp.first;
        }
    }
    return dp[i][t][p][key] = res;
}
ll solve(ll mid) {
    s = to_string(mid);
    while (s.size() < 20) s = "0" + s;
    ll mx = 0;
    for (int i = 0;i < 10;i++){
        mx = max(mx ,  solve(0 , 0 , 1 , i).second);
    }
    tx++;
    return mx;
}
int main() {
    PRE();
    ll n; cin >> n;
    ll left = 1 , right = 9 * n;
    ll res = n;
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (solve(mid) <= n) {
            res = mid;
            left = mid + 1;
        }else {
            right = mid - 1;
        }
    }
    cout << res;
}