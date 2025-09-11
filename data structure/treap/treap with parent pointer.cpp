static std::mt19937_64 RNG(
    (unsigned) chrono::steady_clock::now().time_since_epoch().count()
);
long long randomLongLong(long long l, long long r) {
    std::uniform_int_distribution<long long> dist(l, r);
    return dist(RNG);
}
// init id every test , the nodes return from split make it leader of set
// if I have no parent I am parent of myself
int id = 1;
struct Treap {
    ll val , priority , size;
    Treap *kids[2];
    Treap *parent;
    ll Id;
    ll sum = 0;
    Treap(ll k = 0) {
        val = sum = k;
        size = 1;
        parent = this;
        Id = id++;
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
    me -> sum = me -> val;
    for (auto child : me->kids) if (child) me -> size += child -> size , me -> sum += child -> sum;
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

        if (p.first) p.first->parent = p.first;
        me->parent = me;
        return {p.first, me};
    } else {
        auto p = split(me->kids[1], toLeft - Size(me->kids[0]) - 1);
        me->kids[1] = p.first;
        if (me->kids[1]) me->kids[1]->parent = me;
        recalc(me);

        if (p.second) p.second->parent = p.second;
        me->parent = me;
        return {me, p.second};
    }
}

Treap* Merge(Treap* left, Treap* right) {
    if (left == nullptr) {
        if (right) right->parent = right;
        return right;
    }
    if (right == nullptr) {
        left->parent = left;
        return left;
    }

    if (left->priority < right->priority) {
        left->kids[1] = Merge(left->kids[1], right);
        if (left->kids[1]) left->kids[1]->parent = left;
        recalc(left);
        left->parent = left;
        return left;
    } else {
        right->kids[0] = Merge(left, right->kids[0]);
        if (right->kids[0]) right->kids[0]->parent = right;
        recalc(right);
        right->parent = right;
        return right;
    }
}
Treap* get_parent(Treap* me) {
    if (me == nullptr) return nullptr;
    while (true) {
        assert(me -> parent);
        if (me -> parent -> Id == me -> Id) return me;
        me = me -> parent;
    }
}
int pos(Treap* cur) {
    if (cur == nullptr) return -1;
    ll s = Size(cur -> kids[0]);
    while (cur -> parent != cur) {
        if (cur -> parent -> kids[1] && cur -> parent -> kids[1] -> priority == cur -> priority) {
            // I am right child
            s += 1 + Size(cur -> parent -> kids[0]);
        }
        cur = cur -> parent;
    }
    return s;
}