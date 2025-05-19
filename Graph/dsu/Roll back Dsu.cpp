struct RollBackDsu {
    vector<int> parent, size;
    vector<pair<int , int>> history;
    int cnt;

    RollBackDsu(int n) : cnt(n) {
        parent.resize(n);
        size.assign(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int a) {
        return (parent[a] == a ? a : find(parent[a]));
    }

    bool Merge(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) {
            history.emplace_back(-1 , -1);
            return false;
        }
        if(size[a] > size[b])
            swap(a, b);
        history.emplace_back(a , b);
        parent[a] = b;
        size[b] += size[a];
        cnt--;
        return true;
    }

    void rollback(int steps) {
        while(steps--) {
            auto [a , b] = history.back();
            history.pop_back();
            if (a == -1)continue;
            parent[a] = a;
            size[b] -= size[a];
            ++cnt;
        }
    }
};