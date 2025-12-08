/* problem statement text */
/*
CSES - And Subset Count

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the number of non-empty subsets whose elements' bitwise and is equal to kkk for each k=0,1,…,nk = 0, 1,\dots, nk=0,1,…,n.
Input
The first line has an integer nnn: the size of the array.
The next line has nnn integers a1,a2,…,ana_1, a_2,\dots, a_na1​,a2​,…,an​: the contents of the array.
Output
Print n+1n + 1n+1 integers as specified above modulo 109+710^9 + 7109+7.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
0≤ai≤n0 \le a_i \le n0≤ai​≤n

Example
Input:
4
3 1 3 4

Output:
7 4 0 3 1
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
const int mod = 1e9 + 7;
const int N = 20;
// adding subset to superset , dp 1 base
void forward1(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j] += dp[j ^ (1 << i)];
        }
    }
}
// adding superset to subset , dp 1 base
void forward2(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] += dp[j] , dp[j ^ (1 << i)] %= mod;
        }
    }
}
// undo subset to super set , dp 1 base
void backword1(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j] -= dp[j ^ (1 << i)];
        }
    }
}
// undo superset to subset
void backword2(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] -= dp[j] , dp[j ^ (1 << i)] = (dp[j ^ (1 << i)] + mod) % mod;
        }
    }
}
ll fp(ll a , ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
vector<ll> dp(1 << N);
vector<ll> dp2(1 << N);
int main() {
    PRE();
    int n;cin >> n;
    for (int i = 0;i < n;i++) {
        int x;cin >> x;
        dp[x]++;
    }
    forward2(dp , N);
    for (int i = 0;i < 1 << N;i++) {
        dp2[i] = (fp(2 , dp[i]) - 1 + mod) % mod;
    }
    backword2(dp2 , N);
    for (int i = 0;i <= n;i++)
        cout << dp2[i] << ' ';
}