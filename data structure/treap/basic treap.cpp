long long randomLongLong(long long l, long long r) {
    random_device rd;
    mt19937_64 rng(rd());
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}
struct Treap {
    ll val , priority , size;
    Treap *kids[2];
    Treap(int k = 0) {
        val = k;
        size = 1;
        priority = randomLongLong(1 , 1e18);
        kids[0] = kids[1] = nullptr;
    }
};
void recalc(Treap* me) {
    if (me == nullptr) return;
    me -> size = 1;
    for (auto child : me->kids) if (child) me -> size += child -> size;
}
ll Size(Treap *me) {
    if (me == nullptr) return  0;
    return me->size;
}

pair<Treap* , Treap*> split(Treap* me , int toLeft) {
    if (me == nullptr) return {nullptr , nullptr};
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