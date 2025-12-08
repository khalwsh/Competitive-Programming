/* problem statement text */
/*
CSES - Signal Processing

Time limit: 1.00 s
Memory limit: 512 MB

You are given two integer sequences: a signal and a mask. Your task is to process the signal by moving the mask through the signal from left to right. At each mask position calculate the sum of products of aligned signal and mask values in the part where the signal and the mask overlap.
Input
The first input line consists of two integers nnn and mmm: the length of the signal and the length of the mask.
The next line consists of nnn integers a1,a2,…,ana_1,a_2,\ldots,a_na1​,a2​,…,an​ defining the signal.
The last line consists of mmm integers b1,b2,…,bmb_1,b_2,\ldots,b_mb1​,b2​,…,bm​ defining the mask.
Output
Print n+m−1n+m-1n+m−1 integers: the sum of products of aligned values at each mask position from left to right.
Constraints

1≤n,m≤2⋅1051 \le n,m \le 2 \cdot 10^51≤n,m≤2⋅105
1≤ai,bi≤1001 \le a_i,b_i \le 1001≤ai​,bi​≤100

Example
Input:
5 3
1 3 2 1 4
1 2 3

Output:
3 11 13 10 16 9 4

Explanation: For example, at the second mask position the sum of aligned products is 2⋅1+3⋅3=112 \cdot 1 + 3 \cdot 3 = 112⋅1+3⋅3=11.
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
 
using cd = complex<double>;
const double PI = acos(-1);
 
void FFT(vector<cd> &a, bool invert) {
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
            cd w(1, 0);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
 
    if (invert) {
        for (cd &x: a)
            x /= n;
    }
}
 
vector<ll> multiply(vector<ll> const &a, vector<ll> const &b) {
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
 
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    vector<ll> v(n + 2 * m, 0), mask(m);
    for (int i = 0; i < n; ++i) cin >> v[i + m];
    for (int i = 0; i < m; ++i) cin >> mask[i];
 
    reverse(mask.begin(), mask.end());
 
    auto res = multiply(v, mask);
    for (int i = m; i < 2 * m + n - 1; ++i)
        cout << res[i] << " ";
}