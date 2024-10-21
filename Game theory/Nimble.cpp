// you have n piles of stones in one move you can pick a coin and move it to any left square
// first one can't move lose
int Nimble(const vector<ll>&coins) {
    ll res = 0;
    for(int i = 0;i < coins.size();i++) {
        res ^= (coins[i] & 1) * i;
    }
    return res ? 1 : 2;
}