// adding subset to superset , dp 1 base
void forward1(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j] += dp[j ^ (1 << i)];
        }
    }
}
// adding superset to subset , dp 1 base
void forward2(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] += dp[j];
        }
    }
}
// undo subset to super set , dp 1 base
void backword1(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j] -= dp[j ^ (1 << i)];
        }
    }
}
// undo superset to subset
void backword2(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] -= dp[j];
        }
    }
}