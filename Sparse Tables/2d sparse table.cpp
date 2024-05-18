const int M = 1e3 + 1;
int f[10][10][M][M];
int grid[M][M];
int n, m;
int combine(int a, int b){
    return max(a , b);
}
void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            f[0][0][i][j] = grid[i][j];
        }
    }
    for (int k1 = 0; k1 < 10; k1++) {
        for (int k2 = 0; k2 < 10; k2++) {
            if (k1 == 0 && k2 == 0) continue;
            for (int i = 0; i + (1 << k1) <= n; i++) {
                for (int j = 0; j + (1 << k2) <= m; j++) {
                    if (k1 > 0) {
                        f[k1][k2][i][j] = combine(f[k1 - 1][k2][i][j], f[k1 - 1][k2][i + (1 << (k1 - 1))][j]);
                    }
                    if (k2 > 0) {
                        f[k1][k2][i][j] = combine(f[k1][k2 - 1][i][j], f[k1][k2 - 1][i][j + (1 << (k2 - 1))]);
                    }
                    if (k1 > 0 && k2 > 0) {
                        f[k1][k2][i][j] = combine(combine(
                                f[k1 - 1][k2 - 1][i][j],
                                f[k1 - 1][k2 - 1][i + (1 << (k1 - 1))][j]), combine(
                                f[k1 - 1][k2 - 1][i][j + (1 << (k2 - 1))],
                                f[k1 - 1][k2 - 1][i + (1 << (k1 - 1))][j + (1 << (k2 - 1))])
                        );
                    }
                }
            }
        }
    }
}
int query(int l, int d, int r, int u) {
    int k1 = std::__lg(r - l + 1);
    int k2 = std::__lg(u - d + 1);
    return combine(combine(
                           f[k1][k2][l][d],
                           f[k1][k2][r - (1 << k1) + 1][d]),
                   combine(
                           f[k1][k2][l][u - (1 << k2) + 1],
                           f[k1][k2][r - (1 << k1) + 1][u - (1 << k2) + 1])
    );
}