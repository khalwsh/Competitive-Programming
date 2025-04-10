//remember use safe mul at the fastpower function

bool check_composite(int n, int a, int d, int s) {
    int x = fast_power(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (int)SafeMul(x,x,n);
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(int n, int iter=100) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    int d = n - 1;
    while ((d & 1ll) == 0) {
        d >>= 1ll;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}