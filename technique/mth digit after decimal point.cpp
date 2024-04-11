int solve(int n,int m){
    //return the mth digit after the decimal point 
    if(n == 1){
        return 0;
    }
    return 10 * fast_power(10, m - 1,n) / n;
}
