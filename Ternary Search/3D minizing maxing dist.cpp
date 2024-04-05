int n;
double x[101],y[101],z[101];
double Xa = 0,Xb = 0,Xc = 0;
double f3(double X,double Y, double Z){
    double res = 0;
    for(int i=0;i<n;i++){
        res = max(res,sqrt((X - x[i]) * (X - x[i]) + (Y - y[i]) * (Y - y[i])+(Z - z[i]) * (Z - z[i])));
    }
    return res;
}
pair<double,double> f2(double X,double Y){
    double left = -1e4,right = 1e4;
    double Z = 0;
    while(right - left >= eps){
        double m1 = left + (right - left)/3;
        double m2 = right - (right - left)/3;
        auto i = f3(X,Y,m1), j = f3(X,Y,m2);
        if(i>j){
            left = m1;
            Z = m2;
        }else
            right = m2 , Z = m1;
    }
    double res = 0;
    for(int i=0;i<n;i++){
        res = max(res,sqrt((X - x[i]) * (X - x[i]) + (Y - y[i]) * (Y - y[i])+(Z - z[i]) * (Z - z[i])));
    }
    return make_pair(res,Z);
}
pair<double,pair<double,double>> f1(double X){
    double left = -1e4,right = 1e4;
    double Y = 0;
    double Z = 0;
    while(right - left >= eps){
        double m1 = left + (right - left)/3;
        double m2 = right - (right - left)/3;
        auto i = f2(X,m1), j = f2(X,m2);
        if(i.first>j.first){
            left = m1;
            Y = m2 , Z = j.second;
        }else {
            right = m2;
            Y = m1 , Z = i.second;
        }
    }
    double res = 0;
    for(int i=0;i<n;i++){
        res = max(res,sqrt((X - x[i]) * (X - x[i]) + (Y - y[i]) * (Y - y[i])+(Z - z[i]) * (Z - z[i])));
    }
    return make_pair(res, make_pair(Y,Z));
}
void solve(){
    double left = -1e4,right = 1e4;
    while(right - left >= eps){
        double m1 = left + (right - left)/3;
        double m2 = right - (right - left)/3;
        auto i = f1(m1), j = f1(m2);
        if(i.first>j.first){
            left = m1;
            Xa = m2 , Xb = j.second.first , Xc = j.second.second;
        }else {
            right = m2;
            Xa = m1 , Xb = i.second.first , Xc = i.second.second;
        }
    }
}