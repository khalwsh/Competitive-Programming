public class Solution {
    public int longestPalindromicSubsequence(String s) {
        if (s == null || s.length() == 0) {
            return 0;
        }
        
        int n = s.length();
        // dp[i][j] represents the length of longest palindromic subsequence 
        // from index i to j
        int[][] dp = new int[n][n];
        
        // Base case: single characters are palindromes of length 1
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        // Fill the dp table
        // len is the current substring length we're considering
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;
                
                if (s.charAt(i) == s.charAt(j) && len == 2) {
                    dp[i][j] = 2;
                }
                else if (s.charAt(i) == s.charAt(j)) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else {
                    dp[i][j] = Math.max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Return the result for the entire string
        return dp[0][n - 1];
    }
}