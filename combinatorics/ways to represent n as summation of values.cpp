int sum(int n , int m = 0){
    if(!m)return (1LL << (n - 1));
    return fast_power(2ll , n - 1 , m);
}