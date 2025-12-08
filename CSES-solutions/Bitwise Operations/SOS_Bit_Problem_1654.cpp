/* problem statement text */
/*
CSES - SOS Bit Problem

Time limit: 1.00 s
Memory limit: 512 MB

Given a list of nnn integers, your task is to calculate for each element xxx:

the number of elements yyy such that x∣y=xx \mid y = xx∣y=x
the number of elements yyy such that x&y=xx \mathrel{\&} y = xx&y=x
the number of elements yyy such that x&y≠0x \mathrel{\&} y \neq 0x&y=0

Input
The first line has an integer nnn: the size of the list.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the elements of the list.
Output
Print nnn lines: for each element the required values.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤xi≤1061 \le x_i \le 10^61≤xi​≤106

Example
Input:
5
3 7 2 9 2

Output:
3 2 5
4 1 5
2 4 4
1 1 3
2 4 4
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
// adding subset to superset , dp 1 base
void forward1(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j] += dp[j ^ (1 << i)];
        }
    }
}
// adding superset to subset , dp 1 base
void forward2(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] += dp[j];
        }
    }
}
// undo subset to super set , dp 1 base
void backword1(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j] -= dp[j ^ (1 << i)];
        }
    }
}
// undo superset to subset
void backword2(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] -= dp[j];
        }
    }
}
const int N = 1 << 20;
vector<int>a(N , 0);
int main() {
    PRE();
    int n;cin >> n;
    vector<int>v;
    for (int i = 0;i < n;i++) {
        int x; cin >> x;
        a[x]++;
        v.emplace_back(x);
    }
    forward1(a , 20);
    auto r1 = a;
    backword1(a , 20);
    forward2(a , 20);
    auto r2 = a;
    backword2(a , 20);
    for (auto &x : v) {
        int z = r1[(N - 1) ^ x]; // x & y = 0
        cout << r1[x] << " " << r2[x] << " " << n - z << '\n';
    }
}