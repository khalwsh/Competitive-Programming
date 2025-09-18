#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#define int ll
using namespace std;
using ll = long long;
const char nl = '\n', sp = ' ';

const int mod = 1e9 + 7;

inline int add(int a, int b) {
    return (__int128(a) + b) % mod;
}

inline int mul(int a, int b) {
    return (__int128(a) * b) % mod;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    auto query = [&](int l, int r, vector<int> &v) {
        if (l > r) return 0ll;
        r = min(r, (int) v.size() - 1);
        l = max(l, 0ll);
        int ans = v[r];
        if (l) ans = add(ans, mod - v[l - 1]);
        return ans;
    };
    int ans = 0;
    vector<int> pre_mul, mn, mx, pre_mn, pre_mx;
    auto go = [&](auto &&go, int l, int r) -> void {
        if (l > r) return;
        if (l == r) {
            ans = add(ans, mul(a[l], a[l]));
            return;
        }
        int mid = (l + r) >> 1;
        mn.push_back(a[mid]);
        mx.push_back(a[mid]);
        pre_mul.push_back(mul(a[mid], a[mid]));
        for (int i = mid - 1; i >= l; i--) {
            mn.push_back(min(mn.back(), a[i]));
            mx.push_back(max(mx.back(), a[i]));
            pre_mul.push_back(add(pre_mul.back(), mul(mn.back(), mx.back())));
        }
        reverse(all(mn));
        pre_mn.push_back(mn.front());
        pre_mx.push_back(mx.front());
        for (int i = 1; i < mn.size(); i++) {
            pre_mn.push_back(add(mn[i], pre_mn[i - 1]));
            pre_mx.push_back(add(mx[i], pre_mx[i - 1]));
        }
        ans = add(ans, pre_mul.back());
        int mini = 2e9, maxi = 0;
        int sz = mn.size();
        for (int i = mid + 1; i <= r; i++) {
            mini = min(mini, a[i]);
            maxi = max(maxi, a[i]);
            int fg = upper_bound(all(mx), maxi) - begin(mx);
            int fl = lower_bound(all(mn), mini) - begin(mn) - 1;
            int rev_fl = sz - 1 - fl;
            if (fg > rev_fl) {
                ans = add(ans, mul(mul(mini, maxi), rev_fl));
                ans = add(ans, query(fg, (int) pre_mul.size() - 1, pre_mul));
                ans = add(ans, mul(maxi, query(sz - fg, fl, pre_mn)));
            } else if (fg < rev_fl) {
                ans = add(ans, mul(mul(mini, maxi), fg));
                ans = add(ans, query(rev_fl, (int) pre_mul.size() - 1, pre_mul));
                ans = add(ans, mul(mini, query(fg, rev_fl - 1, pre_mx)));
            } else {
                ans = add(ans, mul(mul(mini, maxi), fg));
                ans = add(ans, query(fg, (int) pre_mul.size() - 1, pre_mul));
            }
        }
        mn.clear();
        mx.clear();
        pre_mn.clear();
        pre_mx.clear();
        pre_mul.clear();
        go(go, l, mid - 1);
        go(go, mid + 1, r);
    };
    go(go, 0, n - 1);
    cout << ans << nl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
