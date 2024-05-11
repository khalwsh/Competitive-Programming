int inv[N] , FInv[N] , fact[N];
void Inverse() {
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}
void FactorialInverse() {
    FInv[0] = FInv[1] = 1;
    for (int i = 2; i < N; i++)
        FInv[i] = (inv[i] * FInv[i - 1]) % mod;
}
void factorial() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
}
int Ncr(int n, int r) {
    int ans = ((fact[n] * FInv[r])
               % mod * FInv[n - r])
              % mod;
    return ans;
}
void init() {
    Inverse();
    FactorialInverse();
    factorial();
}