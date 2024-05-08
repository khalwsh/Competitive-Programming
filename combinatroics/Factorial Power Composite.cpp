int cal (int n, int k) {
    int res = 0;
    //return largest x such that pow(k , x) | n!
    while (n) {
        n /= k;
        res += n;
    }
    return res;
}
int factorial_power(int n,int k) {
    int res = inf;
    for (int j = 2; j * j <= k; j++) {
        if (k % j == 0) {
            res = min(res, cal(n, j));
        }
        while(k % j == 0){
            k /= j;
        }
    }
    if(k != 1)res = min(res , cal(n , k));
    return res;
}