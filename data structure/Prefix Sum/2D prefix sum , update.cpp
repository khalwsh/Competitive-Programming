template <typename T>
struct prefix_sum {
    vector<vector<T>> a;
    vector<vector<T>> prf;
    vector<vector<T>> diff;
    ll n = 0, m = 0;
    prefix_sum(int _n , int _m) {
        n = _n , m = _m;
        a.resize(n + 3 , vector<T>(m + 3));
        prf.resize(n + 3 , vector<T>(m + 3));
        diff.resize(n + 3, vector<T>(m + 3));
    }
    void add(ll x1, ll y1, ll x2, ll y2, T val) {
        ll X1 = x1 + 1;
        ll Y1 = y1 + 1;
        ll X2 = x2 + 1;
        ll Y2 = y2 + 1;
        diff[X1][Y1] += val;
        diff[X2 + 1][Y1] -= val;
        diff[X1][Y2 + 1] -= val;
        diff[X2 + 1][Y2 + 1] += val;
    }
    void build() {
        for (ll i = 1; i <= n; ++i) {
            for (ll j = 1; j <= m; ++j) {
                diff[i][j] = diff[i][j] + diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            }
        }
        for (ll i = 1; i <= n; ++i) {
            for (ll j = 1; j <= m; ++j) {
                T cell = a[i - 1][j - 1] + diff[i][j]; 
                prf[i][j] = cell + prf[i - 1][j] + prf[i][j - 1] - prf[i - 1][j - 1];
            }
        }
    }
    T get(ll from_row, ll from_col, ll to_row, ll to_col) {
        ll r1 = from_row + 1;
        ll c1 = from_col + 1;
        ll r2 = to_row + 1;
        ll c2 = to_col + 1;
        return prf[r2][c2] - prf[r1 - 1][c2] - prf[r2][c1 - 1] + prf[r1 - 1][c1 - 1];
    }
};