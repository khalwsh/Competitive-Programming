int Nim(vector<ll>&piles) {
    ll res = 0;
    for(auto &val:piles)res ^= val;
    return res ? 1 : 2;
}
int StairCase(vector<ll>&piles) {
    vector<ll>all;
    for(int i = 1;i < piles.size();i+=2) {
        all.emplace_back(piles[i]);
    }
    return Nim(all);
}