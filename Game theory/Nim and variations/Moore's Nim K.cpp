// we have N piles and we can remove stones from any k piles
// represent the piles in binary and the sum in every column should be
// divisable by (k + 1)
int MooreNimK(const vector<ll>&piles , int k) {
    vector<int>bits(64);
    for(auto &val:piles) {
        for(int j = 0;j < 63;j++) {
            if(val & (1LL<<j))bits[j]++;
        }
    }
    bool all = true;
    for(auto &val:bits) {
        all = all && ((val % (k + 1)) == 0);
    }
    return all ? 2 : 1;
}