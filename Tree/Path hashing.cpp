
const int N = 500000 + 5;
const int K = 20;

const int mod1 = 1000000009;
const int mod2 = 1000000021;
const int base1 = 91;
const int base2 = 53;

int pw1[N], inv1[N], pw2[N], inv2[N];

inline int norm(ll x, int mod) {
    x %= mod;
    if (x < 0) x += mod;
    return (int) x;
}

inline int add(int a, int b, int mod) { return norm((ll) a + b, mod); }
inline int mul(int a, int b, int mod) { return norm((ll) a * b, mod); }

int modpow(int a, ll e, int mod) {
    ll r = 1;
    ll x = a % mod;
    while (e > 0) {
        if (e & 1) r = (r * x) % mod;
        x = (x * x) % mod;
        e >>= 1;
    }
    return (int) r;
}

void PreCalc() {
    pw1[0] = pw2[0] = 1;
    inv1[0] = inv2[0] = 1;
    int invBase1 = modpow(base1, mod1 - 2, mod1);
    int invBase2 = modpow(base2, mod2 - 2, mod2);
    for (int i = 1; i < N; ++i) {
        pw1[i] = mul(pw1[i - 1], base1, mod1);
        inv1[i] = mul(inv1[i - 1], invBase1, mod1);
        pw2[i] = mul(pw2[i - 1], base2, mod2);
        inv2[i] = mul(inv2[i - 1], invBase2, mod2);
    }
}

int n;
vector<int> adj[N];
int UP[N][K];
pair<int, int> h[N], h_r[N];
int parentArr[N], depthArr[N];
char vals[N];

void dfs(int u, int p, pair<int, int> curr_h, pair<int, int> curr_h_r, int l) {
    parentArr[u] = p;
    depthArr[u] = l;

    curr_h.first = add(curr_h.first, mul(pw1[l], vals[u] - 'a' + 1, mod1), mod1);
    curr_h.second = add(curr_h.second, mul(pw2[l], vals[u] - 'a' + 1, mod2), mod2);

    curr_h_r.first = add(mul(curr_h_r.first, pw1[1], mod1),
                         mul(pw1[0], vals[u] - 'a' + 1, mod1), mod1);
    curr_h_r.second = add(mul(curr_h_r.second, pw2[1], mod2),
                          mul(pw2[0], vals[u] - 'a' + 1, mod2), mod2);

    h[u] = curr_h;
    h_r[u] = curr_h_r;

    for (int v: adj[u])
        if (v != p) {
            dfs(v, u, curr_h, curr_h_r, l + 1);
        }
}

int Get_Kth_Anc(int u, int k) {
    for (int i = 0; i < K && u != -1; ++i) {
        if (k & (1 << i)) {
            u = UP[u][i];
            if (u == -1) return -1;
        }
    }
    return u;
}

void Build() {
    dfs(1, -1, {0, 0}, {0, 0}, 0);
    for (int i = 1; i <= n; ++i) UP[i][0] = parentArr[i];
    for (int i = 1; i < K; ++i) {
        for (int j = 1; j <= n; ++j) {
            int mid = UP[j][i - 1];
            if (mid == -1) UP[j][i] = -1;
            else UP[j][i] = UP[mid][i - 1];
        }
    }
}

int Get_LCA(int u, int v) {
    if (depthArr[u] < depthArr[v]) swap(u, v);
    int diff = depthArr[u] - depthArr[v];
    u = Get_Kth_Anc(u, diff);
    if (u == v) return u;
    for (int i = K - 1; i >= 0; --i) {
        if (UP[u][i] != UP[v][i]) {
            u = UP[u][i];
            v = UP[v][i];
        }
    }
    return UP[u][0];
}

pair<int, int> Get_Hash(int u, int v) {
    int common = Get_LCA(u, v);
    int depth_common = depthArr[common];
    int parent_common = parentArr[common];

    int dist_left = depthArr[u] - depth_common;
    int left1 = h_r[u].first;
    int left2 = h_r[u].second;
    if (parent_common != -1) {
        left1 = add(left1, -mul(h_r[parent_common].first, pw1[dist_left + 1], mod1), mod1);
        left2 = add(left2, -mul(h_r[parent_common].second, pw2[dist_left + 1], mod2), mod2);
    }

    int len_right_excl = depthArr[v] - depth_common;
    int right1 = 0, right2 = 0;
    if (len_right_excl > 0) {
        int raw1 = add(h[v].first, -h[common].first, mod1);
        int raw2 = add(h[v].second, -h[common].second, mod2);
        right1 = mul(raw1, inv1[depth_common + 1], mod1);
        right2 = mul(raw2, inv2[depth_common + 1], mod2);
    }

    int left_len = dist_left + 1;
    int combined1 = add(left1, mul(right1, pw1[left_len], mod1), mod1);
    int combined2 = add(left2, mul(right2, pw2[left_len], mod2), mod2);

    return {combined1, combined2};
}

pair<int, int> GetFullHash(const string &s) {
    int ln = (int) s.length();
    int x1 = 0, x2 = 0;
    for (int i = 0; i < ln; ++i) {
        x1 = add(x1, mul(pw1[i], s[i] - 'a' + 1, mod1), mod1);
        x2 = add(x2, mul(pw2[i], s[i] - 'a' + 1, mod2), mod2);
    }
    return {x1, x2};
}
// call PreCalc before test cases and init after you take n in each test case
void init() {
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        h[i] = {0, 0};
        h_r[i] = {0, 0};
        vals[i] = ' ';
        parentArr[i] = -1;
        depthArr[i] = 0;
        for (int j = 0; j < K; ++j) UP[i][j] = -1;
    }
}