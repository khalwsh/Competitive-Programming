long long randomLongLong(long long l, long long r) {
    random_device rd;
    mt19937_64 rng(rd());
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}
static const unsigned long long MOD = ((unsigned long long)1 << 61) - 1;
static const unsigned long long BASE = randomLongLong(97 , 253);

static inline unsigned long long modAdd(unsigned long long a, unsigned long long b) {
    a += b;
    if(a >= MOD) a -= MOD;
    return a;
}

static inline unsigned long long modSub(unsigned long long a, unsigned long long b) {
    return (a >= b ? a - b : a + MOD - b);
}

static inline unsigned long long modMul(unsigned long long a, unsigned long long b) {
    __uint128_t t = a;
    t *= b;
    // The trick for mod 2^61-1: split into high and low parts.
    t = (t >> 61) + (t & MOD);
    if(t >= MOD) t -= MOD;
    return (unsigned long long)t;
}

unsigned long long modExp(unsigned long long b, unsigned long long e) {
    unsigned long long res = 1;
    while(e) {
        if(e & 1)
            res = modMul(res, b);
        b = modMul(b, b);
        e >>= 1;
    }
    return res;
}

unsigned long long modInv(unsigned long long a) {
    return modExp(a, MOD - 2);
}

struct Fenw {
    int n;
    vector<unsigned long long> fenw;
    explicit Fenw(int n) : n(n) {
        fenw.assign(n + 1, 0);
    }
    void update(int i, unsigned long long delta) {
        for(; i <= n; i += i & -i)
            fenw[i] = modAdd(fenw[i], delta);
    }
    [[nodiscard]] unsigned long long query(int i) const {
        unsigned long long res = 0;
        for(; i > 0; i -= i & -i)
            res = modAdd(res, fenw[i]);
        return res;
    }
    [[nodiscard]] unsigned long long rangeQuery(int l, int r) const {
        return modSub(query(r), query(l - 1));
    }
};

// ------------------------
// DynamicHash Template
// ------------------------
//
// This class builds two Fenwick trees:
//   - The forward tree stores for each index i (0-indexed) the contribution:
//         a[i] * BASE^i
//   - The reverse tree stores for each index i the contribution:
//         a[i] * BASE^(n-1-i)
//
// Then the forward hash of a substring [l, r] is computed as:
//    H_fwd = (sum_{i=l}^{r} a[i]*BASE^i) / BASE^l,
// and the reverse hash is
//    H_rev = (sum_{i=l}^{r} a[i]*BASE^(n-1-i)) / BASE^(n-1-r).
//
// A match (H_fwd == H_rev) shows that the substring is a palindrome.

template<typename T>
class DynamicHash {
    int n;
    vector<unsigned long long> a;
    vector<unsigned long long> p, invp;

    Fenw fenw_forward, fenw_reverse;
public:

    template<typename Container>
    explicit DynamicHash(const Container &c): fenw_forward(c.size()), fenw_reverse(c.size()){
        n = c.size();
        a.resize(n);
        p.resize(n + 1);
        invp.resize(n + 1);

        p[0] = 1;
        for (int i = 1; i <= n; i++) {
            p[i] = modMul(p[i - 1], BASE);
        }
        for (int i = 0; i <= n; i++) {
            invp[i] = modInv(p[i]);
        }

        for (int i = 0; i < n; i++) {
            a[i] = (unsigned long long)c[i];

            unsigned long long valForward = modMul(a[i], p[i]);
            fenw_forward.update(i + 1, valForward);

            unsigned long long valReverse = modMul(a[i], p[n - 1 - i]);
            fenw_reverse.update(i + 1, valReverse);
        }
    }

    DynamicHash(const string &s): DynamicHash(vector<char>(s.begin(), s.end())) { }

    [[nodiscard]] unsigned long long get_hash(int l, int r) const {
        unsigned long long sum = fenw_forward.rangeQuery(l + 1, r + 1);
        return modMul(sum, invp[l]);
    }

    [[nodiscard]] unsigned long long get_reverse_hash(int l, int r) const {
        unsigned long long sum = fenw_reverse.rangeQuery(l + 1, r + 1);
        return modMul(sum, invp[n - 1 - r]);
    }

    void update(int idx, T newVal) {
        unsigned long long nv = (unsigned long long)newVal;
        unsigned long long ov = a[idx];
        a[idx] = nv;

        unsigned long long diff = (nv >= ov ? nv - ov : nv + MOD - ov);

        unsigned long long diffForward = modMul(diff, p[idx]);
        fenw_forward.update(idx + 1, diffForward);

        unsigned long long diffReverse = modMul(diff, p[n - 1 - idx]);
        fenw_reverse.update(idx + 1, diffReverse);
    }
};