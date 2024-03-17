int sum(int n){
   return n * ( n + 1 ) / 2;
}
int S(int n){
    int res = 0;
    for(int i=1;i*i<=n;i++){
        int l = i, r = n/i;
        res += i*(r-l+1) + sum(r) - sum(l);
    }
    return res;
}
int RangeSum(int l,int r){
    return S(r) - S(l-1);
}