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
const int V = 20000;
const int M = 2*V + 1;
int main(){
    PRE();
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<ll> A(M, 0);
    for (int x : s) {
        A[x + V] = 1;
    }
    auto AA  = multiply(A, A);
    auto AAA = multiply(AA, A);

    vector<ll> B(2*M - 1, 0);
    for (int i = 0; i < M; i++) {
        if (A[i])
            B[2*i] = 1;
    }
    auto AB = multiply(A, B);

    vector<ll> T3(3*M - 1, 0);
    for (int x : s) {
        int k = 3*(x + V);
        if (k < (int)T3.size())
            T3[k]++;
    }

    sort(s.begin(), s.end());
    int minSum = s[0] + s[1] + s[2];
    int maxSum = s[n-1] + s[n-2] + s[n-3];

    for (int sum = minSum; sum <= maxSum; sum++) {
        int k = sum + 3*V;
        if (k < 0 || k >= (int)AAA.size()) continue;

        ll totalOrdered = AAA[k];
        ll twoPlus      = (k < (int)AB.size() ? AB[k] : 0LL);
        ll t3           = (k < (int)T3.size() ? T3[k] : 0LL);
        ll t2           = twoPlus - t3;

        ll cnt = (totalOrdered - 3*t2 - t3) / 6;
        if (cnt > 0) {
            cout << sum << " : " << cnt << "\n";
        }
    }
}