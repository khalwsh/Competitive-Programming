template <typename T>
struct prefix_sum {
// send zero base
    vector<vector<T> > a, prf;
    ll n, m;

    prefix_sum(vector<vector<T> > a2) {
        a = a2;
        n = a.size();
        m = a[0].size();
        prf = vector<vector<T> >(n + 1, vector<T>(m + 1, 0));
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= m; j++)
                prf[i][j] = a[i - 1][j - 1] + prf[i - 1][j] + prf[i][j - 1] - prf[i - 1][j - 1];
    }
    void add(int x1, int y1, int x2, int y2, ll val) {
        x1++ , y1++ , x2++ , y2++;
        diff[x1][y1] += val;
        diff[x2 + 1][y1] -= val;
        diff[x1][y2 + 1] -= val;
        diff[x2 + 1][y2 + 1] += val;
    }
    ll get(ll from_row, ll from_col, ll to_row, ll to_col) {
        from_col++, from_row++, to_row++, to_col++;
        return prf[to_row][to_col] - prf[from_row - 1][to_col] -
               prf[to_row][from_col - 1] +
               prf[from_row - 1][from_col - 1];
    }
};