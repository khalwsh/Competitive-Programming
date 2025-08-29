// Monotonic deque for sliding-window maximum
const ll NEG_INF = -1e18;
struct DequeMax {
    deque<pair<int, ll>> dq;
    void push(int idx, ll val) {
        while (!dq.empty() && dq.back().second <= val)
            dq.pop_back();
        dq.emplace_back(idx, val);
    }
    ll getMax(int l) {
        while (!dq.empty() && dq.front().first < l)
            dq.pop_front();
        return dq.empty() ? NEG_INF : dq.front().second;
    }
    void clear() { dq.clear(); }
};