int n , m;
vector<int>adj[1<<10];
int dp[1001][1<<10];
bool can(int a, int b){
	if(a & b)return false;
	int x = ((~a & ~b) & ((1<<n) - 1));
	if(x % 3 != 0)return false;
	int y = x / 3;
	return (y & (y<<1)) == 0;
}
signed main() {
	khaled
	cin>>n>>m;
	for(int i = 0;i<(1<<n);i++){
		for(int j=0;j<(1<<n);j++){
			if(can(i , j)){
				adj[i].emplace_back(j);
			}
		}
	}
	dp[0][0] = 1;
	for(int i = 0;i<m;i++){
		for(int j = 0;j<(1<<n);j++){
			for(auto &val:adj[j]){
				dp[i + 1][val] += dp[i][j];
				dp[i + 1][val] %= mod;
			}
		}
	}
	cout<<dp[m][0]<<line;
 
}