struct WindowFreq {
    map<int, int> freq;
    map<int, multiset<int>> fte;

    void add(int x) {
        int old = freq[x];
        if (old > 0) {
            auto it = fte.find(old);
            if (it != fte.end()) {
                auto mit = it->second.find(x);
                if (mit != it->second.end()) it->second.erase(mit);
                if (it->second.empty()) fte.erase(it);
            }
        }
        freq[x]++;
        fte[freq[x]].insert(x);
    }

    void remove(int x) {
        int old = freq[x];
        if (old == 0) return;

        auto it = fte.find(old);
        if (it != fte.end()) {
            auto mit = it->second.find(x);
            if (mit != it->second.end()) it->second.erase(mit);
            if (it->second.empty()) fte.erase(it);
        }

        freq[x]--;
        if (freq[x] == 0) {
            freq.erase(x);
            return;
        }
        fte[freq[x]].insert(x);
    }

    int getBest() const {
        if (fte.empty()) return -1;
        auto it = fte.rbegin();
        return *it->second.begin();
    }

    int uniqueCount() const {
        return (int)freq.size();
    }
};