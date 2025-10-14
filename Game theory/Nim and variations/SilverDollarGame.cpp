int SilverDollarGame (vector<ll>& locations) {
    // given N cells that has 1 coins in these positions you can move the coin to the left
    // as long as you not jumping over other coins , and no cell has more than 1 coin
    // locations = {2 , 5 , 7 , 11}
    // 1 2 3 4 5 6 7 8 9 10 11
    // 0 1 0 0 1 0 0 0 0 0 1
    if(locations.size() & 1)locations.insert(locations.begin() , 0);
    ll xoring = 0;
    for(int i = 0;i < locations.size();i+=2) {
        xoring ^= (locations[i + 1] - locations[i] - 1);
    }
    return xoring ? 1 : 2;
}