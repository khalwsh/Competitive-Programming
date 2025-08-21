/*
  Generic persistent segment tree template.

  Template params:
    Val  - stored value type (e.g. long long)
    Lazy - lazy operation type (e.g. long long for add, or pair<int,int> for range assign)
    Ops  - a struct providing static methods:
           - Val identity_val(int len)
           - Lazy identity_lazy()
           - Val merge(const Val &L, const Val &R)
           - void apply_lazy(Val &v, const Lazy &lz, int len)
           - void compose_lazy(Lazy &existing, const Lazy &add)
*/

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

        Ops::apply_lazy(v->L->val, v->lazy, v->L->len);
        if (v->L->lazyFlag) Ops::compose_lazy(v->L->lazy, v->lazy);
        else { v->L->lazy = v->lazy; v->L->lazyFlag = true; }

        Ops::apply_lazy(v->R->val, v->lazy, v->R->len);
        if (v->R->lazyFlag) Ops::compose_lazy(v->R->lazy, v->lazy);
        else { v->R->lazy = v->lazy; v->R->lazyFlag = true; }

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
        v->R = build(arr, mid+1, nr);
        v->val = Ops::merge(v->L->val, v->R->val);
        return v;
    }

    Node* update(Node* version, int nl, int nr, int l, int r, const Lazy &delta) {
        if (nl > r || nr < l) {
            return version ? clone(version) : nullptr;
        }

        Node* v = version ? clone(version) : new Node(nr - nl + 1);

        if (l <= nl && nr <= r) {
            Ops::apply_lazy(v->val, delta, v->len);
            if (v->lazyFlag) Ops::compose_lazy(v->lazy, delta);
            else { v->lazy = delta; v->lazyFlag = true; }
            return v;
        }

        push(v);
        int mid = (nl + nr) >> 1;
        v->L = update(v->L, nl, mid, l, r, delta);
        v->R = update(v->R, mid+1, nr, l, r, delta);
        Val leftVal = v->L ? v->L->val : Ops::identity_val(mid - nl + 1);
        Val rightVal = v->R ? v->R->val : Ops::identity_val(nr - (mid+1) + 1);
        v->val = Ops::merge(leftVal, rightVal);
        return v;
    }

    Val query(Node* v, int nl, int nr, int l, int r) {
        if (!v || nl > r || nr < l) return Ops::identity_val(0);
        if (l <= nl && nr <= r) return v->val;
        push(v);
        int mid = (nl + nr) >> 1;
        Val leftRes = query(v->L, nl, mid, l, r);
        Val rightRes = query(v->R, mid+1, nr, l, r);
        return Ops::merge(leftRes, rightRes);
    }
};

template<typename Val , typename Lazy>
struct SumAddOps {
    
    static Val identity_val(int len) { return 0LL; }
    static Lazy identity_lazy() { return 0LL; }
    static Val merge(const Val &L, const Val &R) { return L + R; }
    static void apply_lazy(Val &v, const Lazy &lz, int len) { v += lz * 1LL * len; }
    static void compose_lazy(Lazy &existing, const Lazy &add) { existing += add; }
};

/*
example of usage
   PersistentSegTree<ll, ll, SumAddOps<ll , ll>> pst;
   vector<PersistentSegTree<ll, ll, SumAddOps<ll , ll>>::Node*> roots(q + 5, nullptr);
*/