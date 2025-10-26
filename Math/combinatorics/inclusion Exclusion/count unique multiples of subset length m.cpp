const int C = 21;
ull binom[C][C];
void init() {
    for(int i = 0; i < C; i++)
        binom[i][0] = binom[i][i] = 1;
    for(int i = 2; i < C; i++)
        for(int j = 1; j < i; j++)
            binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];

}
// calc(elements count , subset size , upper bound , elements)
// call init first
ll calc(ull n , ull m , ull y , vector<ull> &a) {
    ull ans = 0;
    for(ull msk = 0; msk < (1 << n); msk++) {
        if (popcount(msk) < m) continue;
        ull L = 1;
        for(int i = 0; i < n; i++) {
            if (~msk >> i & 1) continue;
            ull g = gcd(L, a[i]);
            if ((__int128)(L) * a[i] / g > y) L = y + 1;
            else L *= a[i] / g;
        }
        if (popcount(msk) % 2 == m % 2)
            ans += (y / L) * binom[popcount(msk)][m];
        else
            ans -= (y / L) * binom[popcount(msk)][m];
    }

    return ans;
}