/* problem statement text */
/*
CSES - Tower of Hanoi

Time limit: 1.00 s
Memory limit: 512 MB

The Tower of Hanoi game consists of three stacks (left, middle and right) and nnn round disks of different sizes. Initially, the left stack has all the disks, in increasing order of size from top to bottom.
The goal is to move all the disks to the right stack using the middle stack. On each move you can move the uppermost disk from a stack to another stack. In addition, it is not allowed to place a larger disk on a smaller disk.
Your task is to find a solution that minimizes the number of moves.
Input
The only input line has an integer nnn: the number of disks.
Output
First print an integer kkk: the minimum number of moves.
After this, print kkk lines that describe the moves. Each line has two integers aaa and bbb: you move a disk from stack aaa to stack bbb.
Constraints

1≤n≤161 \le n \le 161≤n≤16

Example
Input:
2

Output:
3
1 2
1 3
2 3
*/
#include<bits/stdc++.h>
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
long long fast_power(long long base,long long power,long long m);
int counter=0;
void towerOfHanoi(int n, int from_rod, int to_rod,int aux_rod);
int main()
{
    khaled
    int n;
    cin>>n;
    cout<<(1<<n)-1;
    cout<<line;
    towerOfHanoi(n,1,3,2);
 
}
void towerOfHanoi(int n, int from_rod, int to_rod,int aux_rod)
{
    if (n == 0) {
        return;
    }
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    cout<< from_rod<< " " << to_rod << line;
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}
long long fast_power(long long base,long long power,long long m)
{
    if(power==1||power==0)
        return base*power+(!power);
    long long res=(fast_power(base,power/2,m)%m)%m;
    if(power&1)
        return(((((base%m)*(res%m))%m)*(res%m))%m)%m;
    else
        return ((res%m)*(res%m))%m;
}