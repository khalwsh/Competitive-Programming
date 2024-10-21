ll mex(const vector<ll>&a) {
    vector<ll>b = a;
    int n = a.size();
    for(int i = 0;i < n;i++) {
        while(b[i] >= 0 && b[i] < n && b[b[i]] != b[i]) {
            swap(b[i] , b[b[i]]);
        }
    }
    for(int i = 0;i < n;i++) {
        if(b[i] != i)return i;
    }
    return n;
}