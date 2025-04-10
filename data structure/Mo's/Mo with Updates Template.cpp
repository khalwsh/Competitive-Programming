int A[N],n,comp[2 * N],ans[N];
int Freq[2 * N],old[2 * N],New[2 * N];
int upIdx[N];
int st,en,tim,BlockSize,CompSize,q,nq,cnt = 0;
int qs[N],qe[N],qi[N],qt[N];
void compress() {
    sort(comp, comp + CompSize);
    CompSize = (int)(unique(comp, comp + CompSize) - comp);
    for (int i = 0; i < n; i++) {
        A[i] = (int)(lower_bound(comp, comp + CompSize, A[i]) - comp);
    }
    for (int i = 1; i <= tim; i++) {
        old[i] = (int)(lower_bound(comp, comp + CompSize, old[i]) - comp);
        New[i] = (int)(lower_bound(comp, comp + CompSize, New[i]) - comp);
    }
}
void Add(int CompressedValue) {
    
}
void Erase(int CompressedValue) {
    
}
void update(int qId) {
    while (tim < qt[qId]) {
        tim++;
        if (upIdx[tim] >= st && upIdx[tim] < en) {
            Erase(old[tim]);
            Add(New[tim]);
        }
        A[upIdx[tim]] = New[tim];
    }
    while (tim > qt[qId]) {
        if (upIdx[tim] >= st && upIdx[tim] < en) {
            Erase(New[tim]);
            Add(old[tim]);
        }
        A[upIdx[tim]] = old[tim];
        tim--;
    }
    while (en <= qe[qId]) {
        Add(A[en++]);
    }
    while (en - 1 > qe[qId]) {
        Erase(A[--en]);
    }
    while (st - 1 >= qs[qId]) {
        Add(A[--st]);
    }
    while (st < qs[qId]) {
        Erase(A[st++]);
    }
}
signed main() {
    khaled
    cin >> n;
    cin >> q;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        comp[i] = A[i];
    }
    CompSize = n;
    for (int i = 0; i < q; i++) {
        char ch;
        cin >> ch;
        int x, y;
        cin >> x >> y;
        if (ch == '2') {
            qs[nq] = x;
            qe[nq] = y;
            qi[nq] = nq;
            qt[nq] = tim;
            nq++;
        } else {
            tim++;
            old[tim] = A[x];
            New[tim] = y;
            upIdx[tim] = x;
            A[x] = y;
            comp[CompSize++] = y;
        }
    }
    compress();
    BlockSize = ceil(pow(n, 2.0 / 3.0));
    sort(qi,qi + nq , [](int a,int b)->int{
        int BsA, BeA,BsB,BeB;
        BsA = qs[a]/BlockSize;
        BeA = qe[a]/BlockSize;
        BsB = qs[b]/BlockSize;
        BeB = qe[b]/BlockSize;
        return tie(BsA,BeA,qt[a]) < tie(BsB,BeB,qt[b]);
    });
    for(int i=0;i<nq;i++){
        update(qi[i]);
        ans[qi[i]] = cnt;
    }
    for(int i=0;i<nq;i++){
        cout<<ans[i]<<line;
    }
}