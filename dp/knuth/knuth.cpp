int n; cin >> n;
    vector<vector<ll>> dp(n , vector<ll>(n));
    vector<vector<int>> opt(n , vector<int>(n));
    auto C = [&](int i, int j)-> ll {
        // Implement cost function C.
    };
    for (int i = 0; i < n; i++) {
        opt[i][i] = i;
        // Initialize dp[i][i] according to the problem
    }
    for (int i = n-2; i >= 0; i--) {
        for (int j = i+1; j < n; j++) {
            ll mn = 1e18;
            ll cost = C(i, j);
            for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k+1][j] + cost; 
                }
            }
            dp[i][j] = mn; 
        }
    }
    cout << dp[0][n - 1];