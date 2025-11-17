const int N = 4001 , K = 801;
ll dp[N][K];
int n , k;
void dnc(int i , int L , int R , int opt_L , int opt_R) {
    if (L > R) return;
    int mid = L + (R - L) / 2;
    int best = opt_L;
    for (int j = opt_L; j < min(opt_R + 1 , mid); j++) {
        ll cost = c(j , mid);
        if (dp[j][i - 1] + cost < dp[mid][i]) {
            dp[mid][i] = dp[j][i - 1] + cost;
            best = j;
        }
    }
    dnc(i , L , mid - 1 , opt_L , best);
    dnc(i , mid + 1 , R , best , opt_R);
}