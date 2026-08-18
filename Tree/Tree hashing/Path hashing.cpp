static constexpr int N = 500000 + 5;
static constexpr int K   = 20;

static constexpr int mod1  = 1000000009;
static constexpr int mod2  = 1000000021;
static constexpr int b1  = 91;
static constexpr int b2  = 53;

struct Hash {
    int a, b;
    bool operator==(const Hash& other) const {
        return a == other.a && b == other.b;
    }
};

int n;
vector<int> adj[N];
int up[N][K];
int depth[N];
char vals[N];
Hash phash[N];     // hash from root to node
Hash shash[N];      // rolling hash built along root -> node order

int pw1[N], inv1[N];
int pw2[N], inv2[N];

inline int norm(ll x, int mod) {
    x %= mod;
    if (x < 0) x += mod;
    return (int)x;
}

inline int addmod(int a, int b, int mod) {
    return norm((ll)a + b, mod);
}

inline int mulmod(int a, int b, int mod) {
    return norm((ll)a * b, mod);
}

int modpow(int a, ll e, int mod) {
    ll r = 1, x = a % mod;
    while (e > 0) {
        if (e & 1) r = (r * x) % mod;
        x = (x * x) % mod;
        e >>= 1;
    }
    return (int)r;
}

void calc_powers() {
    pw1[0] = pw2[0] = 1;
    inv1[0] = inv2[0] = 1;

    int invBase1 = modpow(b1, mod1 - 2, mod1);
    int invBase2 = modpow(b2, mod2 - 2, mod2);

    for (int i = 1; i < N; ++i) {
        pw1[i] = mulmod(pw1[i - 1], b1, mod1);
        pw2[i] = mulmod(pw2[i - 1], b2, mod2);
        inv1[i] = mulmod(inv1[i - 1], invBase1, mod1);
        inv2[i] = mulmod(inv2[i - 1], invBase2, mod2);
    }
}

void init(int n) {
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        depth[i] = 0;
        vals[i] = ' ';
        phash[i] = {0, 0};
        shash[i] = {0, 0};
        for (int j = 0; j < K; ++j) up[i][j] = -1;
    }
}

void dfs(int u, int p, Hash curPref, Hash curRev, int dep) {
    up[u][0] = p;
    depth[u] = dep;

    int x = vals[u] - 'a' + 1;

    curPref.a = addmod(curPref.a, mulmod(pw1[dep], x, mod1), mod1);
    curPref.b = addmod(curPref.b, mulmod(pw2[dep], x, mod2), mod2);

    curRev.a = addmod(mulmod(curRev.a, b1, mod1), x, mod1);
    curRev.b = addmod(mulmod(curRev.b, b2, mod2), x, mod2);

    phash[u] = curPref;
    shash[u] = curRev;

    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, curPref, curRev, dep + 1);
    }
}

void build() {
    dfs(1, -1, {0, 0}, {0, 0}, 0);

    for (int j = 1; j < K; ++j) {
        for (int i = 1; i <= n; ++i) {
            int mid = up[i][j - 1];
            up[i][j] = (mid == -1 ? -1 : up[mid][j - 1]);
        }
    }
}

int kthAncestor(int u, int k) {
    for (int i = 0; i < K && u != -1; ++i) {
        if (k & (1 << i)) u = up[u][i];
    }
    return u;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    u = kthAncestor(u, depth[u] - depth[v]);
    if (u == v) return u;

    for (int i = K - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

Hash getHash(int u, int v) {
    int common = lca(u, v);
    int parentCommon = up[common][0];

    int leftLen = depth[u] - depth[common];
    int rightLen = depth[v] - depth[common];

    int leftA = shash[u].a;
    int leftB = shash[u].b;

    if (parentCommon != -1) {
        leftA = addmod(leftA, -mulmod(shash[parentCommon].a, pw1[leftLen + 1], mod1), mod1);
        leftB = addmod(leftB, -mulmod(shash[parentCommon].b, pw2[leftLen + 1], mod2), mod2);
    }

    int rightA = 0, rightB = 0;
    if (rightLen > 0) {
        int rawA = addmod(phash[v].a, -phash[common].a, mod1);
        int rawB = addmod(phash[v].b, -phash[common].b, mod2);

        rightA = mulmod(rawA, inv1[depth[common] + 1], mod1);
        rightB = mulmod(rawB, inv2[depth[common] + 1], mod2);
    }

    int totalLeft = leftLen + 1;
    Hash res;
    res.a = addmod(leftA, mulmod(rightA, pw1[totalLeft], mod1), mod1);
    res.b = addmod(leftB, mulmod(rightB, pw2[totalLeft], mod2), mod2);

    return res;
}