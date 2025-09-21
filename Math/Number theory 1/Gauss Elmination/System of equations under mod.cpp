
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
