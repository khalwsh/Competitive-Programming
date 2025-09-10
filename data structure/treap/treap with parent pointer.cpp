long long randomLongLong(long long l, long long r) {
    random_device rd;
    mt19937_64 rng(rd());
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}
struct Treap {
    ll val , priority , size;
    Treap *kids[2];
    Treap *parent;
    Treap(int k = 0) {
        val = k;
        size = 1;
        parent = this;
        priority = randomLongLong(1 , 1e18);
        kids[0] = kids[1] = nullptr;
    }
    ~Treap() {
        delete kids[0];
        delete kids[1];
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
pair<Treap*, Treap*> split(Treap* me, int toLeft) {
    if (me == nullptr) return {nullptr, nullptr};

    if (Size(me->kids[0]) >= toLeft) {
        auto p = split(me->kids[0], toLeft);
        me->kids[0] = p.second;
        if (me->kids[0]) me->kids[0]->parent = me;
        recalc(me);

        if (p.first) p.first->parent = nullptr; 
        me->parent = nullptr;                   
        return {p.first, me};
    } else {
        auto p = split(me->kids[1], toLeft - Size(me->kids[0]) - 1);
        me->kids[1] = p.first;
        if (me->kids[1]) me->kids[1]->parent = me;
        recalc(me);

        if (p.second) p.second->parent = nullptr; 
        me->parent = nullptr;                    
        return {me, p.second};
    }
}

Treap* Merge(Treap* left, Treap* right) {
    if (left == nullptr) {
        if (right) right->parent = nullptr;
        return right;
    }
    if (right == nullptr) {
        left->parent = nullptr;
        return left;
    }

    if (left->priority < right->priority) {
        left->kids[1] = Merge(left->kids[1], right);
        if (left->kids[1]) left->kids[1]->parent = left;
        recalc(left);
        left->parent = nullptr; 
        return left;
    } else {
        right->kids[0] = Merge(left, right->kids[0]);
        if (right->kids[0]) right->kids[0]->parent = right;
        recalc(right);
        right->parent = nullptr;
        return right;
    }
}