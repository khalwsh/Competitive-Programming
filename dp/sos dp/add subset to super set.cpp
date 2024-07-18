const int Bits = 20;
const int MaxN = 1<<Bits;
ll dp[MaxN] , arr[MaxN] , v[MaxN];
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
        for(int j = 0;j<MaxN;j++) {
            if(j & (1<<i)) {
                dp[j] += dp[j ^ (1<<i)];
            }
        }
    }
    for(int i = 0;i<n;i++) {
        cout<<dp[v[i]]<<line;
    }