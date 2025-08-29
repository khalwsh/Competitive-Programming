// zero not handled
void fwht_xor(vector<ll> &a) {
    int n = (int)a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += (len << 1)) {
            for (int j = 0; j < len; ++j) {
                ll u = a[i + j];
                ll v = a[i + j + len];
                a[i + j] = u + v;
                a[i + j + len] = u - v;
            }
        }
    }
}

int next_pow2(int x) {
    int p = 1;
    while (p < x) p <<= 1;
    return p;
}

vector<int> distinct_pair_xors(const vector<int> &arr) {
    if (arr.size() < 2) return {};

    int maxv = 0;
    for (int v : arr) if (v > maxv) maxv = v;
    int M = next_pow2(maxv + 1);

    vector<ll> freq(M, 0);
    for (int v : arr) freq[v]++;

    bool hasDuplicate = false;
    for (int i = 0; i < M; ++i) if (freq[i] >= 2) { hasDuplicate = true; break; }

    vector<ll> A = freq;
    fwht_xor(A);
    for (int i = 0; i < M; ++i) A[i] = A[i] * A[i];
    fwht_xor(A);
    for (int i = 0; i < M; ++i) A[i] /= M;

    vector<int> res;
    res.reserve(M);
    for (int t = 0; t < M; ++t) {
        if (t == 0) {
            if (hasDuplicate) res.push_back(0);
        } else {
            if (A[t] > 0) res.push_back(t);
        }
    }
    return res;
}
