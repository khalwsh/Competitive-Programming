/* problem statement text */
/*
CSES - One Bit Positions

Time limit: 1.00 s
Memory limit: 512 MB

You are given a binary string of length nnn. Your task is to calculate, for every kkk between 1…n−11 \ldots n-11…n−1, the number of ways we can choose two positions iii and jjj such that i−j=ki-j=ki−j=k and there is a one-bit at both positions.
Input
The only input line has a string that consists only of characters 000 and 111.
Output
For every distance kkk between 1…n−11\ldots n-11…n−1 print the number of ways we can choose two such positions.
Constraints

2≤n≤2⋅1052 \le n \le 2 \cdot 10^52≤n≤2⋅105

Example
Input:
1001011010

Output:
1 2 3 0 2 1 0 1 0
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
 
const int N = 2e5 + 10;
vector<ll> f1(N + 1), f2(N + 1);
 
int main() {
    PRE();
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '1') f1[i]++, f2[N - i]++;
    }
    auto res = multiply(f1, f2);
    for (int i = N + 1; i <= N + n - 1; i++) {
        cout << res[i] << ' ';
    }
}