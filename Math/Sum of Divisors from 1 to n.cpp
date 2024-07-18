__int128 sum(__int128 n){
   return n * ( n + 1 ) / 2;
}
__int128 S(__int128 n){
    __int128 res = 0;
    for(__int128 i=1;i*i<=n;i++){
        __int128 l = i, r = n/i;
        res = res + i*(r-l+1) + sum(r) - sum(l);
        res %= mod;
    }
    return res;
}
__int128 RangeSum(__int128 l,__int128 r){
    return add(S(r)  , - S(l-1) , mod);
}