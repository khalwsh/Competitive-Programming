int fact[N];
int inv[N]; 
int InvFact[N];
void init() {
    fact[0] = inv[1] = fact[1] = InvFact[0] = InvFact[1] = 1;
    for (long long i = 2; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = mod - (inv[mod % i] * (mod / i) % mod);
        InvFact[i] = (inv[i] * InvFact[i - 1]) % mod;
    }
}
int nCr(int n, int r) {
    if(r > n || n < 0 || r < 0) return 0;
    return (((fact[n] * InvFact[r]) % mod) * InvFact[n - r]) % mod;
}
int lucas(int n , int r){
    if(r == 0) return 1;
    int res = 1;
    while(r){
        res = 1LL * res * nCr(n % mod , r % mod) % mod;
        n /= mod; r/= mod;
    }
    return res;
}