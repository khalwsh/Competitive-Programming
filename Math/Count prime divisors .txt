int CountPrimeDivisors(int n,int val){
    int res=0;
    while(n>=val){
        res+=n/val;
        n/=val;
    }
    return res;
}