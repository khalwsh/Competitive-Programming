const uint64_t HashMod = (1ULL << 61) - 1;
const uint64_t seed1 = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base1 = mt19937_64(seed1)() % (HashMod / 3) + (HashMod / 3);
const uint64_t seed2 = chrono::system_clock::now().time_since_epoch().count() * 2ULL;
const uint64_t base2 = mt19937_64(seed2)() % (HashMod / 3) + (HashMod / 3);
uint64_t base_pow[2][N];
int64_t MUL(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & HashMod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & HashMod) + (ret >> 61);
    ret = (ret & HashMod) + (ret >> 61);
    return (int64_t) ret - 1;
}
void init() {
    base_pow[0][0] = 1;
    for (int i = 1; i < N; i++) {
        base_pow[0][i] = MUL(base_pow[0][i - 1], base1);
    }
    base_pow[1][0] = 1;
    for (int i = 1; i < N; i++) {
        base_pow[1][i] = MUL(base_pow[1][i - 1], base2);
    }

}
struct PolyHash {
    /// Remove suf vector and usage if reverse hash is not required for more speed
    vector<int64_t> pref[2], suf[2];

    template<typename T>
    PolyHash(const vector<T> &ar) {
        if (!base_pow[1][0] || !base_pow[0][0]) init();
        int n = ar.size();
        assert(n < N);
        pref[0].resize(n + 3, 0), suf[0].resize(n + 3, 0);
        pref[1].resize(n + 3, 0), suf[1].resize(n + 3, 0);
        for (int i = 1; i <= n; i++) {
            pref[0][i] = MUL(pref[0][i - 1], base1) + ar[i - 1] + 997;
            if (pref[0][i] >= HashMod) pref[0][i] -= HashMod;
            pref[1][i] = MUL(pref[1][i - 1], base2) + ar[i - 1] + 997;
            if (pref[1][i] >= HashMod) pref[1][i] -= HashMod;
        }

        for (int i = n; i >= 1; i--) {
            suf[0][i] = MUL(suf[0][i + 1], base1) + ar[i - 1] + 997;
            if (suf[0][i] >= HashMod) suf[0][i] -= HashMod;
            suf[1][i] = MUL(suf[1][i + 1], base2) + ar[i - 1] + 997;
            if (suf[1][i] >= HashMod) suf[1][i] -= HashMod;
        }
    }

    explicit PolyHash(string str) : PolyHash(vector<char>(str.begin(), str.end())) {}

    pair<uint64_t, uint64_t> get_hash(int l, int r) {
        int64_t h = pref[0][r + 1] - MUL(base_pow[0][r - l + 1], pref[0][l]);
        uint64_t f = h < 0 ? h + HashMod : h;
        h = pref[1][r + 1] - MUL(base_pow[1][r - l + 1], pref[1][l]);
        uint64_t g = h < 0 ? h + HashMod : h;
        return make_pair(f, g);
    }

    pair<uint64_t, uint64_t> rev_hash(int l, int r) {
        int64_t h = suf[0][l + 1] - MUL(base_pow[0][r - l + 1], suf[0][r + 2]);
        uint64_t f = h < 0 ? h + HashMod : h;
        h = suf[1][l + 1] - MUL(base_pow[1][r - l + 1], suf[1][r + 2]);
        uint64_t k = h < 0 ? h + HashMod : h;
        return make_pair(f, k);
    }
};