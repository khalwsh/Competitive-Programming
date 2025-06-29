ll cnt(ll l,ll r,ll divisor,ll mod) {
    if (mod < 0 || mod >= divisor)
        return 0;
    ll remL = ((l % divisor) + divisor) % divisor;
    ll offset = (mod - remL + divisor) % divisor;
    ll first = l + offset;

    if (first > r)
        return 0;

    return 1 + (r - first) / divisor;
}