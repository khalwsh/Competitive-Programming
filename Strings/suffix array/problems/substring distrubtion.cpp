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
// it doesn't consider empty suffix
vector<int> buildSuffixArray(string s) {
    int n = s.size(); s += char(0);
    vector<int> p(n+1), c(n+1), c1(n+1), cnt(max(256, n+1)), p1(n+1);
    for(int i = 0; i <= n; i++) p[i] = i, c[i] = s[i];

    for(int k = 0; (1 << k) <= n; k++) {
        int len = 1 << k;

        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i <= n; i++) cnt[c[min(n, p[i] + len)]]++;
        for(int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i-1];
        for(int i = n; i >= 0; i--) p1[--cnt[c[min(n, p[i] + len)]]] = p[i];

        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i <= n; i++) cnt[c[p1[i]]]++;
        for(int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i-1];
        for(int i = n; i >= 0; i--) p[--cnt[c[p1[i]]]] = p1[i];

        c1[p[0]] = 0;
        for(int i = 1; i <= n; i++)
            c1[p[i]] = c1[p[i-1]] + (c[p[i]] != c[p[i-1]] || c[min(n,p[i]+len)] != c[min(n,p[i-1]+len)]);
        c.swap(c1);
        if(c[p[n]] == n) break;
    }

    vector<int> res;
    for(int i = 1; i <= n; i++) res.push_back(p[i]);
    return res;
}
// lcp[i] = longest common prefix (suf[i] , suf[i + 1])
vector<int> Kasai(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for(int i = 0; i < n; i++) rank[p[i]] = i;
    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if(rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
        if(k) k--;
    }
    return lcp;
}

int main() {
    PRE();
    string s; cin >> s;
    int n = s.size();
    auto suf = buildSuffixArray(s);
    auto lcp = Kasai(s , suf);
    vector<ll>pref(n + 2);
    auto add = [&](int l , int r) -> void {
        pref[l]++ , pref[r + 1]--;
    };
    add(1 , n - suf[0]);
    for (int i = 1;i < suf.size();i++) {
        add(lcp[i - 1] + 1 , n - suf[i]);
    }
    for (int i = 1;i <= n;i++) pref[i] += pref[i - 1];
    for (int i = 1;i <= n;i++) cout << pref[i] << " ";
}
