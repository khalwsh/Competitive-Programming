
struct MonotonicStack{
   stack<pair<int,int>>st;
   MonotonicStack(){
       st.emplace(-inf,-inf);
   }
   void push(int x){
       st.emplace(x,std::max(st.top().second,x));
   }
   void pop(){
       st.pop();
   }
   int top(){
       return st.top().first;
   }
   int max(){
       return st.top().second;
   }
   int size(){
       return (int)((int)st.size()-1);
   }
   bool empty(){
       return size()==0;
   }
};



struct MonotonicQueue{
    MonotonicStack add,remove;
    void push(int value){
        add.push(value);
    }
    void move(){
        while(!add.empty()){
            remove.push(add.top());
            add.pop();
        }
    }
    void pop(){
        if(remove.empty())move();
        remove.pop();
    }
    int top(){
        if(remove.empty())move();
        return remove.top();
    }
    int max(){
        return std::max(remove.max(),add.max());
    }
    int size(){
        return remove.size()+add.size();
    }
    bool empty(){
        return !size();
    }
};

