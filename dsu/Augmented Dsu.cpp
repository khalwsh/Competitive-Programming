
struct AugmentedDsu {
    int flaw;     //counting numbers of inconsistent assertions
    vector<int>diff,parent;
    AugmentedDsu(int n) {
        flaw = 0;
        diff.resize(n);parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            diff[i] = 0;
        }
    }
    int find(int x) {
        if (parent[x] == x) return x;
        int rx = find(parent[x]);  // rx is the root of x
        diff[x] = diff[parent[x]] + diff[x]; //add all potentials along the path,i.e.,potential calculated wrt root
        parent[x] = rx;
        return rx;
    }
    bool merge(int a, int b, int d) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb && diff[a] - diff[b] != d) {
            flaw++;
            return false;
        } else if (ra != rb) {
            diff[ra] = d + diff[b] - diff[a];
            parent[ra] = rb;
        }
        return true;
    }
    int query(int a,int b){
        int ra = find(a);
        int rb = find(b);
        if(ra != rb){
            //can't get answer
            return -inf;
        }
        return diff[a] - diff[b];
    }
};
