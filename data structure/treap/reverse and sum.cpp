static std::mt19937_64 RNG(
    (unsigned) chrono::steady_clock::now().time_since_epoch().count()
);
long long randomLongLong(long long l, long long r) {
    std::uniform_int_distribution<long long> dist(l, r);
    return dist(RNG);
}
struct Treap {
    ll priority , size;
    ll val;
    bool rev;
    ll sum = 0;
    Treap *kids[2];
    Treap(ll k = 0) {
        sum = val = k;
        size = 1;
        rev = false;
        priority = randomLongLong(1 , 1e18);
        kids[0] = kids[1] = nullptr;
    }
    ~Treap() {
        delete kids[0];
        delete kids[1];
    }
};
void prop(Treap* me) {
    if (!me) return;
    if (me -> rev) {
        swap(me -> kids[0] , me -> kids[1]);
        me -> rev ^= true;
        for (auto &child : me -> kids) if (child) child -> rev ^= true;
    }
}
void recalc(Treap* me) {
    if (me == nullptr) return;
    me -> size = 1;
    me -> sum = me -> val;
    for (auto child : me->kids) if (child) me -> size += child -> size , me -> sum += child -> sum;
}
ll Size(Treap *me) {
    if (me == nullptr) return  0;
    return me->size;
}
 
pair<Treap* , Treap*> split(Treap* me , int toLeft) {
    if (me == nullptr) return {nullptr , nullptr};
    prop(me);
    if (Size(me -> kids[0]) >= toLeft) {
        auto p = split(me -> kids[0] , toLeft);
        me -> kids[0] = p.second;
        recalc(me);
        return {p.first , me};
    }else {
        auto p = split(me -> kids[1] , toLeft - Size(me -> kids[0]) - 1);
        me -> kids[1] = p.first;
        recalc(me);
        return {me , p.second};
    }
}
 
Treap* Merge(Treap* left , Treap* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    prop(left);
    prop(right);
    if (left -> priority < right -> priority) {
        left -> kids[1] = Merge(left -> kids[1] , right);
        recalc(left);
        return left;
    }else {
        right -> kids[0] = Merge(left , right -> kids[0]);
        recalc(right);
        return right;
    }
}
