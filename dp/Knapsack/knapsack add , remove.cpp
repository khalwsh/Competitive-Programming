    int q, k;
    dp[0] = 1;
    cin >> q >> k;
    while (q--) {
        char type;
        cin >> type;
        int x;
        cin >> x;
        if (type == '+') {
            // add
            for (int i = k; i >= x; i--) {
                dp[i] = add(dp[i], dp[i - x]);
            }
        } else {
            // remove
            for (int i = x; i <= k; i++) {
                dp[i] = add(dp[i], -dp[i - x]);
            }
        }
        cout << dp[k] << '\n';
    }