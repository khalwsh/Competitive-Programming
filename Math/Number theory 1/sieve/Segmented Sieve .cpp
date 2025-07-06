vector<ll>Primes;
vector<bool> segmentedSieve(ll L, ll R) {
    int lim = (int)sqrt(R);
    vector<bool> mark(lim + 1, true);
    vector<int> primes;//have primes [2 , sqrt(R)]
    for (ll i = 2; i <= lim; ++i) {
        if (mark[i]) {
            primes.emplace_back(i);
            for (ll j = i * i; j <= lim; j += i)
                mark[j] = false;
        }
    }

    vector<bool> isPrime(R - L + 1, true);
    for (long long i : primes) {
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    }
    if (L == 1)
        isPrime[0] = false;
    for(int i = 0;i < R-L+1;i++){
        if(isPrime[i])Primes.emplace_back(i+L);
    }
    return isPrime;// the ith on the range prime or not   isPrime[i] represent L+i is prime or not
}