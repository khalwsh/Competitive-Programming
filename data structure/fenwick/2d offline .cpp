// n is the limit of first dimension can't equal or greater
template <typename T>
struct OfflineBIT2D {
    int n;
    vector<vector<int>> vals;
    vector<vector<T>> bit;

    int ind(const vector<int> &v, int x) {
        return upper_bound(begin(v), end(v), x) - begin(v) - 1;
    }

    OfflineBIT2D(): n(0) {}
    // n is the limit of the first dimension
    OfflineBIT2D(int n, vector<array<int, 2>> &todo) : n(n), vals(n + 1), bit(n + 1) {
        sort(begin(todo), end(todo), [](auto &a, auto &b) { return a[1] < b[1]; });

        for (int i = 1; i <= n; i++) vals[i].push_back(0);
        for (auto [r, c] : todo) {
            r++, c++;
            for (; r <= n; r += r & -r)
                if (vals[r].back() != c) vals[r].push_back(c);
        }
        for (int i = 1; i <= n; i++) bit[i].resize(vals[i].size());
    }

    void add(int r, int c, T val) {
        r++, c++;
        for (; r <= n; r += r & -r) {
            int i = ind(vals[r], c);
            for (; i < bit[r].size(); i += i & -i) bit[r][i] += val;
        }
    }

    T rect_sum(int r, int c) {
        r++, c++;
        T sum = 0;
        for (; r > 0; r -= r & -r) {
            int i = ind(vals[r], c);
            for (; i > 0; i -= i & -i) sum += bit[r][i];
        }
        return sum;
    }

    T rect_sum(int r1, int c1, int r2, int c2) {
        return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - rect_sum(r1 - 1, c2) +
               rect_sum(r1 - 1, c1 - 1);
    }
};