const int N = 8001 , K = 801;
ll dp[2][N]; // remember base case
ll a[N];
int n , k;
void dnc(int i , int L , int R , int opt_L , int opt_R) {
    if (L > R) return;
    int mid = L + (R - L) / 2;
    int best = opt_L;
    auto c = [&](int l , int r) -> ll {
        // cost function
    };
    for (int j = opt_L; j < min(opt_R + 1 , mid); j++) {
        ll cost = c(j + 1 , mid);
        if (dp[i - 1][j] + cost < dp[i][mid]) {
            dp[i][mid] = dp[i - 1][j] + cost;
            best = j;
        }
    }
    dnc(i , L , mid - 1 , opt_L , best);
    dnc(i , mid + 1 , R , best , opt_R);
}