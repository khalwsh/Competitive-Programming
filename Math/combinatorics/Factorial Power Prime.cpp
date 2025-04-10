int factorial_power (int n, int k) {
    int res = 0;
    //return largest x such that pow(k , x) | n!
    while (n) {
        n /= k;
        res += n;
    }
    return res;
}