static inline ll floor_div(ll x, ll y) {
    if (y <= 0) throw;
    if (x >= 0) return x / y;
    // for negative x: floor(x/y) = - ((-x + y - 1) / y)
    return - ( ( -x + y - 1 ) / y );
}

// sum_{i=0..n-1} floor((a*i + b) / c)
ll floorSum(ll a, ll b, ll c, ll n) {
    if (n <= 0) return 0;
    ll qa = floor_div(a, c);
    ll qb = floor_div(b, c);
    ll res = qa * (n * (n - 1) / 2) + qb * n;

    a -= qa * c;
    b -= qb * c;

    if (a < 0) a += c;
    if (b < 0) b += c;

    ll m = (a * n + b) / c;
    if (m == 0) return res;

    ll new_b = (a * n + b) % c;
    return res + floorSum(c, new_b, a, m);
}