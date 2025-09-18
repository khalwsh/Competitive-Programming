    vector<ll>v(n + 1);
    for (int i = 1;i <= n;i++) cin >> v[i];
    for (int i = 1;i <= n;i++) v[i] += v[i - 1];

    vector<ll>pref(n + 1);
    vector<ll>pref2(n + 1);
    for (int i = 1;i <= n;i++) {
        pref[i] = v[i] * (i + 1);
        pref2[i] = v[i] * i;
        if (i) pref[i] += pref[i - 1] , pref2[i] += pref2[i - 1];
    }
    for (int i = 1;i <= n;i++) v[i] += v[i - 1];

    while (q--) {
        ll res = pref[r] - pref[l - 1];
        res -= (v[r] - v[l - 1]) * l;
        ll temp = (v[r - 1] - (l - 2 == -1 ? 0 : v[l - 2])) * r;
        temp -= (pref2[r - 1] - (l - 2 == -1 ? 0 : pref2[l - 2]));
        cout << res - temp << '\n';
    }