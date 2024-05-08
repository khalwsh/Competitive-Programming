const int M = 1001;
int C[M + 1][M + 1];
void PreCalculation() {
    C[0][0] = 1;
    for (int n = 1; n <= M; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k)
            C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }
}