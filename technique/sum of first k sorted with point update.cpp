const int N = 5e5 + 10;
int n , k , q;
multiset<ll> x , y;
ll a[N];
ll sum = 0;
void balance() {
    while (x.size() < k) {
        sum += *y.rbegin();
        x.insert(*y.rbegin());
        y.erase(y.find(*y.rbegin()));
    }
    if (x.empty() || y.empty()) return;
    while (1) {
        auto it = x.begin();
        auto iit = y.rbegin();
        if (*it >= *iit) return;
        ll v1 = *it , v2 = *iit;
        sum -= v1 , sum += v2;
        x.erase(it);
        y.erase(y.find(*y.rbegin()));
        x.insert(v2) , y.insert(v1);
    }
}
void erase(ll old) {
    auto it = x.find(old);
    if (it != x.end()) {
        sum -= old;
        x.erase(it);
    }else {
        y.erase(y.find(old));
    }
    balance();
}
void insert(ll nw) {
    y.insert(nw);
    balance();
}