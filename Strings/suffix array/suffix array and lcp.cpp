int n;
string s;
vector<int> suf, group, NewGroup, tempSuf;
int curLen = 0;

void countingSort(int maxGroup) {
    vector<int> count(maxGroup + 1, 0);
    tempSuf.resize(n);

    for (int i = 0; i < n; i++) {
        count[group[min(n - 1, suf[i] + curLen)]]++;
    }
    for (int i = 1; i <= maxGroup; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        tempSuf[--count[group[min(n - 1, suf[i] + curLen)]]] = suf[i];
    }
    for (int i = 0; i < n; i++) {
        suf[i] = tempSuf[i];
    }
}

void radixSort() {
    int maxGroup = max(n, 256);  // Initial max group value for radix sort

    // Sort by the second key (group[i + curLen])
    countingSort(maxGroup);

    // Sort by the first key (group[i])
    curLen = 0;
    countingSort(maxGroup);
}

void build() {
    suf.clear();
    group.clear();
    NewGroup.clear();
    n = (int)s.size();
    NewGroup.resize(n + 1);
    n++;
    for (int i = 0; i < n; i++) {
        suf.emplace_back(i);
        group.emplace_back(s[i]);
    }
    for (int len = 1;; len *= 2) {
        curLen = len;
        radixSort();
        for (int i = 1; i < n; i++) {
            NewGroup[i] = NewGroup[i - 1] + (group[suf[i - 1]] != group[suf[i]] || group[suf[i - 1] + len] != group[suf[i] + len]);
        }
        for (int i = 0; i < n; i++) {
            group[suf[i]] = NewGroup[i];
        }
        if (NewGroup[n - 1] == n - 1) break;
    }
}
vector<int>lcp;
void BuildLcp() {
    lcp.resize(n);
    int k = 0;
    for (int i = 0; i < n - 1; i++) {
        int pi = group[i] - 1; // Corrected index for accessing the previous suffix
        int j = suf[pi];
        while (s[j + k] == s[i + k]) k++;
        lcp[pi] = k; // Store the LCP value at the correct index
        if (k > 0) k--;
    }

}