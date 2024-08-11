string s;
vector<int>suf , group , NewGroup;
int curLen = 0;
bool comp(int i , int j) {
    return group[i] < group[j] || group[i] == group[j] && group[i + curLen] < group[j + curLen];
}
void build() {
    suf.clear();
    group.clear();
    NewGroup.clear();
    int n = (int)s.size();
    NewGroup.resize(n + 1);
    n++;
    for(int i = 0;i < n;i++) {
        suf.emplace_back(i);
        group.emplace_back(s[i]);
    }
    for(int len = 1;;len *= 2) {
        curLen = len;
        sort(suf.begin() , suf.end() , comp);
        for(int i = 1;i < n;i++) {
            NewGroup[i] = NewGroup[i - 1] + comp(suf[i - 1] , suf[i]);
        }
        for(int i = 0;i < n;i++) {
            group[suf[i]] = NewGroup[i];
        }
        if(NewGroup[n - 1] == n - 1)break;
    }
}