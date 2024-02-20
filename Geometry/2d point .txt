template<class T>
struct point2d {
    T x, y;
    point2d():point2d(0,0) {}
    point2d(T x, T y): x(x), y(y) {}
    point2d& operator+=(const point2d &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(T t) {
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(T t) {
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const {
        return point2d(*this) -= t;
    }
    point2d operator*(T t) const {
        return point2d(*this) *= t;
    }
    point2d operator/(T t) const {
        return point2d(*this) /= t;
    }
    friend point2d operator*(T a, point2d b) {
        return b * a;
    }
    friend istream& operator>>(istream & fin , point2d &b){
        fin >>b.x>>b.y;
        return fin;
    }
};
template<class TT>
TT dot(const point2d<TT>& a, const point2d<TT>& b) {
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
TT norm(const point2d<TT>& a) {
    return dot(a, a);
}
template<typename TT>
double abs(const point2d<TT>& a) {
    return sqrt(norm(a));
}
template<typename TT>
double proj(const point2d<TT> &a,const  point2d<TT>& b) {
    return dot(a, b) / abs(b);
}
template<typename TT>
double angle(const point2d<TT>& a, const point2d<TT>& b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}
template<typename TT>
double cross(const point2d<TT>& a, const point2d<TT>& b) {
    //B x C is the vector orthogonal to both B and C
    /*  properties
     * 1) A x B = - (B x A)
     * 2) (constant * A) x B = constant * (A x B)
     * 3) A.(B x C) = B.(C x A) = C.(A x B) = -B.(A x C)
     * 4) (A+B)xC = AxC + BxC
     * 5) |AxB| = |A||B|sin(x) : x is the angle between A,B
     * 6) AxB = 0 so A,B are parallel
    */
    return a.x * b.y - a.y * b.x;
}
template<typename TT>
point2d<TT> intersect(const point2d<TT>& a1, const point2d<TT>& d1, const point2d<TT>& a2, const point2d<TT>& d2) {
    //note if they were the same line you gonna get (-inf,-inf)
    //if they were parallel you gonna get (-inf,-inf)
    double temp = cross(d1,d2);
    if(temp==0)return point2d<TT>(-inf,-inf);
    return a1 + cross(a2 - a1, d2) / temp * d1;
}