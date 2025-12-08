/* problem statement text */
/*
CSES - Throwing Dice

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to calculate the number of ways to get a sum nnn by throwing dice. Each throw yields an integer between 1…61 \ldots 61…6.
For example, if n=10n=10n=10, some possible ways are 3+3+43+3+43+3+4, 1+4+1+41+4+1+41+4+1+4 and 1+1+6+1+11+1+6+1+11+1+6+1+1.
Input
The only input line contains an integer nnn.
Output
Print the number of ways modulo 109+710^9+7109+7.
Constraints

1≤n≤10181 \le n \le 10^{18}1≤n≤1018

Example
Input:
8

Output:
125
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
const int mod = 1e9 + 7;
ll mul(ll a , ll b) {
    return a % mod * (b % mod) % mod;
}
struct matrix {
    int siz;
    vector<vector<ll>>mat;
    matrix(int _siz) {
        mat.resize(_siz,vector<ll>(_siz));
        siz = _siz;
        for (int i = 0; i < siz; i++) {
            for (int j = 0; j < siz; j++) {
                mat[i][j] = 0;
            }
        }
    }
 
    matrix operator*(const matrix &b) {
        matrix c(siz);
        for (int i = 0; i < siz; i++) {
            for (int j = 0; j < siz; j++) {
                c.mat[i][j] = 0;
                for (int k = 0; k < siz; k++) {
                    c.mat[i][j] += mul(mat[i][k] , b.mat[k][j]);
                }
                c.mat[i][j] %= mod;
            }
        }
        return c;
    }
 
    matrix operator+(const matrix &b){
        matrix res(siz);
        for(int i = 0; i < siz; i++){
            for(int j = 0; j < siz; j++){
                res.mat[i][j] = mat[i][j] + b.mat[i][j];
                res.mat[i][j] %= mod;
            }
        }
        return res;
    }
 
    ll Trace() {
        ll sum = 0;
        for (int i = 0; i < siz; i++)sum += mat[i][i] % mod;
        return sum % mod;
    }
};
matrix Identity(int siz) {
    matrix res(siz);
    for (int i = 0; i < siz; i++) {
        for (int j = 0; j < siz; j++) {
            res.mat[i][j] = 0;
        }
    }
    for (int i = 0; i < siz; i++) {
        res.mat[i][i] = 1;
    }
    return res;
}
matrix ZeroMatrix(int siz) {
    matrix res(siz);
    return res;
}
matrix FastPower(matrix a, ll power) {
    matrix res = Identity(a.siz);
    while (power > 0) {
        if (power & 1) {
            res = res * a;
        }
        power >>= 1ll;
        a = a * a;
    }
    return res;
}
matrix Rotation(const matrix &a){
    matrix res(a.siz);
    int siz = a.siz;
    for(int i = 0; i < siz; i++){
        for(int j = 0; j < siz; j++){
            res.mat[j][siz - 1 - i] = a.mat[i][j];
        }
    }
    return res;
}
matrix Reflection(const matrix &a){
    matrix res(a.siz);
    int siz = a.siz;
    for(int i = 0; i < siz; i++){
        for(int j = 0; j < siz; j++){
            res.mat[i][siz - 1 - j] = a.mat[i][j];
        }
    }
    return res;
}
matrix SumPowers(matrix &a , ll _n) {
    if (_n == 0) return ZeroMatrix(a.siz);
    if (_n & 1) {
        return a * (Identity(a.siz) + SumPowers(a, _n - 1));
    } else {
        return SumPowers(a, _n / 2) * (Identity(a.siz) + FastPower(a, _n / 2));
    }
}
ll NthTerm(vector<ll>&FirstKthTerms,vector<ll>&Cof,ll n) {
    ll k = (int) FirstKthTerms.size();
    matrix base(k);
    for (int i = 0; i < k; ++i) {
        base.mat[i][0] = FirstKthTerms[i];
    }
    matrix trans(k);
    reverse(Cof.begin(), Cof.end());
    for (int i = 1; i < k; i++) {
        trans.mat[i - 1][i] = 1;
    }
    for (int i = 0; i < k; i++) {
        trans.mat[k - 1][i] = Cof[i];
    }
    matrix res = FastPower(trans, n - 1) * base;
    return res.mat[0][0];
}
vector<ll> dp , cof;
int main() {
    PRE();
    ll n; cin >> n;
    dp.resize(6);
    cof.resize(6 , 1);
    for (int j = 0; j < 6; j++) {
        ll s = 1;
        for (int t = 0; t < j; t++) s = (s + dp[t]) % mod;
        dp[j] = s;
    }
    cout << NthTerm(dp , cof , n) << '\n';
}