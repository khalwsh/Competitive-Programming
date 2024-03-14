MontonicStack:
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
