int grundy(int x) {
    if (x == 0) return 0;
    // remember to memo
    vector<int> v;
    // fill v with the grundy(nx) where nx is any next position you can go to
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int mex = 0;
    while (mex < v.size() && v[mex] == mex) ++mex;
    return mex;
}