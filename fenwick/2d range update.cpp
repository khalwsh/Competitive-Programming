const int maxn = 1e3 + 5;
ll S[4][maxn][maxn];

void add_point(int z, int x, int Y, ll c) {
    for(; x < maxn; x += x & -x) {
        for(int y = Y; y < maxn; y += y & -y) {
            S[z][x][y] += c;
        }
    }
}

// add c on [a, inf) x [b, inf)
void add_suffix(int a, int b, ll c) {
    add_point(0, a, b, c);
    add_point(1, a, b, -c * (a - 1));
    add_point(2, a, b, -c * (b - 1));
    add_point(3, a, b, c * (a - 1) * (b - 1));
}

// add c on [x1, x2] x [y1, y2]
void add_range(int x1, int y1, int x2, int y2, ll c) {
    add_suffix(x1, y1, c);
    add_suffix(x1, y2 + 1, -c);
    add_suffix(x2 + 1, y1, -c);
    add_suffix(x2 + 1, y2 + 1, c);
}


ll get_point(int z, int x, int Y) {
    ll res = 0;
    for(; x > 0; x -= x & -x) {
        for(int y = Y; y > 0; y -= y & -y) {
            res += S[z][x][y];
        }
    }
    return res;
}

// get sum on [0, x] x [0, y]
ll get_prefix(int x, int y) {
    return get_point(0, x, y) * x * y
         + get_point(1, x, y) * y
         + get_point(2, x, y) * x
         + get_point(3, x, y);
}

// get sum on [x1, x2] x [y1, y2]
ll get_range(int x1, int y1, int x2, int y2) {
    return get_prefix(x2, y2)
        - get_prefix(x1 - 1, y2)
        - get_prefix(x2, y1 - 1)
        + get_prefix(x1 - 1, y1 - 1);
}
