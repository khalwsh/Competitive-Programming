
vector<long long> prevMaxSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> prevSmall(n, -1), leftSum(n, 0);
        leftSum[0] = nums[0];
        stack<int> st;
        st.push(0);

        for(int i=1;i<n;i++) {
            while(!st.empty() and nums[st.top()] >= nums[i]) st.pop();
            if(!st.empty()) prevSmall[i] = st.top();

            int prevSmallIdx = prevSmall[i];
            int temp = i - prevSmallIdx;
            leftSum[i] += (temp*1LL*nums[i]);
            if(prevSmall[i] != -1) leftSum[i] += leftSum[prevSmallIdx];

            st.push(i);
        }
        return leftSum;
    }

    vector<long long> rightMaxSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> nextSmall(n, n), rightSum(n, 0);
        rightSum[n-1] = nums[n-1];
        stack<int> st;
        st.push(n-1);

        for(int i=n-2;i>=0;i--) {
            while(!st.empty() and nums[st.top()] >= nums[i]) st.pop();
            if(!st.empty()) nextSmall[i] = st.top();

            int nextSmallIdx = nextSmall[i];
            int temp = nextSmallIdx - i;
            rightSum[i] += (temp*1LL*nums[i]);
            if(nextSmall[i] != n) rightSum[i] += rightSum[nextSmallIdx];

            st.push(i);
        }
        return rightSum;
    }

    long long maximumSumOfHeights(vector<int>& nums) {
        int n = nums.size();
        vector<long long> leftSum = prevMaxSum(nums);
        vector<long long> rightSum = rightMaxSum(nums);

        long long ans = 0;
        for(int i=0;i<n;i++) {
            long long temp = leftSum[i] + rightSum[i] - nums[i];
            ans = max(ans, temp);
        }
        return ans;
    }