template<typename T>
struct point3d {
    T x, y, z;
    point3d():point3d(0,0,0) {}
    point3d(T x, T y, T z): x(x), y(y), z(z) {}
    point3d& operator+=(const point3d &t) {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    point3d& operator-=(const point3d &t) {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    point3d& operator*=(T t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    point3d& operator/=(T t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    point3d operator+(const point3d &t) const {
        return point3d(*this) += t;
    }
    point3d operator-(const point3d &t) const {
        return point3d(*this) -= t;
    }
    point3d operator*(T t) const {
        return point3d(*this) *= t;
    }
    point3d operator/(T t) const {
        return point3d(*this) /= t;
    }
    friend point3d operator*(T a, point3d b) {
        return b * a;
    }
    friend istream& operator>>(istream &fin, point3d &b){
        fin>>b.x>>b.y;
        return fin;
    }
};
template<class TT>
TT dot(const point3d<TT>& a, const point3d<TT>& b) {
    //length of a * length of b projection in a direction = |a| * |b| * cos(x) : x is the angle between a,b
    /*        properties
     * 1- a.b = b.a
     * 2- (x * a).b = a.(x*b)
     * 3- (a+b).c = a.c + b.c
     * 4- a.b = 0 : a and b have angle 90 between them
     * 5- a.a = |a|^2
     * 6- |a| = sqrt(a.a)
     * 7- |a|cos(x) = (a.b)/|b|  , |b|cos(x) = (a.b)/|a|   : |a|cos(x) is projection of a in b , |b|cos(x) is projection of b in a
     * 8- cos(x) = (a.b)/(|b|*|a|) : x is the angle between vector a , vector b
     * 9- From the previous point we may see that the dot product is positive if the angle between them is acute,
     * -- negative if it is obtuse and it equals zero if they are orthogonal, i.e. they form a right angle.
    */
    return a.x * b.x + a.y * b.y;
}
template<typename TT>
TT norm(const point3d<TT>& a) {
    return dot(a, a);
}
template<typename TT>
double abs(const point3d<TT>& a) {
    return sqrt(norm(a));
}
template<typename TT>
double proj(const point3d<TT> &a,const point3d<TT>& b) {
    return dot(a, b) / abs(b);
}
template<typename TT>
double angle(const point3d<TT>& a, const point3d<TT>& b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}
template<typename TT>
point3d<TT> cross(const point3d<TT>& a,const point3d<TT>& b) {
    //B x C is the vector orthogonal to both B and C
    /*  properties
     * 1) A x B = - (B x A)
     * 2) (constant * A) x B = constant * (A x B)
     * 3) A.(B x C) = B.(C x A) = C.(A x B) = -B.(A x C)
     * 4) (A+B)xC = AxC + BxC
     * 5) |AxB| = |A||B|sin(x) : x is the angle between A,B
     * 6) AxB = 0 so A,B are parallel
    */
    return point3d(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}
template<typename TT>
double Volume(const point3d<TT>& a, const point3d<TT>& b, const point3d<TT>& c) {
    return dot(a, cross(b, c));
}
template<typename TT>
point3d<TT> intersect(const point3d<TT>& a1, const point3d<TT>& n1, const point3d<TT>& a2, const point3d<TT>& n2,const point3d<TT>& a3, const point3d<TT>& n3) {
    point3d x(n1.x, n2.x, n3.x);
    point3d y(n1.y, n2.y, n3.y);
    point3d z(n1.z, n2.z, n3.z);
    point3d d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
    return point3d(triple(d, y, z),
                   triple(x, d, z),
                   triple(x, y, d)) / triple(n1, n2, n3);
}