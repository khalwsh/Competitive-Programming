// count number of strings of length n containing s as substring
const int mod = 998244353;
 
vector<int> PI(string& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; ++i, j = pi[i - 1]) {
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) pi[i] = j + 1;
    }
    return pi;
}
 
auto computeAutometa(string &s) {
    s += '#';
    int n = s.size();
    vector<int> pi = PI(s);
 
    auto nxt = vector(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i]) nxt[i][c] = nxt[pi[i-1]][c];
            else nxt[i][c] = i + ('a' + c == s[i]);
        }
    }
 
    return nxt;
}
 
using Row = vector<int>;
using Matrix = vector<Row>;
 
Matrix mul(Matrix &a, Matrix &b) {
    int n = a.size(), m = a[0].size(), k = b[0].size();
    Matrix res(n, Row(k));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < k; ++j)
            for(int o = 0; o < m; ++o) {
                res[i][j] += 1ll * a[i][o] * b[o][j] % mod;
                if(res[i][j] >= mod) res[i][j] -= mod;
            }
    return res;
}
 
Matrix power(Matrix a, ll b) {
    int n = a.size();
    Matrix res(n, Row(n));
    for(int i = 0; i < n; ++i) res[i][i] = 1;
 
    while(b) {
        if(b & 1) res = mul(res, a);
        a = mul(a, a), b >>= 1;
    }
 
    return res;
}

void magic() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
 
    Matrix T(m + 1, Row(m + 1));
    auto nxt = computeAutometa(s);
 
    for (int i = 0; i < m; ++i)
        for (int c = 0; c < 26; ++c) T[i][nxt[i][c]]++;
 
    T[m][m] = 26;
 
    T = power(T, n);
    cout << T[0][m] << endl;
}
