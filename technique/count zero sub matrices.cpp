#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
void rotate90(vector<vector<ll>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<ll>> rotated(n, vector<ll>(m));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            rotated[j][m - 1 - i] = matrix[i][j];
    matrix = move(rotated);
}
struct prefix_sum {
    vector<vector<ll> > a, prf;
    ll n, m;

    prefix_sum(vector<vector<ll> > a2) {
        a = a2;
        n = a.size();
        m = a[0].size();
        prf = vector<vector<ll> >(n + 1, vector<ll>(m + 1, 0));
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= m; j++)
                prf[i][j] = a[i - 1][j - 1] + prf[i - 1][j] + prf[i][j - 1] - prf[i - 1][j - 1];
    }

    ll get(ll from_row, ll from_col, ll to_row, ll to_col) {
        from_col++, from_row++, to_row++, to_col++;
        return prf[to_row][to_col] - prf[from_row - 1][to_col] -
               prf[to_row][from_col - 1] +
               prf[from_row - 1][from_col - 1];
    }
};
ll count_zero_sub_matrices(vector<vector<ll>> &grid) {
    int n = grid.size() , m = grid[0].size();
    if (n > m) {
        rotate90(grid);
        swap(n, m);
    }
    prefix_sum ps(grid);

    ll res = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = i; j < n; j++) {
            gp_hash_table<ll, ll> mp({}, {}, {}, {}, {1 << 13});
            ll sm = 0;
            mp[sm] = 1;
            for (ll k = 0; k < m; k++) {
                sm += ps.get(i, k, j, k);
                res += mp[sm];
                mp[sm]++;
            }
        }
    }
    return res;
}