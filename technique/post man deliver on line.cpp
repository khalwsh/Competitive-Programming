int k;
ll solve(vector<pair<ll,ll>>v){
	ll res = 0 , rem = k , pos = 0;
	for(auto &val:v){
		if(val.second >= rem){
			res += pos;
			if(rem != k)val.second -= rem;
			res += (2 * ((val.second + k - 1) / k) - 1) * val.first;
			rem = ((val.second + k - 1) / k * k) - val.second;
			pos = val.first;
		}else{
			rem -= val.second;
			res += abs(val.first - pos);
			pos = val.first;
		}
	}
	return res + pos;
}