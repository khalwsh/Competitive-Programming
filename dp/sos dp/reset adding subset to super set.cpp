for(int i = 0;i < Bits;i++) {
		for(int j = MaxN - 1;j >= 0;j--) {
			if(i & (1<<i)) {
				dp[i ^ (1<<i)] -= dp[i];
			}
		}
	}