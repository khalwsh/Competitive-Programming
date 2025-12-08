ll floorSum(ll a, ll b, ll c, ll n) {
    
    // calculate sum of (a * i + b) / c for (0 <= i <= n - 1)
    if (n <= 0) return 0;
    
    ll result = n * (n - 1) / 2 * (a / c) + n * (b / c);
    
    a %= c;
    b %= c;
    
    ll m = (a * n + b) / c;
    
    if (m == 0) return result;
    
    return result + floorSum(c, (a * n + b) % c, a, m);
}