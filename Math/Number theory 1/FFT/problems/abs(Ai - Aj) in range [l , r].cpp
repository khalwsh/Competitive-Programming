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
typedef complex<double> C;
typedef vector<int> vi;
typedef vector<double> vd;

void fft(vector<C>& a) {
    int n = (int)a.size();
    int L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1.0);
    static vector<C> rt(2, C(1 ,0));  // (^ 10% faster if double)

    for (static int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i = k; i < 2 * k; i++) {
            R[i] = (i & 1) ? R[i / 2] * x : R[i / 2];
            rt[i] = R[i];
        }
    }

    vector<int> rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | ((i & 1) << L)) / 2;
    }

    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                double* x = (double*)&rt[j + k];
                double* y = (double*)&a[i + j + k];
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}
template<int M>
vi convMod(const vi &a, const vi &b) {
    if (a.empty() || b.empty()) return {};
    int resSize = (int)a.size() + (int)b.size() - 1;
    vi res(resSize);
    int B = 32 - __builtin_clz(resSize);
    int n = 1 << B;
    int cut = (int)sqrt(M);

    vector<C> L(n), R(n), outs(n), outl(n);
    for (int i = 0; i < (int)a.size(); i++) {
        L[i] = C(a[i] / cut, a[i] % cut);
    }
    for (int i = 0; i < (int)b.size(); i++) {
        R[i] = C(b[i] / cut, b[i] % cut);
    }

    fft(L);
    fft(R);

    for (int i = 0; i < n; i++) {
        int j = (-i) & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / C(0, 1);
    }

    fft(outl);
    fft(outs);

    for (int i = 0; i < resSize; i++) {
        ll av = ll(real(outl[i]) + 0.5);
        ll cv = ll(imag(outs[i]) + 0.5);
        ll bv = ll(imag(outl[i]) + 0.5) + ll(real(outs[i]) + 0.5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }

    return res;
}

const int mod = 132120577;
const int N = 1e5 + 1;
int main(){
    PRE();
    freopen("differences.in", "r", stdin);

    int t;cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> poly(n + 10), poly2(n + 10);
        for (int i = 0; i < n; i++) {
            int x, f;
            cin >> x >> f;
            poly[x] += f;
            poly[x] %= mod;
            poly2[n - x] += f;
            poly2[n - x] %= mod;
        }
        auto res = convMod<mod>(poly, poly2);
        ll pref[3 * n + 5] = {};
        for (int i = 0; i < res.size(); i++) {
            if (i - n > 0 && i - n <= n) {
                pref[i - n] += res[i];
                pref[i - n] %= mod;
            }
        }
        for(int i = 1 ; i <= n ; i++){
            pref[i] += pref[i - 1];
            pref[i] %= mod;
        }
        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            cout << ((pref[r] - pref[l - 1]) % mod + mod) % mod << '\n';
        }
    }
}