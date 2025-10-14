// solution for Miser is same as Nim unless all piles are ones then the reverse of Nims
// so we do same strategy as Nim before we reach leaf node then we can make us win in the leaf nodes
int MiserNim(vector<ll>&piles) {
    ll res = 0;
    int ones = 0;
    for(auto &val:piles)res ^= val , ones += val == 1;
    if(ones == piles.size())res = res ? 0 : 1;
    return res ? 1 : 2;
}