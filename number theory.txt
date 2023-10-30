long long gcd_euldien_algo(int a,int b,int &x,int &y)
{
    if(a<0)
    {
        long long r= gcd_euldien_algo(-a,b,x,y);
        x*=-1;
        return r;
    }
    if(b<0)
    {
        long long r= gcd_euldien_algo(a,-b,x,y);
        y*=-1;
        return r;
    }
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    long long sol= gcd_euldien_algo(b,a%b,y,x);
    y-=(a/b)*x;
    return sol;
}

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
long long phi(long long n) {
long long result = n;
for (int i = 2; i * i <= n; i++) 
{
if (n % i == 0)
{
while (n % i == 0)
   n /= i;result -= result / i;
}
}
if (n > 1)result -= result / n;return result;
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
//mod inverse for a prime in a range
vector<int>mod_inverse_for_range(int p)
{
    vector<int>inv(p,1);
    for(int i=2;i<p;i++) {
        inv[i] = (p - (p / i) * inv[p % i] % p) % p;
    }
    return inv;
}