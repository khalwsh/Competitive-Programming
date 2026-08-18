struct Node;
using PNode = Node*;
map<long long, PNode> mp;
 
struct Node {
    Node *l = 0, *r = 0, *par = 0;
    ull prior = rng();
    long long st, len, sz;
    char ch;
 
    Node(long long s, long long e, char c) : st(s), len(e-s+1), sz(e-s+1), ch(c) { mp[st] = this; }
    ~Node() { if(mp.count(st) && mp[st] == this) mp.erase(st); }
};
 
long long sz(PNode t){ return t ? t->sz : 0; }
 
void pull(PNode t){ if(t) t->sz = sz(t->l) + t->len + sz(t->r); }
 
void merge(PNode &t, PNode l, PNode r){
    if(!l || !r) t = l ? l : r;
    else if(l->prior > r->prior) {
        merge(l->r, l->r, r);
        if(l->r) l->r->par = l;
        t = l;
    }
    else {
        merge(r->l, l, r->l);
        if(r->l) r->l->par = r;
        t = r;
    }
    pull(t);
}
 
void split(PNode t, long long k, PNode &l, PNode &r){
    if(!t){ l = r = 0; return; }
    long long L = sz(t->l);
    if(k <= L) {
        split(t->l, k, l, t->l);
        if(t->l) t->l->par = t;
        r = t; pull(r);
        if(l) l->par = 0;
    }
    else if(k >= L + t->len) {
        split(t->r, k - L - t->len, t->r, r);
        if(t->r) t->r->par = t;
        l = t; pull(l);
        if(r) r->par = 0;
    }
    else {
        PNode tl = t->l, tr = t->r;
        if(tl) tl->par = 0;
        if(tr) tr->par = 0;
 
        PNode n1 = new Node(t->st, t->st + k - L - 1, t->ch);
        PNode n2 = new Node(t->st + k - L, t->st + t->len - 1, t->ch);
 
        merge(l, tl, n1);
        merge(r, n2, tr);
        delete t;
    }
}
 
void clean(PNode t){
    if(!t) return;
    clean(t->l); clean(t->r); delete t;
}
 
void ins(PNode &t, long long idx, long long s, long long e, char c){
    PNode l, r; 
    split(t, idx, l, r);
    merge(l, l, new Node(s, e, c));
    merge(t, l, r);
}
 
void del(PNode &t, long long idx, long long k){
    PNode l, m, r;
    split(t, idx, l, r);
    split(r, k, m, r);
    clean(m);
    merge(t, l, r);
}
 
long long get_k(PNode t, long long k){
    if(!t || k < 0 || k >= sz(t)) return -1;
    long long L = sz(t->l);
    if(k < L) return get_k(t->l, k);
    if(k < L + t->len) return t->st + (k - L);
    return get_k(t->r, k - L - t->len);
}
 
long long get_idx(long long val) {
    auto it = mp.upper_bound(val);
    if(it == mp.begin()) return -1;
    --it;
    PNode curr = it->second;
    long long idx = sz(curr->l) + (val - curr->st);
    while(curr->par) {
        PNode p = curr->par;
        if(p->r == curr) idx += sz(p->l) + p->len;
        curr = p;
    }
    return idx;
}
 