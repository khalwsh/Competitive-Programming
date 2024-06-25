vector<int> zFunction(string s) {
    //it computes for every index i starts at i what is the largest string is matching a prefix
    int n = (int)s.size();
    vector<int> z(n);
    int left = 0, right = 0;
    for(int i = 1; i < n; i++) {
        if(i <= right) {
            z[i] = min(right - i + 1, z[i - left]);
        }
        while(i + z[i] < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if(i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}