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
string kth(string &s , ll k) {
    int n = s.size();
    auto suf = buildSuffixArray(s);
    auto lcp = Kasai(s , suf);
    ll dis = n - suf[0];
    if (dis >= k) {
        return s.substr(suf[0] , k);
    }
    for (int i = 1;i < suf.size();i++) {
        dis += n - suf[i] - lcp[i - 1];
        if (dis >= k) {
            ll d = k - (dis - (n - suf[i] - lcp[i - 1]));
            return s.substr(suf[i] , lcp[i - 1] + d);
        }
    }
    return "-1";
}

int main() {
    PRE();
    string s;cin >> s;
    int n;cin >> n;
    vector<pair<ll , int>>Q;
    for (int i = 0;i < n;i++) {
        ll x;cin >> x;
        Q.emplace_back(x , i);
    }

    sort(Q.begin() , Q.end());
    vector<string>ans(n);
    n = s.size();
    auto suf = buildSuffixArray(s);
    auto lcp = Kasai(s , suf);
    int j = 0;

    ll dis = n - suf[0];

    while (j < Q.size() && dis >= Q[j].first) {
        ans[Q[j].second] = s.substr(suf[0] , Q[j].first);
        j++;
    }

    for (int i = 1;i < suf.size();i++) {
        dis += n - suf[i] - lcp[i - 1];
        while (j < Q.size() && dis >= Q[j].first) {
            ll d = Q[j].first - (dis - (n - suf[i] - lcp[i - 1]));
            ans[Q[j].second] =  s.substr(suf[i] , lcp[i - 1] + d);
            j++;
        }
    }
    for (int i = 0;i < Q.size();i++) cout << ans[i] << '\n';
}
