struct ordered__set {

    ordered_set<ll> se;

    void erase(ll val) {
        if (se.size() == 0 || *se.find_by_order(se.size() - 1) < val || *se.lower_bound(val - 1) != val) return;
        se.erase(se.lower_bound(--val));
    }

    int lw_bound(ll val) { // log --> return index ;
        if (se.size() == 0 || *se.find_by_order(se.size() - 1) < val) return -1;
        return se.order_of_key(*se.lower_bound(--val));
    }

    int up_bound(ll val) { return lw_bound(val + 1ll); }

    void insert(ll val) { se.insert(val); }

    ll operator[](int idx) { return *se.find_by_order(idx); }

    int size() { return se.size(); }

    void clr() { se.clear(); }
};
