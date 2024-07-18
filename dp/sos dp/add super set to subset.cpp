const int Bits = 20;
const int MaxN = 1<<Bits;
ll arr[MaxN] , v[MaxN] , dp[MaxN];
signed main() {
    khaled
    int n;cin>>n;
    for(int i = 0;i<n;i++) {
        int x;cin>>x;
        arr[x]++;
        v[i] = x;
    }
    for(int i = 0; i<(MaxN); ++i)
       dp[i] = arr[i];
    
    for(int i = 0;i < Bits;i++) {
        for(int j = MaxN - 1;j >= 0;j--) {
            if(j & (1<<i)) {
                dp[j ^ (1<<i)] += dp[j];
            }
        }
    }
    
}