struct Big {
    static const uint32_t BASE = 1000000000;
    vector<uint32_t> d;  // little‑endian limbs

    Big(uint64_t v = 0) { 
        if (v == 0) d.clear();
        else {
            while (v) {
                d.push_back(v % BASE);
                v /= BASE;
            }
        }
    }

    // remove leading zeros
    void trim() {
        while (!d.empty() && d.back() == 0) d.pop_back();
    }

    bool isZero() const { return d.empty(); }

    // multiply by small m (m fits in 32 bits)
    void mul(uint32_t m) {
        if (isZero() || m == 1) return;
        if (m == 0) { d.clear(); return; }
        uint64_t carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            uint64_t prod = uint64_t(d[i]) * m + carry;
            d[i] = uint32_t(prod % BASE);
            carry = prod / BASE;
        }
        while (carry) {
            d.push_back(uint32_t(carry % BASE));
            carry /= BASE;
        }
    }

    // add another Big
    void add(const Big &o) {
        size_t n = max(d.size(), o.d.size());
        d.resize(n, 0);
        uint64_t carry = 0;
        for (size_t i = 0; i < n; ++i) {
            uint64_t sum = uint64_t(d[i]) + (i < o.d.size() ? o.d[i] : 0) + carry;
            d[i] = uint32_t(sum % BASE);
            carry = sum / BASE;
        }
        if (carry) d.push_back(uint32_t(carry));
    }

    // output as decimal string
    string toString() const {
        if (isZero()) return "0";
        string s = to_string(d.back());
        char buf[16];
        for (int i = (int)d.size() - 2; i >= 0; --i) {
            // pad to 9 digits
            snprintf(buf, sizeof(buf), "%09u", d[i]);
            s += buf;
        }
        return s;
    }
};
