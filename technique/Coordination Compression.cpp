vector<int>all;
int compress (int val) {
    return lower_bound(all.begin(),all.end(), val) - all.begin();
}
void pre(vector<int>&v){
    for(auto &val:v)all.emplace_back(val);
    sort(all.begin(),all.end());
    all.erase(unique(all.begin(),all.end()) ,all.end());
}