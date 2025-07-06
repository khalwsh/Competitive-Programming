struct Basis {
    static const int BITs = 60;
    ll basis[BITs + 1]{};
    vector<int> who[BITs + 1];
    int comp_sz = 0;

    void insert(ll msk, int idx) {
        vector<int> cur = { idx };
        for (int b = BITs; b >= 0; --b) {
            if (!(msk >> b & 1)) continue;
            if (!basis[b]) {
                basis[b] = msk;
                who[b] = cur;
                ++comp_sz;
                return;
            }
            msk ^= basis[b];
            vector<int> merged;
            merged.reserve(cur.size() + who[b].size());
            merged.insert(merged.end(), cur.begin(), cur.end());
            merged.insert(merged.end(), who[b].begin(), who[b].end());
            sort(merged.begin(), merged.end());
            cur.clear();
            for (int i = 0, j; i < (int)merged.size(); i = j) {
                j = i + 1;
                while (j < (int)merged.size() && merged[j] == merged[i]) ++j;
                if (((j - i) & 1) == 1) {
                    cur.push_back(merged[i]);
                }
            }
        }
    }
    vector<int> reconstruct(ll x) const {
        vector<int> answer;
        for (int b = BITs; b >= 0; --b) {
            if (!(x >> b & 1)) continue;
            if (!basis[b]) {
                return { -1 };
            }
            answer.insert(answer.end(), who[b].begin(), who[b].end());
            x ^= basis[b];
        }
        if (answer.empty()) return answer;
        sort(answer.begin(), answer.end());
        vector<int> result;
        for (int i = 0, j; i < (int)answer.size(); i = j) {
            j = i + 1;
            while (j < (int)answer.size() && answer[j] == answer[i]) ++j;
            if (((j - i) & 1) == 1) {
                result.push_back(answer[i]);
            }
        }
        return result;
    }
};