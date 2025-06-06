template<class T = int>
struct Bit2D {
    vector<T> ord;
    vector<vector<T>> fw, coord;

    // pts needs all points that will be used in the upd
    // if range upds remember to build with {x1, y1}, {x1, y2 + 1}, {x2 + 1, y1}, {x2 + 1, y2 + 1}
    Bit2D(vector<pair<T, T>> pts) {
        sort(pts.begin(), pts.end());
        for (auto a : pts)
            if (ord.empty() || a.first != ord.back())
                ord.push_back(a.first);
        fw.resize(ord.size() + 1);
        coord.resize(fw.size());

        // Swap coordinates for building BIT structure for y-dimension updates
        for (auto& a : pts)
            swap(a.first, a.second);
        sort(pts.begin(), pts.end());
        for (auto& a : pts) {
            swap(a.first, a.second);
            for (int on = std::upper_bound(ord.begin(), ord.end(), a.first) - ord.begin(); on < fw.size(); on += on & -on)
                if (coord[on].empty() || coord[on].back() != a.second)
                    coord[on].push_back(a.second);
        }

        for (int i = 0; i < fw.size(); i++)
            fw[i].assign(coord[i].size() + 1, 0);
    }

    T merge(T a, T b) {
        return a + b;
    }

    // point update: adds value v at (x, y)
    void upd(T x, T y, T v) {
        for (int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx < fw.size(); xx += xx & -xx)
            for (int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy < fw[xx].size(); yy += yy & -yy)
                fw[xx][yy] = merge(fw[xx][yy], v);
    }

    // point query: returns sum from (0, 0) to (x, y)
    T qry(T x, T y) {
        T ans = 0;
        for (int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx > 0; xx -= xx & -xx)
            for (int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy > 0; yy -= yy & -yy)
                ans = merge(ans, fw[xx][yy]);
        return ans;
    }

    // range query: returns sum for rectangle defined by bottom-left (x1, y1) and top-right (x2, y2)
    T qry(T x1, T y1, T x2, T y2) {
        return qry(x2, y2) - qry(x2, y1 - 1) - qry(x1 - 1, y2) + qry(x1 - 1, y1 - 1);
    }

    // range update: adds v to each point in the rectangle defined by bottom-left (x1, y1) and top-right (x2, y2)
    void upd(T x1, T y1, T x2, T y2, T v) {
        upd(x1, y1, v);
        upd(x1, y2 + 1, -v);
        upd(x2 + 1, y1, -v);
        upd(x2 + 1, y2 + 1, v);
    }
};