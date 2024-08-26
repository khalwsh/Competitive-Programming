int numSubmat(vector<vector<int>>& mat) {
      int rows = mat.size();
        int cols = mat[0].size();
        vector<vector<int>> height(rows, vector<int>(cols, 0));
        
        // Step 1: Calculate heights
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (mat[i][j] == 1) {
                    height[i][j] = (i == 0) ? 1 : height[i-1][j] + 1;
                }
            }
        }

        int totalSubmatrices = 0;

        // Step 2: Use Monotonic Stack for each row
        for (int i = 0; i < rows; ++i) {
            vector<int> stack;
            vector<int> sum(cols, 0);
            for (int j = 0; j < cols; ++j) {
                // Pop from the stack until the stack is empty or we find a height that is less than or equal to the current height
                while (!stack.empty() && height[i][stack.back()] >= height[i][j]) {
                    stack.pop_back();
                }

                // If the stack is empty, this is the smallest element encountered so far
                if (!stack.empty()) {
                    int k = stack.back();
                    sum[j] = sum[k] + height[i][j] * (j - k);
                } else {
                    sum[j] = height[i][j] * (j + 1);
                }
                
                // Add the number of submatrices ending at (i, j) to the total
                totalSubmatrices += sum[j];
                stack.push_back(j);
            }
        }
        
        return totalSubmatrices;
    }