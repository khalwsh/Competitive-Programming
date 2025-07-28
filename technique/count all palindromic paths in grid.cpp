#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;
static int dp[500][500], ndp[500][500];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> g(n);
    for(int i=0;i<n;i++) cin >> g[i];
    if (g[0][0] != g[n-1][n-1]) {
        cout << 0 << "\n";
        return 0;
    }
    dp[0][n-1] = 1;
    for(int k = 0; k < n - 1; k++){
        for(int i=0;i<n;i++) 
            memset(ndp[i], 0, n * sizeof(int));

        int i1_lo = max(0, k-(n-1));
        int i1_hi = min(k, n-1);
        int i2_lo = max(0, (n-1)-k);
        int i2_hi = n-1;

        for(int i1 = i1_lo; i1 <= i1_hi; i1++){
            int j1 = k - i1;
            if (j1 < 0 || j1 >= n) continue;
            for(int i2 = i2_lo; i2 <= i2_hi; i2++){
                int ways = dp[i1][i2];
                if (!ways) continue;
                int j2 = (2*n-2-k) - i2;
                
                int ni1 = i1+1, nj1 = j1;
                int ni2 = i2-1, nj2 = j2;
                if (ni1 < n && ni2 >= 0) {
                    if (g[ni1][nj1] == g[ni2][nj2]) {
                        ndp[ni1][ni2] = (ndp[ni1][ni2] + ways) % MOD;
                    }
                }
                ni1 = i1+1; nj1 = j1;
                ni2 = i2;   nj2 = j2-1;
                if (ni1 < n && nj2 >= 0) {
                    if (g[ni1][nj1] == g[ni2][nj2]) {
                        ndp[ni1][ni2] = (ndp[ni1][ni2] + ways) % MOD;
                    }
                }
                ni1 = i1;   nj1 = j1+1;
                ni2 = i2-1; nj2 = j2;
                if (nj1 < n && ni2 >= 0) {
                    if (g[ni1][nj1] == g[ni2][nj2]) {
                        ndp[ni1][ni2] = (ndp[ni1][ni2] + ways) % MOD;
                    }
                }
                ni1 = i1;   nj1 = j1+1;
                ni2 = i2;   nj2 = j2-1;
                if (nj1 < n && nj2 >= 0) {
                    if (g[ni1][nj1] == g[ni2][nj2]) {
                        ndp[ni1][ni2] = (ndp[ni1][ni2] + ways) % MOD;
                    }
                }
            }
        }
        for(int i=0;i<n;i++)
            memcpy(dp[i], ndp[i], n * sizeof(int));
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        ans = (ans + dp[i][i]) % MOD;
    }
    cout << ans << "\n";
}
