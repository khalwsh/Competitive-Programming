const ld eps = 1e-9;

int Gauss(vector<vector<ld> > a, vector<ld> &ans) {
    int n = (int) a.size(), m = (int) a[0].size() - 1;
    vector<int> pos(m, -1);
    ld det = 1;
    int rank = 0;
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int mx = row;
        for (int i = row; i < n; i++) if (fabs(a[i][col]) > fabs(a[mx][col])) mx = i;
        if (fabs(a[mx][col]) < eps) {
            det = 0;
            continue;
        }
        for (int i = col; i <= m; i++) swap(a[row][i], a[mx][i]);
        if (row != mx) det = -det;
        det *= a[row][col];
        pos[col] = row;
        for (int i = 0; i < n; i++) {
            if (i != row && fabs(a[i][col]) > eps) {
                ld c = a[i][col] / a[row][col];
                for (int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
            }
        }
        ++row;
        ++rank;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; i++) {
        if (pos[i] != -1) ans[i] = a[pos[i]][m] / a[pos[i]][i];
    }
    for (int i = 0; i < n; i++) {
        ld sum = 0;
        for (int j = 0; j < m; j++) sum += ans[j] * a[i][j];
        if (fabs(sum - a[i][m]) > eps) return -1; //no solution
    }
    for (int i = 0; i < m; i++) if (pos[i] == -1) return 2; //infinte solutions
    return 1; //unique solution
}