/// you should allow merging with dummy node (if you can't modify calc to skip merges with dummy)
static std::mt19937_64 RNG(
    (unsigned) chrono::steady_clock::now().time_since_epoch().count()
);
long long randomLongLong(long long l, long long r) {
    std::uniform_int_distribution<long long> dist(l, r);
    return dist(RNG);
}
struct Info {
    ll mx1 , mx0 , suf , pref , l , r, total;
    bool flip;
    Info(ll k = -1) {
        flip = false;
        if (k == -1) {
            total = 0;
            l = r = -1;
            pref = suf = 0;
            mx0 = mx1 = 0;
        } else {
            l = r = k;
            total = 1;
            pref = suf = 1;
            mx0 = (k == 0);
            mx1 = (k == 1);
        }
    }
};
struct Treap {
    ll val , priority , size;
    Treap *kids[2];
    Info info;
    Treap(int k = 0) {
        val = k;
        info = Info(k);
        size = 1;
        priority = randomLongLong(1 , 1e18);
        kids[0] = kids[1] = nullptr;
    }
    ~Treap() {
        delete kids[0];
        delete kids[1];
    }
};
Info merge_info(const Info& a, const Info& b) {
    // Merge 2 info
    return Info();
}
void prop(Treap* me) {
    if (me == nullptr) return;
    // write your lazy propagation
}
void recalc(Treap* me) {
    if (me == nullptr) return;
    me -> size = 1;
    Info lefti(-1);
    if (me->kids[0]) {
        prop(me->kids[0]);
        lefti = me->kids[0]->info;
        me -> size += me->kids[0] -> size;
    }
    Info righti(-1);
    if (me->kids[1]) {
        prop(me->kids[1]);
        righti = me->kids[1]->info;
        me -> size += me->kids[1] -> size;
    }
    Info midi(me -> val);
    me -> info = merge_info(merge_info(lefti , midi) , righti);
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
    if (left -> priority > right -> priority) {
        left -> kids[1] = Merge(left -> kids[1] , right);
        recalc(left);
        return left;
    }else {
        right -> kids[0] = Merge(left , right -> kids[0]);
        recalc(right);
        return right;
    }
}