struct SevenSegment{
    int a,b,c,d,e,f,g;
    SevenSegment(int A,int B,int C,int D,int E,int F,int G){
        a = A;
        b = B;
        c = C;
        d = D;
        e = E;
        f = F;
        g = G;
    }
    static SevenSegment Generate(int value){
        SevenSegment res(1,1,1,1,1,1,0);
        if(value == 1)
            res = SevenSegment(0,1,1,0,0,0,0);
        else if(value == 2)
            res = SevenSegment(1,1,0,1,1,0,1);
        else if(value == 3)
            res = SevenSegment(1,1,1,1,0,0,1);
        else if(value == 4)
            res = SevenSegment(0,1,1,0,0,1,1);
        else if(value == 5)
            res = SevenSegment(1,0,1,1,0,1,1);
        else if(value == 6)
            res = SevenSegment(1,0,1,1,1,1,1);
        else if(value == 7)
            res = SevenSegment(1,1,1,0,0,0,0);
        else if(value == 8)
            res = SevenSegment(1,1,1,1,1,1,1);
        else if(value == 9)
            res = SevenSegment(1,1,1,1,0,1,1);
        return res;
    }
    static pair<int,int> cost(const SevenSegment &a,const SevenSegment &b){
        int Erase = 0;
        int Add = 0;
        if(a.a != b.a){
            if(a.a == 1)Erase++;
            else Add++;
        }if(a.b != b.b){
            if(a.b == 1)Erase++;
            else Add++;
        }if(a.c != b.c){
            if(a.c == 1)Erase++;
            else Add++;
        }
        if(a.d != b.d){
            if(a.d == 1)Erase++;
            else Add++;
        }
        if(a.e != b.e){
            if(a.e == 1)Erase++;
            else Add++;
        }
        if(a.f != b.f){
            if(a.f == 1)Erase++;
            else Add++;
        }
        if(a.g != b.g){
            if(a.g == 1)Erase++;
            else Add++;
        }
        return {Erase,Add};
    }
    bool operator ==(const SevenSegment &seg){
        return a == seg.a && b == seg.b && c == seg.c && d == seg.d && e == seg.e && f == seg.f && g == seg.g;
    }
    static int GenerateReverse(const SevenSegment &value) {
        if (value == SevenSegment(0, 1, 1, 0, 0, 0, 0))
            return 1;
        else if (value == SevenSegment(1, 1, 0, 1, 1, 0, 1))
            return 2;
        else if (value == SevenSegment(1, 1, 1, 1, 0, 0, 1))
            return 3;
        else if (value == SevenSegment(0, 1, 1, 0, 0, 1, 1))
            return 4;
        else if (value == SevenSegment(1, 0, 1, 1, 0, 1, 1))
            return 5;
        else if (value == SevenSegment(1, 0, 1, 1, 1, 1, 1))
            return 6;
        else if (value == SevenSegment(1, 1, 1, 0, 0, 0, 0))
            return 7;
        else if (value == SevenSegment(1, 1, 1, 1, 1, 1, 1))
            return 8;
        else if (value == SevenSegment(1, 1, 1, 1, 0, 1, 1))
            return 9;
        return 0;
    }
};