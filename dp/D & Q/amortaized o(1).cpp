auto add = [&](int x , bool is_front) {
        if (!is_front) {
        }else {
        }
    };
    auto remove = [&](int x , bool is_front) {
        if (!is_front) {
        }else {
        }
    };
    int cur_l = 0, cur_r = -1;
    auto C = [&](int l, int r) {
        while (cur_l > l) add(a[--cur_l] , 1);
        while (cur_r < r) add(a[++cur_r] , 0);
        while (cur_l < l) remove(a[cur_l++] , 1);
        while (cur_r > r) remove(a[cur_r--] , 0);
        // return inv;
    };

    vector<ll> dp(n , 1e18), ndp(n , 1e18);
    for (int i = 0; i < n; i++) dp[i] = C(0, i);
    function<void(int, int, int, int)> go = [&](int l, int r, ll optl, ll optr) {
        if (l > r) return;
        ll mid = (l + r) / 2, opt = optl, mx = 1e18;
        for (ll i = optl; i <= min(mid, optr); i++) {
            ll cur = (i ? dp[i - 1] : 0) + C(i, mid);
            // maximize / minimize
            if (cur < mx) mx = cur, opt = i;
        }
        ndp[mid] = mx;
        go(l, mid - 1, optl, opt);
        go(mid + 1, r, opt, optr);
    };
    for (int i = 0; i < k - 1; i++) {
        go(0, n - 1, 0, n - 1);
        swap(dp, ndp);
    }