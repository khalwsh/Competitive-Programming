
using int64 = long long;
using i128 = __int128_t;

int64 mul_mod(int64 a, int64 b, int64 mod) {
    return (int64) ((i128) a * b % mod);
}

int64 pow_mod(int64 a, int64 e, int64 mod) {
    int64 r = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return r;
}

int64 extgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return llabs(a);
    }
    int64 x1, y1;
    int64 g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int64 inv_mod(int64 a, int64 m) {
    int64 x, y;
    int64 g = extgcd(a, m, x, y);
    if (g != 1) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

int64 count_p_in_fact(int64 n, int64 p) {
    int64 cnt = 0;
    while (n) {
        n /= p;
        cnt += n;
    }
    return cnt;
}

int64 block_prod_without_p(int64 p, int64 pe) {
    int64 prod = 1;
    for (int64 i = 1; i <= pe; ++i) {
        if (i % p != 0) prod = mul_mod(prod, i, pe);
    }
    return prod;
}

int64 fact_without_p_mod_pe(int64 n, int64 p, int64 pe, int64 block_prod) {
    if (n == 0) return 1 % pe;
    int64 res = pow_mod(block_prod, n / pe, pe);
    int64 rem = n % pe;
    for (int64 i = 1; i <= rem; ++i)
        if (i % p != 0) res = mul_mod(res, i, pe);
    res = mul_mod(res, fact_without_p_mod_pe(n / p, p, pe, block_prod), pe);
    return res;
}

int64 nCr_mod_prime_power(int64 n, int64 r, int64 p, int64 q) {
    if (r < 0 || r > n) return 0;
    int64 pe = 1;
    for (int i = 0; i < q; ++i) pe *= p; 
    int64 exp_p = count_p_in_fact(n, p) - count_p_in_fact(r, p) - count_p_in_fact(n - r, p);
    if (exp_p >= q) return 0;

    int64 block = block_prod_without_p(p, pe);
    int64 a = fact_without_p_mod_pe(n, p, pe, block);
    int64 b = fact_without_p_mod_pe(r, p, pe, block);
    int64 c = fact_without_p_mod_pe(n - r, p, pe, block);

    int64 denom = mul_mod(b, c, pe);
    int64 inv_denom = inv_mod(denom, pe);
    if (inv_denom == -1) {
        return 0;
    }
    int64 res = mul_mod(a, inv_denom, pe);
    res = mul_mod(res, pow_mod(p, exp_p, pe), pe);
    return res % pe;
}

vector<pair<int64, int> > factorize(int64 M) {
    vector<pair<int64, int> > fac;
    int64 m = M;
    for (int64 p = 2; p * p <= m; ++p) {
        if (m % p == 0) {
            int e = 0;
            while (m % p == 0) {
                m /= p;
                ++e;
            }
            fac.push_back({p, e});
        }
    }
    if (m > 1) fac.push_back({m, 1});
    return fac;
}

pair<int64, int64> crt_pair(int64 a1, int64 m1, int64 a2, int64 m2) {
    int64 diff = (a2 - a1) % m2;
    if (diff < 0) diff += m2;
    int64 inv = inv_mod(m1 % m2, m2);
    int64 t = mul_mod(diff, inv, m2);
    int64 x = a1 + (i128) m1 * t;
    int64 mod = m1 * m2;
    x %= mod;
    if (x < 0) x += mod;
    return {x, mod};
}

int64 nCr_mod(int64 n, int64 r, int64 M) {
    if (r < 0 || r > n) return 0;
    if (M == 1) return 0;
    auto fac = factorize(M);
    vector<pair<int64, int64> > residues;
    for (auto &pe: fac) {
        int64 p = pe.first;
        int q = pe.second;
        int64 modulus = 1;
        for (int i = 0; i < q; ++i) modulus *= p;
        int64 ai = nCr_mod_prime_power(n, r, p, q);
        residues.push_back({ai, modulus});
    }
    int64 x = residues[0].first;
    int64 mod = residues[0].second;
    for (size_t i = 1; i < residues.size(); ++i) {
        auto pr = crt_pair(x, mod, residues[i].first, residues[i].second);
        x = pr.first;
        mod = pr.second;
    }
    return x % M;
}