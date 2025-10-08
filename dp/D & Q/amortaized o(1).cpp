const int N = 10001;
int dp[N][2], it = 1, L = 1, R = 0, sum = 0;
char a[N];
int freq[26];
 
void addR(int i) {
    for (int j = a[i] - 'a' + 1; j < 26; ++j) {
        sum += freq[j];
    }
    freq[a[i] - 'a']++;
}
void addL(int i) {
    for (int j = a[i] - 'a' - 1; j >= 0; --j) {
        sum += freq[j];
    }
    freq[a[i] - 'a']++;
}
 
void remL(int i) {
    for (int j = a[i] - 'a' - 1; j >= 0; --j) {
        sum -= freq[j];
    }
    freq[a[i] - 'a']--;
}
 
void remR(int i) {
    for (int j = a[i] - 'a' + 1; j < 26; ++j) {
        sum -= freq[j];
    }
    freq[a[i] - 'a']--;
}
 
 
void move(int l, int r) {
    while(R < r) addR(++R);
    while(L > l) addL(--L);
    while(R > r) remR(R--);
    while(L < l) remL(L++);
}
 
void go(int l, int r, int lx, int rx) {
    if(l > r) return;
 
    int m = (l + r) / 2, opt = 1;
    for(int i = lx; i <= min(rx, m); ++i) {
        move(i, m);
        int curr = dp[i - 1][it ^ 1] + sum;
 
        if(curr < dp[m][it])
            dp[m][it] = curr, opt = i;
    }
 
    go(l, m - 1, lx, opt);
    go(m + 1, r, opt, rx);
}
 
void solve(int tc) {
    string s; cin >> s;
    int n = s.length(), k; cin >> k;
    for(int i = 1; i <= n; ++i) a[i] = s[i - 1];
 
    // base case
    memset(dp, 0x3f3f3f3f, sizeof dp);
    dp[0][0] = 0;
    it = 1;
 
    // calculate
    for(int i = 1; i <= k; ++i, it ^= 1)
        go(1, n, 1, n);
 
 
    cout << dp[n][k & 1];
}