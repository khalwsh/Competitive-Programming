#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}

struct Matrix {
    __int128 m[2][2];
};

Matrix mulMatrix(const Matrix &A, const Matrix &B, ll mod) {
    Matrix C = {{{0,0},{0,0}}};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++){
            __int128 sum = 0;
            for (int k = 0; k < 2; k++){
                sum += A.m[i][k] * B.m[k][j];
            }
            C.m[i][j] = (long long)(sum % mod);
        }
    return C;
}

Matrix powerMatrix(Matrix base, ll exp, ll mod) {
    Matrix res = {{{1,0},{0,1}}};
    while(exp > 0){
        if(exp & 1)
            res = mulMatrix(res, base, mod);
        base = mulMatrix(base, base, mod);
        exp >>= 1;
    }
    return res;
}

ll fib(ll n, ll mod) {
    if(n == 0) return 0;
    if(n == 1) return 1 % mod;
    Matrix Q = {{{1, 1}, {1, 0}}};
    Matrix Qn = powerMatrix(Q, n - 1, mod);
    return Qn.m[0][0] % mod; // F(n)
}

namespace PollardRho {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    constexpr int P = 1000009;
    ll seq[P];
    int primes[P], spf[P];

    inline ll add_mod(ll x, ll y, ll m) {
        x += y;
        return (x >= m ? x - m : x);
    }

    inline ll mul_mod(ll x, ll y, ll m) {
        return (__int128)x * y % m;
    }

    inline ll pow_mod(ll base, ll exp, ll mod) {
        ll res = 1 % mod;
        while(exp){
            if(exp & 1)
                res = mul_mod(res, base, mod);
            base = mul_mod(base, base, mod);
            exp >>= 1;
        }
        return res;
    }

    inline bool miller_rabin(ll n) {
        if(n <= 2 || (n % 2 == 0))
            return n == 2;
        if(n < P) return spf[n] == n;

        ll r = n - 1, s = 0;
        while ((r & 1LL) == 0) {
            r >>= 1;
            ++s;
        }

        for (int i = 0; primes[i] < n && primes[i] < 32; ++i) {
            ll x = pow_mod(primes[i], r, n);
            ll prev = x;
            for (int j = 0; j < s; ++j) {
                ll y = mul_mod(prev, prev, n);
                if (y == 1 && prev != 1 && prev != n - 1)
                    return false;
                prev = y;
            }
            if (prev != 1)
                return false;
        }
        return true;
    }

    void init() {
        int cnt = 0;
        for (int i = 2; i < P; i++) {
            if(!spf[i]){
                primes[cnt++] = spf[i] = i;
            }
            for (int j = 0, k; (k = i * primes[j]) < P; ++j) {
                spf[k] = primes[j];
                if(spf[i] == primes[j]) break;
            }
        }
    }

    ll pollard_rho(ll n) {
        while (true) {
            ll x = rng() % n, y = x, c = rng() % n;
            ll u = 1, v, t = 0;
            ll *px = seq, *py = seq;
            while (true) {
                *py++ = y = add_mod(mul_mod(y, y, n), c, n);
                *py++ = y = add_mod(mul_mod(y, y, n), c, n);
                x = *px++;
                if (x == y) break;
                v = u;
                u = mul_mod(u, (ll)abs(y - x), n);
                if (u == 0)
                    return __gcd(v, n);
                if (++t == 32) {
                    t = 0;
                    if ((u = __gcd(u, n)) > 1 && u < n)
                        return u;
                }
            }
            if(t && (u = __gcd(u, n)) > 1 && u < n)
                return u;
        }
    }

    vector<ll> factorize(ll n) {
        if(n == 1) return {};
        if(miller_rabin(n)) return {n};

        vector<ll> factors;
        while(n < P && n > 1) {
            factors.push_back(spf[n]);
            n /= spf[n];
        }

        if(n >= P){
            ll x = pollard_rho(n);
            auto left = factorize(x);
            auto right = factorize(n / x);
            factors.insert(factors.end(), left.begin(), left.end());
            factors.insert(factors.end(), right.begin(), right.end());
        }

        return factors;
    }
}


ll modExp(ll a, ll b, ll mod) {
    ll result = 1 % mod;
    while(b){
        if(b & 1)
            result = (__int128)result * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return result;
}

vector<ll> getDivisors(ll x) {
    auto factors = PollardRho::factorize(x);
    map<ll, int> mp;
    for (auto &val : factors)
        mp[val]++;
    vector<pair<ll, int>> all(mp.begin(), mp.end());

    function<void(int, ll, vector<ll>&)> backtrack = [&](int idx, ll current, vector<ll> &res) {
        if (idx == (int)all.size()) {
            res.push_back(current);
            return;
        }
        backtrack(idx + 1, current, res);
        ll prime = all[idx].first;
        ll cur = prime;
        for (int i = 0; i < all[idx].second; i++) {
            backtrack(idx + 1, current * cur, res);
            cur *= prime;
        }
    };

    vector<ll> divisors;
    backtrack(0, 1, divisors);
    return divisors;
}

ll get_period_prime(ll p) {
    ll candidate;
    if(modExp(5, (p - 1) / 2, p) == 1)
        candidate = p - 1;
    else
        candidate = 2 * (p + 1);

    vector<ll> divs = getDivisors(candidate);
    sort(divs.begin(), divs.end());
    for (ll d : divs) {
        if(fib(d, p) % p == 0 && fib(d + 1, p) % p == 1)
            return d;
    }
    return candidate;
}

ll get_period_prime_power(ll p, int e) {
    // Special handling for p = 2.
    if(p == 2) {
        if(e == 1) return 3;
        if(e == 2) return 6;
        return 3LL << (e - 1);
    }
    // Special handling for p = 5.
    if(p == 5) {
        ll pw = 1;
        for (int i = 0; i < e; i++) pw *= 5;
        return 4 * pw;
    }
    // Compute the period modulo prime p.
    ll period_p = get_period_prime(p);
    if(e == 1) return period_p;
    // Check if the period remains stable modulo p^2.
    if(fib(period_p, p * p) == 0 && fib(period_p + 1, p * p) == 1)
        return period_p;
    // Otherwise, it lifts by a factor of p^(e-1).
    ll factor = 1;
    for (int i = 1; i < e; i++) factor *= p;
    return period_p * factor;
}

ll lcm_ll(ll a, ll b) {
    return a / __gcd(a, b) * b;
}


int main(){
    PRE();
    PollardRho::init();
    int t;
    cin >> t;
    while(t--) {
        ll m;
        cin >> m;
        vector<ll> fac = PollardRho::factorize(m);
        map<ll, int> freq;
        for(auto &p : fac)
            freq[p]++;

        ll overall = 1;
        for(auto &pr : freq) {
            ll p = pr.first;
            int e = pr.second;
            ll period_pp = get_period_prime_power(p, e);
            overall = lcm_ll(overall, period_pp);
        }
        cout << overall << "\n";
    }
    return 0;
}
