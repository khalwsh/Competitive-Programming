int Nim(vector<ll>&piles) {
    ll res = 0;
    for(auto &val:piles)res ^= val;
    return res ? 1 : 2;
}
int NimSkip(vector<ll>&piles , int a , int b) {
    if(a > b)return 1;
    if(b > a)return 2;
    return Nim(piles);
}