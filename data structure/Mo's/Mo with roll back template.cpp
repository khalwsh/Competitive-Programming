struct Query {
    int l, r, id;
};

const int N = 300001;
const int SQ = 500; // sqrt(N) where N is maximum L in input when solving [L , R]
int n, q;
int ans[N];
int BLOCKSIZE = 0;
vector<Query> Buckets[SQ];

// you init BLOCKSIZE = sqrt(max(n , q)).
// then you fill Bucket then call MO() then answer will be filled in array ans[i] : answer of query i
void Mo() {
    for (int i = 0; i < SQ; i++) {
        sort(Buckets[i].begin(), Buckets[i].end(), [&](const Query &a, const Query &b)-> bool {
            return a.r < b.r;
        });
        int base = (i + 1) * BLOCKSIZE;
        int r = base;
        for (auto &qu: Buckets[i]) {
            while (r <= qu.r) {
                // insert element r in the data structure
                r++;
            }
            while (qu.l <= min(base - 1, qu.r)) {
                // insert element qu.l in the data structure
                qu.l++;
            }
            // answer in ans[qu.id]
            // roll back your data structure the updates happened in the while(qu.l)
        }
    }
}