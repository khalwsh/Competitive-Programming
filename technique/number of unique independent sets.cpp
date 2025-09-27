// this compute maximum numbers of clique for a graph G by getting G' and calcualte maximum number of indepenet set
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
ll g[50];
unordered_map<ll, ll> mp;

ll compOf(ll mask, int s) {
    ll comp = 0;
    ll st = (1LL << s);
    while (st) {
        int v = __builtin_ctzll(st);
        st &= st - 1;
        if ((comp >> v) & 1LL) continue;
        comp |= (1LL << v);
        ll neigh = g[v] & mask & ~comp;
        st |= neigh;
    }
    return comp;
}

ll dfs(ll mask) {
    if (mask == 0) return 1;
    auto it = mp.find(mask);
    if (it != mp.end()) return it->second;

    int f = __builtin_ctzll(mask);
    ll comp = compOf(mask, f);
    if (comp != mask) {
        ll a = dfs(comp);
        ll b = dfs(mask ^ comp);
        ll r = a * b;
        mp[mask] = r;
        return r;
    }

    int best = -1, md = -1;
    ll t = mask;
    while (t) {
        int u = __builtin_ctzll(t);
        t &= t - 1;
        int deg = __builtin_popcountll(g[u] & mask);
        if (deg > md) { md = deg; best = u; }
    }
    int v = best;
    ll without_v = mask & ~(1LL << v);
    ll r1 = dfs(without_v);
    ll r2 = dfs(without_v & ~g[v]);
    ll res = r1 + r2;
    mp[mask] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) {
        g[i] = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (a[i][j] == '0') g[i] |= (1LL << j);
        }
    }
    cout << dfs((1LL << n) - 1);
}
