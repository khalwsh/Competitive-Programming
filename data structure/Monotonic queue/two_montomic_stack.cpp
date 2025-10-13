/*
  MonoQueue / MonoStack — two-stack queue that keeps a precomputed aggregate
  per stack node so you can get the aggregate of the whole queue in O(1).
  Queue = [out (front)] ++ [in (back)]; get() = merge(out.get(), in.get()).
  Amortized O(1) push/pop/get (each element moved at most once).
  Requirements for merge: associative & closed (identity helpful); should be O(1).
  Examples: max, min, sum, bitwise OR/AND/XOR, string concat (order preserved).
*/

template <typename T> struct MonoStack {
    stack<pair<T, T>> st;
    function<T(T, T)> merge;

    MonoStack(function<T(T, T)> merge)
        : merge(merge) {}

    void push(T x) {
        T cur = st.empty() ? x : merge(x, st.top().second);
        st.push({x, cur});
    }

    void pop() { st.pop(); }

    size_t size() const { return st.size(); }

    bool empty() const { return st.empty(); }

    T top() const { return st.top().first; }

    T get() const { return st.top().second; }
};

template <typename T> struct MonoQueue {
    MonoStack<T> in, out;
    function<T(T, T)> merge;
    MonoQueue(function<T(T, T)> merge)
        : merge(merge), in(merge), out(merge) {}

    void push(T x) { in.push(x); }

    void moveInToOut() {
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }

    void pop() {
        if (out.empty())
            moveInToOut();
        out.pop();
    }

    T front() {
        if (out.empty())
            moveInToOut();
        return out.top();
    }

    size_t size() const { return in.size() + out.size(); }

    bool empty() const { return in.empty() && out.empty(); }

    T get() const {
        if (in.empty())
            return out.get();
        if (out.empty())
            return in.get();
        return merge(out.get(), in.get()); // preserve queue order
    }
};
