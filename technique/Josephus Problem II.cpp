vector<int>solve(int n , int k){
    ordered_set<int>os;
    for(int i=0;i<n;i++)os.insert(i + 1);
    ll beg = k % os.size();
    vector<int>res;
    while(n--){
        res.emplace_back(*os.find_by_order(beg % os.size()));
        os.erase(os.find_by_order(beg % os.size()));
        beg+= k;
        if(n) beg %= os.size();
    }
    return res;
}