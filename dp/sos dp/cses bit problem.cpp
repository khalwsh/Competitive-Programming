const int Bits = 20;
const int MaxN = 1<<Bits;
ll dp1[MaxN] , arr[MaxN] , v[MaxN] , dp2[MaxN];
signed main() {
    khaled
    // cout<<log2_floor(3)<<line;
    int n;cin>>n;
    for(int i = 0;i<n;i++) {
        int x;cin>>x;
        arr[x]++;
        v[i] = x;
    }
    for(int i = 0; i<(MaxN); ++i)
        dp1[i] = arr[i] , dp2[i] = arr[i];
    for(int i = 0;i < Bits;i++) {
        for(int j = 0;j<MaxN;j++) {
            if(j & (1<<i)) {
                dp1[j] += dp1[j ^ (1<<i)];
            }
        }
    }
    for(int i = 0;i < Bits;i++) {
        for(int j = MaxN - 1;j >= 0;j--) {
            if(j & (1<<i)) {
                dp2[j ^ (1<<i)] += dp2[j];
            }
        }
    }
    for(int i = 0;i<n;i++) {
        cout<<dp1[v[i]]<<" "<<dp2[v[i]]<<" "<<n - dp1[(MaxN - 1) ^ v[i]]<<line;
	//#of y: x|y = x  ... #of  y: x & y = x ... #y: x & y != 0
    }
}