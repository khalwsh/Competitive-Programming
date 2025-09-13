auto minPeriod = [&](int l, int r) -> array<int, M> {
        if ((l == r) || getHash(root, l, r - 1) == getHash(root, l + 1, r))
            return getHash(root, l, l);
        int len = (r - l + 1), ans = len;
        while (len > 1) {
            auto x = getHash(root, l, r - ans / lp[len]);
            auto y = getHash(root, l + ans / lp[len], r);
            if (x == y)
                ans /= lp[len];
            len /= lp[len];
        }
 
        return getHash(root, l, l + ans - 1);
    };