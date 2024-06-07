// many collision ? make 2 hashes with different base and to make s[i] == s[j]
// then hash1(s[i]) should equal hash1(s[j]) also hash2
const uint64_t HashMod = (1ULL << 61) - 1;
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (HashMod / 3) + (HashMod / 3);
uint64_t base_pow[N];

int64_t MUL(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & HashMod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & HashMod) + (ret >> 61);
    ret = (ret & HashMod) + (ret >> 61);
    return (int64_t) ret - 1;
}

void init() {
    base_pow[0] = 1;
    for (int i = 1; i < N; i++) {
        base_pow[i] = MUL(base_pow[i - 1], base);
    }
}
struct PolyHash {
    /// Remove suf vector and usage if reverse hash is not required for more speed
    vector<int64_t> pref, suf;

        template<typename T>
    PolyHash(const vector<T> &ar) {
        if (!base_pow[0]) init();

        int n = ar.size();
        assert(n < N);
        pref.resize(n + 3, 0), suf.resize(n + 3, 0);

        for (int i = 1; i <= n; i++) {
            pref[i] = MUL(pref[i - 1], base) + ar[i - 1] + 997;
            if (pref[i] >= HashMod) pref[i] -= HashMod;
        }

        for (int i = n; i >= 1; i--) {
            suf[i] = MUL(suf[i + 1], base) + ar[i - 1] + 997;
            if (suf[i] >= HashMod) suf[i] -= HashMod;
        }
    }

    explicit PolyHash(string str) : PolyHash(vector<char>(str.begin(), str.end())) {}

    uint64_t get_hash(int l, int r) {
        int64_t h = pref[r + 1] - MUL(base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + HashMod : h;
    }

    uint64_t rev_hash(int l, int r) {
        int64_t h = suf[l + 1] - MUL(base_pow[r - l + 1], suf[r + 2]);
        return h < 0 ? h + HashMod : h;
    }
};