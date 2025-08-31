struct LazyAdd {
    ll firstValue;
    ll Increment;
    LazyAdd(ll f = 0, ll i = 0) : firstValue(f), Increment(i) {}
    LazyAdd operator+(const LazyAdd &a) const {
        return LazyAdd(firstValue + a.firstValue, Increment + a.Increment);
    }
};

inline ll sum_ap(ll s, ll inc, ll len) {
    return s * len + inc * (len - 1) * len / 2;
}
template<typename Val, typename Lazy, typename Ops>
struct PersistentSegTree {
    struct Node {
        Val val;
        Lazy lazy;
        bool lazyFlag;
        Node *L, *R;
        int len;
        Node(int _len = 0)
            : val(Ops::identity_val(_len)),
              lazy(Ops::identity_lazy()),
              lazyFlag(false), L(nullptr), R(nullptr), len(_len) {}
        Node(const Val &v, const Lazy &lz, bool lf, Node* l, Node* r, int _len)
            : val(v), lazy(lz), lazyFlag(lf), L(l), R(r), len(_len) {}
    };

    Node* clone(Node* p) {
        if (!p) return nullptr;
        return new Node(p->val, p->lazy, p->lazyFlag, p->L, p->R, p->len);
    }

    void push(Node* v) {
        if (!v || !v->lazyFlag || v->len == 1) return;

        int leftLen = (v->len + 1) / 2;
        int rightLen = v->len - leftLen;

        if (!v->L) v->L = new Node(leftLen);
        else v->L = clone(v->L);

        if (!v->R) v->R = new Node(rightLen);
        else v->R = clone(v->R);

        Ops::apply_lazy(v->L->val, v->lazy, leftLen);
        if (v->L->lazyFlag) v->L->lazy = v->L->lazy + v->lazy;
        else { v->L->lazy = v->lazy; v->L->lazyFlag = true; }

        Lazy shifted = v->lazy;
        shifted.firstValue += shifted.Increment * (ll)leftLen;
        Ops::apply_lazy(v->R->val, shifted, rightLen);
        if (v->R->lazyFlag) v->R->lazy = v->R->lazy + shifted;
        else { v->R->lazy = shifted; v->R->lazyFlag = true; }

        v->lazyFlag = false;
        v->lazy = Ops::identity_lazy();
    }

    Node* build(const vector<Val> &arr, int nl, int nr) {
        int len = nr - nl + 1;
        Node* v = new Node(len);
        if (nl == nr) {
            v->val = arr[nl];
            return v;
        }
        int mid = (nl + nr) >> 1;
        v->L = build(arr, nl, mid);
        v->R = build(arr, mid + 1, nr);
        v->val = Ops::merge(v->L->val, v->R->val);
        return v;
    }

    Node* update(Node* version, int nl, int nr, int l, int r, const Lazy &delta) {
        if (nl > r || nr < l) {
            return version ? clone(version) : nullptr;
        }

        Node* v = version ? clone(version) : new Node(nr - nl + 1);

        if (l <= nl && nr <= r) {
            ll shift = (ll)(nl - l);
            Lazy local(delta.firstValue + delta.Increment * shift, delta.Increment);
            Ops::apply_lazy(v->val, local, v->len);
            if (v->lazyFlag) v->lazy = v->lazy + local;
            else { v->lazy = local; v->lazyFlag = true; }
            return v;
        }

        push(v);
        int mid = (nl + nr) >> 1;
        v->L = update(v->L, nl, mid, l, r, delta);
        v->R = update(v->R, mid + 1, nr, l, r, delta);

        Val leftVal = v->L ? v->L->val : Ops::identity_val(mid - nl + 1);
        Val rightVal = v->R ? v->R->val : Ops::identity_val(nr - (mid + 1) + 1);
        v->val = Ops::merge(leftVal, rightVal);
        return v;
    }

    Val query(Node* v, int nl, int nr, int l, int r) {
        if (!v || nl > r || nr < l) return Ops::identity_val(0);
        if (l <= nl && nr <= r) return v->val;
        push(v);
        int mid = (nl + nr) >> 1;
        Val leftRes = query(v->L, nl, mid, l, r);
        Val rightRes = query(v->R, mid + 1, nr, l, r);
        return Ops::merge(leftRes, rightRes);
    }
};

template<typename Val, typename Lazy>
struct SumAddOps {
    static Val identity_val(int len) { (void)len; return 0LL; }
    static Lazy identity_lazy() { return Lazy(0, 0); }
    static Val merge(const Val &L, const Val &R) { return L + R; }
    static void apply_lazy(Val &v, const Lazy &lz, int len) {
        v += sum_ap(lz.firstValue, lz.Increment, len);
    }
};