int getRandomNumber(int l, int r) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(l, r);
    return dis(gen);
}
ll powers[N] , inv[N];
int base = 0;
ll extended_euclidean(ll a,ll b,ll &x,ll &y)
{
    if(a<0)
    {
        ll r= extended_euclidean(-a,b,x,y);
        x*=-1;
        return r;
    }
    if(b<0)
    {
        ll r= extended_euclidean(a,-b,x,y);
        y*=-1;
        return r;
    }
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    ll sol= extended_euclidean(b,a%b,y,x);
    y-=(a/b)*x;
    return sol;
}
struct Hashing {
    vector<ll>prefix;
    template<class T>
    Hashing(T container , int inital) {
        if(base == 0) {
            base = getRandomNumber(45 , 1e9 + 7);
            powers[0] = 1;
            for(int i = 1;i < N; i++) {
                powers[i] = 1LL * powers[i - 1] * base;
                if(powers[i] >= mod)powers[i] %= mod;
            }
            int v = 1;
            for (int i = 0; i != N; ++i) {
                inv[i] = v;
                v = static_cast<long long>(v) * powers[i] % mod;
            }
            ll x, y;
            extended_euclidean(v, mod, x, y);
            x = (x % mod + mod) % mod;
            for (int i = N - 1; i >= 0; --i) {
                inv[i] = static_cast<long long>(x) * inv[i] % mod;
                x = static_cast<long long>(x) * powers[i] % mod;
            }
        }
        prefix.resize(container.size());
        for(int i = 0; i < container.size();i++) {
            prefix[i] = powers[i] * (container[i] - inital);
            if(i)prefix[i] += prefix[i - 1];
            if(prefix[i] >= mod)prefix[i] %= mod;
        }
    }
    ll query(int l , int r) {
        ll res = prefix[r];
        if(l)res -= prefix[l - 1];
        if(res < 0)res += mod;
        res = mul(res , inv[l], mod);
        return res;
    }
};