vector<pair<int,int>> all;
    for (int i = 0; i < n; i++){
        int cnt = K[i];
        int base = 1;
        while(cnt > 0){
            int num = min(base, cnt);
            all.emplace_back(W[i] * num, V[i] * num);
            cnt -= num;
            base *= 2;
        }
    }
 
    for (auto &val : all){
        int weight = val.first;
        int value = val.second;
        for (int j = w; j >= weight; j--){
            dp[j] = max(dp[j], dp[j - weight] + value);
        }
    }