struct pt {
    double x, y;
};
struct Line {
    double a, b, c;
};
double det(double a, double b, double c, double d) {
    return a*d - b*c;
}
bool intersect(const Line & m, const Line & n, pt & res) {
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS)
        return false;
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}
bool parallel(const Line & m, const Line &  n) {
    return abs(det(m.a, m.b, n.a, n.b)) < EPS;
}
bool equivalent(const Line & m, const Line & n) {
    return abs(det(m.a, m.b, n.a, n.b)) < EPS
           && abs(det(m.a, m.c, n.a, n.c)) < EPS
           && abs(det(m.b, m.c, n.b, n.c)) < EPS;
}