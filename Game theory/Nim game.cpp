// nim game have k piles and you choose one pile then remove some stones
// the loser who couldn't choose
// if the xor != 0 I win so my move is to make his xor == 0
// you find number has MSB same as the total Xor then any number has this MSB you can reduce it
// to make xor == 0
int Nim(vector<ll>&piles) {
    ll res = 0;
    for(auto &val:piles)res ^= val;
    return res ? 1 : 2;
}