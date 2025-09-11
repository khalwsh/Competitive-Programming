
// after you update a node prop and recalc
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
static std::mt19937_64 RNG(
    (unsigned) chrono::steady_clock::now().time_since_epoch().count()
);
long long randomLongLong(long long l, long long r) {
    std::uniform_int_distribution<long long> dist(l, r);
    return dist(RNG);
}
struct Info {
    ll mx1 , mx0 , suf , pref , l , r, total;
    bool alter;
    bool rev;
    Info(ll k = -1) {
        alter = false;
        rev = false;
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
    if (a.total == 0) return b;
    if (b.total == 0) return a;
    Info res;
    res.total = a.total + b.total;
    res.l = a.l;
    res.r = b.r;
    res.alter = false;
    res.pref = a.pref;
    if (a.pref == a.total && a.r == b.l) {
        res.pref = a.total + b.pref;
    }
    res.suf = b.suf;
    if (b.suf == b.total && b.l == a.r) {
        res.suf = b.total + a.suf;
    }
    res.mx0 = max(a.mx0, b.mx0);
    res.mx1 = max(a.mx1, b.mx1);
    if (a.r == b.l) {
        ll conn = a.suf + b.pref;
        if (a.r == 0) {
            res.mx0 = max(res.mx0, conn);
        } else {
            res.mx1 = max(res.mx1, conn);
        }
    }
    return res;
}
void prop(Treap* me) {
    if (me == nullptr) return;
    if (me->info.alter) {
        me->val ^= 1;
        if (me->info.l != -1) me->info.l ^= 1;
        if (me->info.r != -1) me->info.r ^= 1;
        swap(me->info.mx0, me->info.mx1);
        for (auto &child : me->kids) if (child) child->info.alter ^= true;
        me->info.alter = false;
    }
    if (me -> info.rev) {
        swap(me -> kids[0] , me -> kids[1]);
        if (me -> kids[0]) me -> kids[0]->info.rev ^= true;
        if (me -> kids[1]) me -> kids[1]->info.rev ^= true;
        swap(me->info.pref, me->info.suf);
        swap(me->info.l, me->info.r);
        me -> info.rev ^= true;
    }
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