for(int i = 0;i < Bits;i++) {
		for(int j = 0;j <= MaxN;j++) {
			if(i & (1<<i)) {
				dp[i ^ (1<<i)] -= dp[i];
			}
		}
	}