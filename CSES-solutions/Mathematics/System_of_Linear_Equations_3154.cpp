/* problem statement text */
/*
CSES - System of Linear Equations

Time limit: 1.00 s
Memory limit: 512 MB

You are given n⋅(m+1)n\cdot(m+1)n⋅(m+1) coefficients ai,ja_{i,j}ai,j​ and bib_ibi​ which form the following nnn linear equations:

a1,1x1+a1,2x2+⋯+a1,mxm=b1(mod109+7)a_{1,1}x_1 + a_{1,2}x_2 + \dots + a_{1,m}x_m = b_1 \pmod {10^9 + 7}a1,1​x1​+a1,2​x2​+⋯+a1,m​xm​=b1​(mod109+7)
a2,1x1+a2,2x2+⋯+a2,mxm=b2(mod109+7)a_{2,1}x_1 + a_{2,2}x_2 + \dots + a_{2,m}x_m = b_2 \pmod {10^9 + 7}a2,1​x1​+a2,2​x2​+⋯+a2,m​xm​=b2​(mod109+7)
…\dots…
an,1x1+an,2x2+⋯+an,mxm=bn(mod109+7)a_{n,1}x_1 + a_{n,2}x_2 + \dots + a_{n,m}x_m = b_n \pmod {10^9 + 7}an,1​x1​+an,2​x2​+⋯+an,m​xm​=bn​(mod109+7)

Your task is to find any mmm integers x1,x2,…,xmx_1, x_2, \dots, x_mx1​,x2​,…,xm​  that satisfy the given equations.
Input
The first line has two integers nnn and mmm: the number of equations and variables.
The next nnn lines each have m+1m+1m+1 integers ai,1,ai,2,…,ai,m,bia_{i,1}, a_{i,2}, \dots, a_{i,m}, b_iai,1​,ai,2​,…,ai,m​,bi​: the coefficients of the iii-th equation.
Output
Print mmm integers x1,x2,…,xmx_1, x_2,\dots, x_mx1​,x2​,…,xm​: the values of the variables that satisfy the equations. The values must also satisfy 0≤xi<109+70 \le x_i < 10^9 + 70≤xi​<109+7. You can print any valid solution. If no solution exists print only −1-1−1.
Constraints

1≤n,m≤5001 \le n, m \le 5001≤n,m≤500
0≤ai,j,bi<109+70 \le a_{i,j}, b_i < 10^9 + 70≤ai,j​,bi​<109+7

Example
Input:
3 3
2 0 1 7
1 2 0 0
1 3 1 2

Output:
2 1000000006 3
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
 
int power(long long n, long long k) {
    int ans = 1 % mod;
    n %= mod;
    if (n < 0) n += mod;
    while (k) {
        if (k & 1) ans = (long long) ans * n % mod;
        n = (long long) n * n % mod;
        k >>= 1;
    }
    return ans;
}
 
/*
    a_{1,1}x_1 + a_{1,2}x_2 + ... + a_{1,m}x_m = b_1 % {mod}
    a_{2,1}x_1 + a_{2,2}x_2 + ... + a_{2,m}x_m = b_2 % {mod}
    ....
    a_{n,1}x_1 + a_{n,2}x_2 + ... + a_{n,m}x_m = b_n % {mod}
*/
int Gauss(vector<vector<int> > a, vector<int> &ans) {
    int n = a.size(), m = (int) a[0].size() - 1;
    vector<int> pos(m, -1);
    int free_var = 0;
    const long long MODSQ = (long long) mod * mod;
    int det = 1, rank = 0;
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int mx = row;
        for (int k = row; k < n; k++) if (a[k][col] > a[mx][col]) mx = k;
        if (a[mx][col] == 0) {
            det = 0;
            continue;
        }
        for (int j = col; j <= m; j++) swap(a[mx][j], a[row][j]);
        if (row != mx) det = det == 0 ? 0 : mod - det;
        det = 1LL * det * a[row][col] % mod;
        pos[col] = row;
        int inv = power(a[row][col], mod - 2);
        for (int i = 0; i < n && inv; i++) {
            if (i != row && a[i][col]) {
                int x = ((long long) a[i][col] * inv) % mod;
                for (int j = col; j <= m && x; j++) {
                    if (a[row][j]) a[i][j] = (MODSQ + a[i][j] - ((long long) a[row][j] * x)) % mod;
                }
            }
        }
        row++;
        ++rank;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; i++) {
        if (pos[i] == -1) free_var++;
        else ans[i] = ((long long) a[pos[i]][m] * power(a[pos[i]][i], mod - 2)) % mod;
    }
    for (int i = 0; i < n; i++) {
        long long val = 0;
        for (int j = 0; j < m; j++) val = (val + ((long long) ans[j] * a[i][j])) % mod;
        if (val != a[i][m]) return -1; //no solution
    }
    return free_var; //has solution
}
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    vector<vector<int> > A(n, vector<int>(m + 1));
    for (int i = 0; i < n; i++) for (int j = 0; j <= m; j++) cin >> A[i][j];
    vector<int> ans;
    if (Gauss(A, ans) == -1) {
        cout << -1 << "\n";
    } else {
        for (auto &val: ans)
            cout << val << " ";
    }
}
 