// you are going from segment {a[0] , a[1]} to {a[2] , a[3]}
// with {Time} seconds passed and you move with 1 unit per second
// it return the point you are at the segment 
array<ld, 2> get_point(array<ld, 4> &a, ld Time) {
    auto [sx, sy, gx, gy] = a;
    if (Time <= 0) return array<ld, 2>{sx, sy};

    ld dx = gx - sx;
    ld dy = gy - sy;
    ld dist = sqrtl(dx * dx + dy * dy);

    if (dist <= 1e-18L) return array<ld, 2>{sx, sy};
    if (Time >= dist) return array<ld, 2>{gx, gy};

    ld frac = Time / dist; // fraction along segment
    return array<ld, 2>{sx + dx * frac, sy + dy * frac};
}