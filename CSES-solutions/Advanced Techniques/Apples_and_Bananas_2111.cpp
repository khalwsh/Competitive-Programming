/* problem statement text */
/*
CSES - Apples and Bananas

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn apples and mmm bananas, and each of them has an integer weight between 1…k1 \ldots k1…k. Your task is to calculate, for each weight www between 2…2k2 \dots 2k2…2k, the number of ways we can choose an apple and a banana whose combined weight is www.
Input
The first input line contains three integers kkk, nnn and mmm: the number kkk, the number of apples and the number of bananas.
The next line contains nnn integers a1,a2,…,ana_1,a_2,\ldots,a_na1​,a2​,…,an​: weight of each apple.
The last line contains mmm integers b1,b2,…,bmb_1,b_2,\ldots,b_mb1​,b2​,…,bm​: weight of each banana.
Output
For each integer www between 2…2k2 \ldots 2k2…2k print the number of ways to choose an apple and a banana whose combined weight is www.
Constraints

1≤k,n,m≤2⋅1051 \le k,n,m \le 2 \cdot 10^51≤k,n,m≤2⋅105
1≤ai≤k1 \le a_i \le k1≤ai​≤k
1≤bi≤k1 \le b_i \le k1≤bi​≤k

Example
Input:
5 3 4
5 2 5
4 3 2 3

Output:
0 0 1 2 1 2 4 2 0  

Explanation: For example for www = 888 there are 444 different ways: we can pick an apple of weight 555 in two different ways and a banana of weight 333 in two different ways.
*/
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
int main() {
    PRE();
    int k , n , m;cin >> k >> n >> m;
    vector<ll>poly1(k + 1) , poly2(k + 1);
    for (int i = 0;i < n;i++) {
        int x;cin >> x;
        poly1[x]++;
    }
    for (int j = 0;j < m;j++) {
        int x;cin >> x;
        poly2[x]++;
    }
    auto res = multiply(poly1 , poly2);
    for (int i = 2;i <= 2 * k;i++) {
        cout << res[i] << " ";
    }
    cout << '\n';
}