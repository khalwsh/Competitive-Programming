/* problem statement text */
/*
CSES - Forest Queries

Time limit: 1.00 s
Memory limit: 512 MB

You are given an n×nn \times nn×n grid representing the map of a forest. Each square is either empty or contains a tree. The upper-left square has coordinates (1,1)(1,1)(1,1), and the lower-right square has coordinates (n,n)(n,n)(n,n).
Your task is to process qqq queries of the form: how many trees are inside a given rectangle in the forest?
Input
The first input line has two integers nnn and qqq: the size of the forest and the number of queries.
Then, there are nnn lines describing the forest. Each line has nnn characters: . is an empty square and * is a tree.
Finally, there are qqq lines describing the queries. Each line has four integers y1y_1y1​, x1x_1x1​, y2y_2y2​, x2x_2x2​ corresponding to the corners of a rectangle.
Output
Print the number of trees inside each rectangle.
Constraints

1≤n≤10001 \le n \le 10001≤n≤1000
1≤q≤2⋅1051 \le q \le 2 \cdot 10^51≤q≤2⋅105
1≤y1≤y2≤n1 \le y_1 \le y_2 \le n1≤y1​≤y2​≤n
1≤x1≤x2≤n1 \le x_1 \le x_2 \le n1≤x1​≤x2​≤n

Example
Input:
4 3
.*..
*.**
**..
****
2 2 3 4
3 1 3 1
1 1 2 2

Output:
3
1
2
*/
#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);
long long mulmod(long long a,long long b,long long mod=INT64_MAX)
{
    long long res=0,y=a%mod;
    while(b>0)
    {
        if(b&1)
        {
            res=((res%mod)+(y%mod))%mod;
        }
        y=((y%mod)*(2ll%mod))%mod;
        b>>=1ll;
    }
    return (res%mod);
}
long long fast_power( long long base, long long power,long long mod=INT64_MAX)
{
    if(power==0)
        return 1;
    long long res = fast_power(base, power / 2,mod) % mod;
    res = ((res % mod) * (res % mod)) % mod;
    if (power & 1)
        return ((res % mod) * (base % mod)) % mod;
    else
        return res % mod;
}
long long gcd_ecludien_algorthim(long long a,long long b,long long &x,long long &y)
{
    //a*x+b*y=gcd(a,b)
    //this function return gcd of (a,b) and update the value of x,y to achieve the ecludien equation ax+by=gcd(a,b);
    //to get more x and y we can get another sol (x+k*b/gcd(a,b),y-k*a/gcd(a,b)):x is the x of first sol,and also the y
    if (b == 0) {
 
        x = 1;y = 0;return a;
    }
    long long x1, y1;
    long long d = gcd_ecludien_algorthim(b, a % b, x1, y1);
    x = y1;
    y = x1 - x * (a / b);
    return d;
}
long long euler_totient_function(long long n)
{
    if(n==1)
        return 1;
    set<long long>prime_factors;
    //calculate how many number smaller than or equal n and coprime with n gcd(n,x:0<x<n)==1
    auto res=(double)n;
    for(long long i=2;i*i<=n;i++)
    {
        while(n%i==0)
        {
            prime_factors.insert(i);
            n/=i;
        }
    }
    if(n!=1) {
        prime_factors.insert(n);
    }
    for(auto &val:prime_factors)
    {
        res*=(1.0-1.0/(double )val);
    }
    prime_factors.clear();
    return(long long)res;
 
}
vector<vector<long long>> generate_pascal_triangle(int size,long long mod=INT64_MAX)
{
    vector<vector<long long>>pascal;
    vector<long long>temp;
    temp.emplace_back(1);
    pascal.emplace_back(temp);
    temp.emplace_back(1);
    pascal.emplace_back(temp);
    temp.clear();
    for(int i=2;i<=size;i++)
    {
        temp.emplace_back(1);
        for(int j=1;j<=i-1;j++)
        {
            temp.emplace_back((pascal[i-1][j-1]+pascal[i-1][j])%mod);
        }
        temp.emplace_back(1);
        pascal.emplace_back(temp);
        temp.clear();
    }
    return pascal;
}
long long mod_inverse(long long A,long long M)
{
    //(A*B)%M=1;
    //to solve this gcd(A,M) must equal to one
    //B is the x from the ecludien algorthim which it is the value returned from this function
    //B is the x getting it from Ax+My=gcd(A,M):gcd(A,M)==1
    //we also can get the multiblicative inverse by take a which we want to get it's inverse
    //and raise it to the power of the value of the eulwer totient function of(mod)
    //a^(phi(mod)-1)%mod return B at (A*B%M)==1;
    //also if M is a prime we can get B by getting (pow(A,(M-2)))%M-->using fermat little theroy
    if(__gcd(A,M)!=1)
        return -1;
    return fast_power(A, euler_totient_function(M)-1,M);
}
long long lcm(long long a,long long b)
{
    return a*(b/__gcd(a,b));
}
vector<long long> sieve_of_eratosthenes(long long n)
{
    //return the numbers which  prime in the range from 1 to size
    //o(nlog(log(n)))
    vector<bool>primes(n+1,true);
    primes[0]=primes[1]=false;
    for(long long i=2;i*i<=n;i++)
    {
        if(primes[i])
        {
            for(long long j=i*i;j<=n;j+=i)
            {
                primes[j]=false;
            }
        }
    }
    vector<long long>prime_numbers;
    for(long long i=0;i<n+1;i++)
    {
        if(primes[i])
            prime_numbers.emplace_back(i);
 
    }
    return prime_numbers;
 
}
vector<long long> linear_sieve(long long n)
{
    //return all primes in range form [1,n] in o(n)
    vector<bool>prime(n+1,true);
    prime[0]=prime[1]=false;
    vector<long long>returned_primes;
    for(long long i=2;i<=n;i++)
    {
        if(prime[i])
            returned_primes.emplace_back(i);
 
        for(auto &val:returned_primes)
        {
            if(val*i>n)
                break;
            prime[val*i]=false;
        }
 
    }
    prime.clear();
    return returned_primes;
}
vector<long long> segment_sieve(long long l,long long r)
{
    //take a range and get the primes within the range
    //o(r-l+l)log(r)+sqrt(r)
    //to make integer ceil(l/i)----->(l+i-1)/i;
    //to get first number k|x  by k and bigger than n ---->  ((n+k-1)/k)*k;
    vector<bool>prime(r-l+1,true);
    for(long long i=2;i*i<=r;i++)
    {
        for(long long j=max(i*i,((l+i-1)/i)*i);j<=r;j+=i)
        {
            prime[j-l]=false;
        }
    }
    if(l==1)
        prime[0]=false;
    vector<long long>returned_primes;
    for(long long i=l;i<=r;i++)
    {
        if(prime[i-l])
            returned_primes.emplace_back(i);
    }
    return returned_primes;
}
long long solve_system_of_equation_using_chinese_reminder_theory(vector<long long>&rem,vector<long long>&mods)
{
    //solve for mods are coprime;
    long long prod=1,res=0;
    for(auto &val:mods)
        prod*=val;
    for(int i=0;i<(int)mods.size();i++)
    {
        long long sub_prod=prod/mods[i];
        res+=sub_prod* mod_inverse(sub_prod,mods[i])*rem[i];
    }
    return res%prod;
}
bool fermat_prime_testing(long long n,int number_of_moves=2000)
{
    // if n is prime and b is a natural number such that 1<b<n;
    // the following equation come true
    // (b^(n-1))%n=1
    // using mulmod in the fast power to make sure to avoid overflow
    //if p is a prime number so (p-1)!%p=p-1
    if(n==1||n==4||n==0)
        return false;
    if(n==2||n==3||n==5)
        return true;
    while(number_of_moves--)
    {
        if(fast_power((long long)2+std::rand()%(n-3),n-1,n)!=1)
            return false;
    }
    return true;
}
bool robin_muller_prime_test(long long n,int number_of_moves=2000)
{
    // factorize the n-1 to powers of 2 and an odd number
    // check if a: 1<a<n a^(d)==1||n-1 if true probably prime;
    // check if a: 1<a<n a^(2^(r)*d)==n-1||-1 if true probably prime
    // iterate for a number of moves if all true
    // there is big probality it is a prime
    return -1;
}
string convert_infix_to_postfix(string &s)
{
    map<char,int>mp;
    stack<char>sk;
    mp['+']=1;
    mp['-']=1;
    mp['*']=2;
    mp['/']=2;
    mp['^']=3;
    string res;
    for(auto &val:s)
    {
        if(isdigit(val)|| isupper(val)|| islower(val))
        {
            res+=val;
        }
        else if(sk.empty()||val=='('||!sk.empty()&&sk.top()=='(')
        {
            sk.push(val);
        }
        else if(val==')')
        {
            while(sk.top()!='(')
            {
                res+=sk.top();
                sk.pop();
            }
            sk.pop();
        }
        else
        {
            while(!sk.empty()&&mp[val]<=mp[sk.top()])
            {
                if(val=='^'&&sk.top()=='^')
                    break;
                res+=sk.top();
                sk.pop();
            }
            sk.push(val);
        }
    }
    while(!sk.empty())
        res+=sk.top(),sk.pop();
    return res;
}
string convert_infix_to_postfix_reversed(string &s)
{
    map<char,int>mp;
    stack<char>sk;
    mp['+']=1;
    mp['-']=1;
    mp['*']=2;
    mp['/']=2;
    mp['^']=3;
    string res;
    for(auto &val:s)
    {
        if(isdigit(val)|| isupper(val)|| islower(val))
        {
            res+=val;
        }
        else if(sk.empty()||val=='('||!sk.empty()&&sk.top()=='(')
        {
            sk.push(val);
        }
        else if(val==')')
        {
            while(sk.top()!='(')
            {
                res+=sk.top();
                sk.pop();
            }
            sk.pop();
        }
        else
        {
            while(!sk.empty()&&mp[val]<mp[sk.top()]||!sk.empty()&&mp[val]==mp[sk.top()]&&val=='^')
            {
                res+=sk.top();
                sk.pop();
            }
            sk.push(val);
        }
    }
    while(!sk.empty())
        res+=sk.top(),sk.pop();
    return res;
}
double convert_from_string_to_int(char &s)
{
    stringstream ss;
    ss<<s;
    double temp;
    ss>>temp;
    return temp;
}
double operation(double c,double d,char sign)
{
    if(sign=='^')
        return pow(c,d);
    else if(sign=='+')
        return c+d;
    else if(sign=='*')
        return c*d;
    else if(sign=='-')
        return c-d;
    else
        return c/d;
}
long double evaluate_postfix(string &s)
{
    stack<double>numbers;
    for(auto &val:s)
    {
        if(isdigit(val))
            numbers.push((convert_from_string_to_int(val)));
        else
        {
            double a=numbers.top();
            numbers.pop();
            double b=numbers.top();
            numbers.pop();
            numbers.push(operation(b,a,val));
        }
    }
    return numbers.top();
}
string infix_to_prefix(string &s)
{
    string reverse_infix;
    for(int i=(int)s.size()-1;i>=0;i--)
    {
        if(s[i]=='(')
            reverse_infix+=')';
        else if(s[i]==')')
            reverse_infix+='(';
        else
            reverse_infix+=s[i];
    }
    string reversed_postfix= convert_infix_to_postfix_reversed(reverse_infix);
    string prefix;
    for(int i=(int)reversed_postfix.size()-1;i>=0;i--)
    {
        prefix+=reversed_postfix[i];
    }
    return prefix;
}
class binary_search_tree{
private:
    int data{};
    binary_search_tree* left{},*right{};
    int length{};
public:
    binary_search_tree()
    {
        length=0;
        right=left=nullptr;
        data=-1;
    }
    binary_search_tree(int data){
        this->data=data;
        left=right=nullptr;
        length++;
    }
    void insert(int value)
    {
        if(length==0)
        {
            this->data=value;
            length++;
            return;
        }
        binary_search_tree*curr=this;
        while(true)
        {
            if(!curr->left&&value<=curr->data)
            {
                curr->left=new binary_search_tree{value};
                length++;
                break;
            }
            if(!curr->right&&value>curr->data)
            {
                curr->right=new binary_search_tree{value};
                length++;
                break;
            }
            if(value>curr->data)
                curr=curr->right;
            else
                curr=curr->left;
        }
 
    }
    void inorder_traversal()
    {
        if(left)
            left->inorder_traversal();
        cout<<this->data<<" ";
        if(right)
            right->inorder_traversal();
    }
};
class binary_tree{
private:
    int data{};
    binary_tree*left{},*right{};
    int length=0;
    int cal_height(binary_tree*temp,bool flag=true)
    {
        if(flag)
        {
            if(!temp)
            {
                return 0;
            }
            flag=false;
        }
        int h=1;
        if(temp&&temp->left)
            h=std::max(h,1+ cal_height(temp->left,flag));
        if(temp&&temp->right)
            h=std::max(h,1+ cal_height(temp->right,flag));
        return h;
    }
public:
    binary_tree(deque<int>&preorder,deque<int>&inorder,int inorder_start=0,int inorder_end=-1)
    {
        if(inorder_end==-1)
            inorder_end=(int)preorder.size()-1;
        data=preorder[0];
        preorder.pop_front();
        for(int split=inorder_start;split<=inorder_end;split++)
        {
            if(data==inorder[split])
            {
                if(inorder_start<split)
                    left=new binary_tree(preorder,inorder,inorder_start,split-1);
                if(inorder_end>split)
                    right=new binary_tree(preorder,inorder,split+1,inorder_end);
                break;
            }
        }
    }
    binary_tree(deque<pair<int,bool>>&preorder)
    {
        data=preorder.front().first;
        bool p=preorder.front().second;
        preorder.pop_front();
        if(!p)
        {
            left=new binary_tree(preorder);
            right=new binary_tree(preorder);
        }
    }
    void print_spirial()
    {
        deque<binary_tree*>q;
        q.push_front(this);
        bool turn=false;
        while(!q.empty())
        {
            if(!turn)
            {
                int sz=(int)q.size();
                while(sz--)
                {
                    cout << q.front()->data << " ";
                    if (q.front()->left)
                        q.push_back(q.front()->left);
                    if (q.front()->right)
                        q.push_back(q.front()->right);
                    q.pop_front();
                }
            }
            else
            {
                int sz=(int)q.size();
                int temp=sz;
                while(sz--)
                {
                    cout<<q[sz]->data<<" ";
                }
                while(temp--) {
                    if (q.front()->left)
                        q.push_back(q.front()->left);
                    if (q.front()->right)
                        q.push_back(q.front()->right);
                    q.pop_front();
                }
            }
            turn^=true;
        }
 
    }
    bool is_complete()
    {
        int h=tree_height();
        queue<binary_tree*>q;
        q.push(this);
        for(int i=1;i<h;i++)
        {
            int k=(int)q.size();
            while(k--)
            {
                if(q.front()->left)
                    q.push(q.front()->left);
                if(q.front()->right)
                    q.push(q.front()->right);
            }
        }
        if((int)q.size()!=((1<<h)-1))
            return false;
        int siz=(int)q.size()-((int)(1<<h)-1);
        while(siz--)
            q.pop();
        siz=(int)q.size();
        bool flag=false;
        while(!q.empty())
        {
            int counter=0;
            if(q.front()->left)
            {
                counter++;
                if(flag)
                    return false;
            }
            else
                flag=true;
            if(q.front()->right)
            {
                counter++;
                if(counter==1)
                    return false;
                if(flag)
                    return false;
            }
            else
                flag=true;
            q.pop();
        }
        return true;
    }
    void print_nodes(int level)
    {
        if(!level) {
            cout << this->data << " ";
            return;
        }
        else
        {
            if(left)
                left->print_nodes(level-1);
            if(right)
                right->print_nodes(level-1);
        }
    }
    void level_order_traversal_recursive()
    {
        int h=tree_height();
        for(int i=0;i<h;i++)
        {
            print_nodes(i);
        }
        cout<<line;
    }
    binary_tree(string postfix)
    {
        //create tree;
        stack<binary_tree*>tree;
        for(auto &val:postfix)
        {
            auto cur=new binary_tree{val};
            if(!isdigit(val))
            {
                cur->right=tree.top();
                tree.pop();
                cur->left=tree.top();
                tree.pop();
            }
            tree.push(cur);
        }
        this->data=tree.top()->data;
        this->right=tree.top()->right;
        this->left=tree.top()->left;
    }
    void print()
    {
        //print inorder expression tree
    }
    int diameter()
    {
        //it's the length of the longest path form deep right to deep left
        return cal_height(left)+ cal_height(right);
    }
    void print_left_boundary()
    {
        cout<<this->data<<" ";
        if(left)
            left->print_left_boundary();
        else if(right)
            right->print_left_boundary();
    }
    int count_internal_node()
    {
        return count_number_of_nodes()-count_leaf_nodes();
    }
    void clear()
    {
        if(left)
            delete left,left=nullptr;
        if(right)
            delete right,right=nullptr;
        length=0;
    }
    ~binary_tree()
    {
        clear();
    }
    bool is_perfect_iterative()
    {
        return count_number_of_nodes()==(1<<(tree_height()+1))-1;
    }
    bool find(int value)
    {
        bool found=value==data;
        if(left&&!found)
        {
            left->find(value);
        }
        if(right&&!found)
        {
            right->find(value);
        }
        return found;
    }
    int count_leaf_nodes()
    {
        static int counter=0;
        if(left)
            left->count_leaf_nodes();
        if(right)
            right->count_leaf_nodes();
        if(!left&&!right)
            counter++;
        return counter;
    }
    int count_number_of_nodes()
    {
        int counter=1;
        if(left)
            counter+=left->count_number_of_nodes();
        if(right)
            counter+=right->count_number_of_nodes();
        return counter;
    }
    binary_tree(int root_value)
    {
        data=root_value;
        length++;
    }
    void add(vector<int>path,vector<char>direction)
    {
        binary_tree* current=this;
        int n=(int)direction.size();
        for(int i=0;i<n;i++)
        {
            if(direction[i]=='L')
            {
                if(!current->left)
                {
                    current->left=new binary_tree{path[i]};
                    length++;
                }
                current=current->left;
            }
            else
            {
                if(!current->right)
                {
                    current->right=new binary_tree{path[i]};
                    length++;
                }
                current=current->right;
            }
        }
    }
    void display_inorder()
    {
        if(left)
            left->display_inorder();
        cout<<data<<" ";
        if(right)
            right->display_inorder();
    }
    int size()
    {
        return length;
    }
    int max()
    {
        int my_max=0;
        if(left)
            my_max=std::max(my_max,left->max());
        if(right)
            my_max=std::max(my_max,right->max());
        return std::max(data,my_max);
    }
    int min()
    {
        int my_min=INT_MAX;
        if(left)
            my_min=std::min(my_min,left->min());
        if(right)
            my_min=std::min(my_min,right->min());
        return std::min(my_min,data);
    }
    int tree_height()
    {
        int h=0;
        if(left)
            h=std::max(h,1+left->tree_height());
        if(right)
            h=std::max(h,1+right->tree_height());
        return h;
    }
    string parentization()
    {
        string repr="("+ to_string(data);
        vector<string>v;
        if(left)
            v.push_back(left->parentization());
        else
            v.push_back("()");
        if(right)
            v.push_back(right->parentization());
        else
            v.push_back("()");
        sort(v.begin(),v.end());
        for(auto &val:v)
            repr+=val;
        repr+=')';
        return repr;
    }
    void  level_order_traversal()
    {
        queue<binary_tree*>q;
        q.push(this);
        while(!q.empty())
        {
            cout<<q.front()->data<<" ";
            if(q.front()->left)
                q.push(q.front()->left);
            if(q.front()->right)
                q.push(q.front()->right);
            q.pop();
        }
    }
};
double findAngle(double hh, double mm)
{
    // handle 24-hour notation
    hh = (int)hh % 12;
 
    // find the position of the hour's hand
    double h = (hh * 360) / 12 + (mm * 360) / (12 * 60);
 
    // find the position of the minute's hand
    double m = (mm * 360) / (60);
 
    // calculate the angle difference
    double angle = abs(h - m);
 
    // consider the shorter angle and return it
    if (angle > 180) {
        angle = 360 - angle;
    }
 
    return angle;
}
double eps=1e-9;
int main() {
    khaled
    int n;
    cin>>n;
    int m;
    m=n;
    int q;
    cin>>q;
    vector<vector<char>>in(n,vector<char>(n));
    int l=0;
    for(auto &val:in)
    {
        for(auto &x:val)
            cin>>x;
    }
    vector<vector<int>>v(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            v[i][j]=(in[i-1][j-1]=='*');
        }
    }
    vector<int>temp(m+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            v[i][j]+=v[i][j-1];
        }
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            v[j][i]+=v[j-1][i];
        }
    }
    while(q--)
    {
        int x1,x2,y1,y2;
        cin>>x1>>y1>>x2>>y2;
 
        cout<<v[x2][y2]+v[x1-1][y1-1]-v[x1-1][y2]-v[x2][y1-1];
        cout<<line;
    }
}
 
 
 