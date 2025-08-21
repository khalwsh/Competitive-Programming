 int countSquares(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size(), result = 0, prev = 0;
        vector<int> dp(col + 1, 0);

        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                if (matrix[i - 1][j - 1] == 1) {
                    int temp = dp[j];
                    dp[j] = 1 + min(prev, min(dp[j - 1], dp[j]));
                    prev = temp;
                    result += dp[j];
                } else {
                    dp[j] = 0;
                }
            }
        }
        return result;
    }