struct RollBackDsu {
    vector<int> parent, size;
    vector<array<int,5>> history;
    vector<int> opStack;
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
            opStack.push_back(0);
            return false;
        }
        if(size[a] > size[b])
            swap(a, b);
        history.push_back({a, parent[a], b, size[b], cnt});
        opStack.push_back(1);
        parent[a] = b;
        size[b] += size[a];
        cnt--;
        return true;
    }

    void rollback(int steps) {
        while(steps--) {
            int op = opStack.back();
            opStack.pop_back();
            if(op == 1) {
                auto act = history.back();
                history.pop_back();
                int a = act[0], oldParent = act[1], b = act[2], oldSize = act[3], oldCnt = act[4];
                parent[a] = oldParent;
                size[b] = oldSize;
                cnt = oldCnt;
            }
        }
    }
};