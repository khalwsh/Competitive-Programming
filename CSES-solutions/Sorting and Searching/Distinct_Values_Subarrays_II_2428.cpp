/* problem statement text */
/*
CSES - Distinct Values Subarrays II

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to calculate the number of subarrays that have at most kkk distinct values.
Input
The first input line has two integers nnn and kkk.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print one integer: the number of subarrays.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
5 2
1 2 3 1 1

Output:
10
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int  n , k;
const int N = 2e5 + 5;
int x[N];
int main(){
    cin>>n>>k;
    for(int i = 0;i < n;i++)cin>>x[i];
    map<int , int>mp;
    int left = 0;
    ll res = 0;
    for(int i = 0;i < n;i++) {
        mp[x[i]]++;
        while(mp.size() > k) {
            mp[x[left]]--;
            if(mp[x[left]] == 0)mp.erase(x[left]);
            left++;
        }
        res += i - left + 1;
    }
    cout<<res<<endl;
}