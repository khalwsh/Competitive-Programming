ll count(ll n){
    ll res = 0;
    for (int i = 0; i < 60; i++) {
        ll bit = 1LL << i;
        ll cycle = bit << 1LL;

        ll full = n / cycle;
        ll rem = n % cycle;

        res += full * bit;
        res += max(0LL, rem - bit + 1);
    }
    cout << res << '\n';
}
