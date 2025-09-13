static std::mt19937_64 RNG(
    (unsigned) chrono::steady_clock::now().time_since_epoch().count()
);
long long randomLongLong(long long l, long long r) {
    std::uniform_int_distribution<long long> dist(l, r);
    return dist(RNG);
}

const int N = 3e5 + 10;
const int mod = 1e9 + 21;
const int base = 97;
ll pw[N]; // remember to init it , and make double hashing
struct Treap {
    ll hash , rev_hash , priority , size;
    char val;
    Treap *kids[2];
    Treap(char k = 0) {
        val = k;
        hash = rev_hash = (int)k;
        size = 1;
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
    me -> hash = me -> rev_hash = (int)me -> val;
    for (auto child : me->kids) if (child) me -> size += child -> size;

    ll forward = 0;
    if (me -> kids[0]) {
        forward = me -> kids[0] -> hash;
    }
    forward *= base;
    forward += me -> val;
    forward %= mod;
    if (me -> kids[1]) {
        forward *= pw[me -> kids[1] -> size];
        forward += me -> kids[1] -> hash;
        forward %= mod;
    }
    me -> hash = forward;

    ll reverse = 0;
    if (me -> kids[1]) {
        reverse = me -> kids[1] -> rev_hash;
    }
    reverse *= base;
    reverse += me -> val;
    reverse %= mod;
    if (me -> kids[0]) {
        reverse *= pw[me -> kids[0] -> size];
        reverse += me -> kids[0] -> rev_hash;
        reverse %= mod;
    }
    me -> rev_hash = reverse;
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
