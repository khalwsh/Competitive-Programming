int n;
int v[N];
const int SQ = 800;
int sq;
vector<int>pre[SQ];
void Modify(int ind , int NewVal) {
    int Block = ind / sq;//gettign array index
    int IndBlock = lower_bound(pre[Block].begin(), pre[Block].end(), v[ind]) - pre[Block].begin();
    //getting index inside the block
    v[ind] = NewVal;
    pre[Block][IndBlock] = NewVal;
    //sort block in o(block size)
    while (IndBlock + 1 < pre[Block].size() && pre[Block][IndBlock] > pre[Block][IndBlock + 1])
        swap(pre[Block][IndBlock], pre[Block][IndBlock + 1]), IndBlock++;
    while (IndBlock - 1 >= 0 && pre[Block][IndBlock - 1] > pre[Block][IndBlock])
        swap(pre[Block][IndBlock], pre[Block][IndBlock - 1]), IndBlock--;
}
int Query(int l,int r,int c) {
    int BS = l / sq;
    int BE = r / sq;
    //knowing block start and block end
    int res = 0;
    for (int i = l; i < min(r + 1, (BS + 1) * sq); i++) {
        res += v[i] >= c;//iterate on the first un completed protion
    }
    if (BS == BE)return res;//return it if they are in the same block
    for (int i = BE * sq; i <= r; i++) {
        res += v[i] >= c;//iterate on the last un completed protion
    }
    if (BS == BE - 1)return res;//return it if the blocks are conseq.
    for (int i = (BS + 1); i < BE; i++) {
        res += (int) pre[i].size() - (int) (lower_bound(pre[i].begin(), pre[i].end(), c) - pre[i].begin());
        //iterate on the blocks in between and calculate answer fast.
    }
    return res;
}
signed main() {
    khaled
    cin >> n;
    for (int i = 0; i < n; i++)cin >> v[i];
    sq = (int) sqrt(n) + 1;
    for (int i = 0; i < n; i++) {
        pre[i / sq].emplace_back(v[i]);
        // build the partions
    }
    for (auto &val: pre)sort(val.begin(), val.end());
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int type;
        cin >> type;
        if (type) {
            //modify
            int ind, newVal;
            cin >> ind >> newVal;
            ind--;
            Modify(ind, newVal);
        } else {
            //query
            int l, r, c;
            cin >> l >> r >> c;
            l--, r--;
            cout << Query(l, r, c) << line;
        }
    }
}
