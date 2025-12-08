/* problem statement text */
/*
CSES - Range Xor Queries

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to process qqq queries of the form: what is the xor sum of values in range [a,b][a,b][a,b]?
Input
The first input line has two integers nnn and qqq: the number of values and queries.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Finally, there are qqq lines describing the queries. Each line has two integers aaa and bbb: what is the xor sum of values in range [a,b][a,b][a,b]?
Output
Print the result of each query.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
8 4
3 2 4 5 1 1 5 3
2 4
5 6
1 8
3 3

Output:
3
0
6
4
*/
#include<bits/stdc++.h>
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
int main() {
    khaled
    long long n,q;
    cin>>n>>q;
    vector<long long>v(n);
    vector<long long>v_xor(n);
    for(auto&val:v)
        cin>>val;
    v_xor[0]=v[0];
    for(int i=1;i<n;i++)
    {
        v_xor[i]=v_xor[i-1]^v[i];
    }
    while(q--)
    {
        int a,b;
        cin>>a>>b;
        b--;
        a--;
        if(a==0)
            cout<<v_xor[b];
        else
            cout<<(v_xor[b]^v_xor[a-1]);
        cout<<line;
 
    }
}