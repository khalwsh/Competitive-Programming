int findK(vector<int> & v, int k){
    int n = v.size();
    int idx = randomLongLong(0, n - 1);
    int pivot = v[idx];
    vector<int> up, down;
    for (int i = 0; i < n; ++i) {
        if(i == idx) continue;
        if(v[i] > pivot) up.push_back(v[i]);
        else down.push_back(v[i]);
    }
    if(k == down.size() + 1){
        return pivot;
    }
    else if(k <= down.size()){
        return findK(down, k);
    }
    else{
        return findK(up, k - (down.size() + 1));
    }
}