int findK(vector<int> &v, int k){
    nth_element(v.begin(), v.begin() + k, v.end());
    return v[k];
}