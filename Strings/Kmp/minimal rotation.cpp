int findMinRotation(string s){
    // Concatenate string to itself to avoid modular
    // arithmetic
    s += s;

    // Initialize failure function
    vector<int> failureFunc(s.size(), -1);

    // Initialize least rotation of string found so far
    int minRotationIdx = 0;

    // Iterate over the concatenated string
    for (int currentIdx = 1; currentIdx < s.size();
         ++currentIdx) {
        char currentChar = s[currentIdx];
        int failureIdx
            = failureFunc[currentIdx - minRotationIdx - 1];

        // Find the failure function value
        while (
            failureIdx != -1
            && currentChar
                   != s[minRotationIdx + failureIdx + 1]) {
            if (currentChar
                < s[minRotationIdx + failureIdx + 1]) {
                minRotationIdx
                    = currentIdx - failureIdx - 1;
                }
            failureIdx = failureFunc[failureIdx];
                   }

        // Update the failure function and the minimum
        // rotation index
        if (currentChar
            != s[minRotationIdx + failureIdx + 1]) {
            if (currentChar < s[minRotationIdx]) {
                minRotationIdx = currentIdx;
            }
            failureFunc[currentIdx - minRotationIdx] = -1;
            }
        else {
            failureFunc[currentIdx - minRotationIdx]
                = failureIdx + 1;
        }
         }

    // Return the index of the lexicographically minimal
    // rotation
    return minRotationIdx;
}