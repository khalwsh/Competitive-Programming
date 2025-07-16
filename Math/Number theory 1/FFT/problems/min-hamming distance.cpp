#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
using cd = complex<double>;
const double PI = acos(-1);
void FFT(vector<cd> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1 , 0);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    FFT(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    while (result.size() != a.size() + b.size() - 1) result.pop_back();
    return result;
}

string s , t;
const int N = 5e5 + 10;

int main(){
    PRE();
    cin >> s >> t;
    int left = 0 , right = t.size();
    int res = 0;
    int n = s.size() , m = t.size();
    string chars = "ACTG";
    vector<ll>ans(n + 2 * m);
    for (int j = 0;j < 4;j++) {
        vector<ll>poly1(n) , poly2(m);
        for (int i = 0;i < n;i++) {
            if (s[i] == chars[j]) poly1[i]++;
        }
        for (int i = 0;i < m;i++) {
            if (t[i] == chars[j]) poly2[m - i - 1]++;
        }
        auto res2 = multiply(poly1 , poly2);
        for (int i = 0;i < res2.size();i++) {
            ans[i] += res2[i];
        }
    }
    ll mx = 0;
    for (int i = 0;i <= n - m;i++) {
        mx = max(mx , ans[i + m - 1]);
    }
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (m - mx <= mid) {
            right = mid - 1;
            res = mid;
        }else
            left = mid + 1;
    }
    cout << res << '\n';
}
