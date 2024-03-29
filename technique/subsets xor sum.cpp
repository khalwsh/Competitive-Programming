int xorSum(vector<int>&arr, int n)
{
    int bits = 0;
    for (int i=0; i < n; ++i)
        bits |= arr[i];
    int ans = mul(bits , fast_power(2ll, n-1,mod),mod);
    return ans;
}