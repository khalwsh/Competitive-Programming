// Monotonic deque for sliding-window minimum
struct DequeMin {
    deque<pair<int, ll>> dq;
    void push(int idx, ll val) {
        while (!dq.empty() && dq.back().second >= val)
            dq.pop_back();
        dq.emplace_back(idx, val);
    }
    ll getMin(int l) {
        while (!dq.empty() && dq.front().first < l)
            dq.pop_front();
        return dq.empty() ? POS_INF : dq.front().second;
    }
    void clear() { dq.clear(); }
};