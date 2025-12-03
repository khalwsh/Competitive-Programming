/*
 Count distinct subsequences by length.
 Input: s
 Returns: vector<int> dp of size n+1, where dp[k] = #distinct subsequences of length k (mod MOD).
 Complexity: O(n^2) time, O( alphabet_size * n ) extra memory (here alphabet_size = 256).
*/
const int mod = 1000000007;
vector<int> solve(const string &s) {
    int n = (int)s.size();
    vector<int> F(n + 1, 0), newF(n + 1, 0);
    F[0] = 1;
    vector<vector<int>> last(256, vector<int>(n + 1, 0));
    for (int c = 0; c < 256; ++c) last[c][0] = 0;
    for (int i = 1; i <= n; ++i) {
        char ch = s[i - 1];
        newF[0] = 1;
        for (int k = 1; k <= i; ++k) {
            ll val = F[k];  
            val += F[k - 1];  
            val -= last[ch][k - 1];
            val %= mod;
            if (val < 0) val += mod;
            newF[k] = val;
        }
        last[ch] = F;
        swap(F, newF);
    }
    return F; 
}