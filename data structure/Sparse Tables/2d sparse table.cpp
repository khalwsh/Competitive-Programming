const int M = 1e3 + 1;
const int LOG = 10;
int f[LOG][LOG][M][M];
int grid[M][M];
int n, m;
/*
 2d sparse table f[log(n)][log(m)][N][M] --> take m * n * log(n) * log(m) memory and time and o(1) for quering
 it can be used for min , max , gcd , lcm , and , or ,... any non mutable function
 it support no updates.
 note it written like that to be cache friendly don't change the dimesions order.
 if your problem have N = 5000 change the LOG make it 13 
 if your problem have N * M <= 1e6 then you have to use vectors instead of arrays but avoid that as possible
*/
int combine(int a, int b){
    return max(a , b);
}
void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            f[0][0][i][j] = grid[i][j];
        }
    }
    for (int k1 = 0; k1 < LOG; k1++) {
        for (int k2 = 0; k2 < LOG; k2++) {
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