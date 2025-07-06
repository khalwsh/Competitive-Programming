using cd = complex<double>;
const double PI = acos(-1);
void FFT(vector<cd> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1 , 0);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    FFT(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    while (result.size() != a.size() + b.size() - 1) result.pop_back();
    return result;
}

string multiply_big_integers(string &a, string &b) {
    bool sign1 = (a[0] == '-');
    bool sign2 = (b[0] == '-');
    if (sign1) a.erase(a.begin());
    if (sign2) b.erase(b.begin());
    bool sign = sign1 ^ sign2;

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    vector<ll> aa(a.size()), bb(b.size());
    for (int i = 0; i < (int)a.size(); i++) aa[i] = a[i] - '0';
    for (int i = 0; i < (int)b.size(); i++) bb[i] = b[i] - '0';

    vector<ll> c = multiply(aa, bb);

    reverse(c.begin(), c.end());
    ll carry = 0;
    for (int i = (int)c.size() - 1; i >= 0; --i) {
        ll v = c[i] + carry;
        c[i] = v % 10;
        carry = v / 10;
    }
    while (carry > 0) {
        c.insert(c.begin(), carry % 10);
        carry /= 10;
    }

    int pos = 0;
    while (pos + 1 < (int)c.size() && c[pos] == 0)
        ++pos;

    string res;
    for (; pos < (int)c.size(); ++pos)
        res.push_back(char('0' + c[pos]));

    if (res == "0")
        return res;
    if (sign)
        res.insert(res.begin(), '-');
    return res;
}