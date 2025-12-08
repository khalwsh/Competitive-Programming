/* problem statement text */
/*
CSES - Monster Game II

Time limit: 1.00 s
Memory limit: 512 MB

You are playing a game that consists of nnn levels. Each level has a monster. On levels 1,2,…,n−11,2,\dots,n-11,2,…,n−1, you can either kill or escape the monster. However, on level nnn you must kill the final monster to win the game.
Killing a monster takes sfsfsf time where sss is the monster's strength and fff is your skill factor. After killing a monster, you get a new skill factor  (lower skill factor is better). What is the minimum total time in which you can win the game?
Input
The first input line has two integers nnn and xxx: the number of levels and your initial skill factor.
The second line has nnn integers s1,s2,…,sns_1,s_2,\dots,s_ns1​,s2​,…,sn​: each monster's strength.
The third line has nnn integers f1,f2,…,fnf_1,f_2,\dots,f_nf1​,f2​,…,fn​: your new skill factor after killing a monster.
Output
Print one integer: the minimum total time to win the game.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤x≤1061 \le x \le 10^61≤x≤106
1≤si,fi≤1061 \le s_i, f_i \le 10^61≤si​,fi​≤106

Example
Input:
5 100
50 20 30 90 30
60 20 20 10 90

Output:
2600

Explanation: The best way to play is to kill the second and fifth monster.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
    freopen("out.txt", "w",stdout);
    freopen("error.txt", "w",stderr);
#endif
}
 
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<> > {
    static const ll inf = LLONG_MAX;
    bool isMn = false;
 
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
 
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
 
    void add(ll k, ll m) {
        if (isMn) k = -k, m = -m;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
 
    ll query(ll x) {
        auto l = *lower_bound(x);
        return (isMn ? -1 : 1) * (l.k * x + l.m);
    }
};
 
int main() {
    PRE();
    LineContainer cht;
    cht.isMn = true;
    int n;
    cin >> n;
    ll x;
    cin >> x;
    vector<ll> f(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) cin >> f[i];
    for (int i = 1; i <= n; i++) cin >> s[i];
    s[0] = x;
    cht.add(x, 0);
    vector<ll> dp(n + 1, 1e18);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = cht.query(f[i]);
        cht.add(s[i], dp[i]);
    }
    cout << dp[n] << '\n';
}