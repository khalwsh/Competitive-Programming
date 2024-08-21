#include <bits/stdc++.h>
using namespace std;

// Define int as long long data type
#define int long long
// Define endl as newline character
#define endl '\n'
// Alias for first element in a pair
#define F first
// Alias for second element in a pair
#define S second

// Define a constant for maximum size
const int mxN = 1e5 + 5;
// Arrays for suffix array, position, temporary, and longest
// common prefix
int sa[mxN], pos[mxN], tmp[mxN], lcp[mxN];
// Variables for gap and size of the string
int gap, N;
// Input string
string S;

// Function to compare two positions in the suffix array

bool comp(int x, int y)
{
    // Compare positions based on their values in the pos
    // array
    if (pos[x] != pos[y])
        return pos[x] < pos[y];
    // If pos[x] == pos[y], compare their positions with a
    // gap
    x += gap;
    y += gap;
    // If within bounds, return comparison result based on
    // pos array; otherwise, return comparison of x and y
    return (x < N && y < N) ? pos[x] < pos[y] : x > y;
}

// Function to construct the suffix array
void suffix()
{
    // Initialize sa and pos arrays with initial values
    for (int i = 0; i < N; i++)
        sa[i] = i, pos[i] = S[i];

    // Loop for different gap values
    for (gap = 1;; gap <<= 1) {
        // Sort the suffix array based on the comparison
        // function comp
        sort(sa, sa + N, comp);
        // Update temporary array tmp
        for (int i = 0; i < N - 1; i++)
            tmp[i + 1] = tmp[i] + comp(sa[i], sa[i + 1]);
        // Update pos array
        for (int i = 0; i < N; i++)
            pos[sa[i]] = tmp[i];
        // If all suffixes are sorted, break the loop
        if (tmp[N - 1] == N - 1)
            break;
    }
}

// Function to construct the longest common prefix array
void build_lcp()
{
    for (int i = 0, k = 0; i < N; i++)
        if (pos[i] != N - 1) {
            int j = sa[pos[i] + 1];
            while (S[i + k] == S[j + k])
                k++;
            lcp[pos[i]] = k;
            if (k)
                k--;
        }
}

// Segment tree related functions for efficient range
// queries and updates Segment tree array
pair<int, int> seg[mxN * 10];
// Array to mark updates
int mark[mxN * 10];

// Function to push updates down the segment tree
void push(int k)
{
    if (mark[k]) {
        mark[k] = 0;
        seg[2 * k].F = seg[2 * k + 1].F = seg[k].F / 2;
        seg[2 * k].S = seg[2 * k + 1].S = 0;
        mark[2 * k] = mark[2 * k + 1] = 1;
    }
}

// Function to update values in the segment tree
void update(int v, int a, int b, int k, int x, int y)
{
    if (b < x || a > y)
        return;
    if (a <= x && b >= y) {
        seg[k].S += v;
        return;
    }
    int h = min(b, y) - max(a, x) + 1;
    push(k);
    seg[k].F += h * v;
    int d = (x + y) / 2;
    update(v, a, b, 2 * k, x, d);
    update(v, a, b, 2 * k + 1, d + 1, y);
}

// Function to assign values in the segment tree
int assign(int v, int a, int b, int k, int x, int y)
{
    if (b < x || a > y)
        return seg[k].F + (y - x + 1) * seg[k].S;
    if (a <= x && b >= y) {
        seg[k].F = (y - x + 1) * v;
        seg[k].S = 0;
        mark[k] = 1;
        return seg[k].F;
    }
    push(k);
    int d = (x + y) / 2;
    seg[2 * k].S += seg[k].S, seg[2 * k + 1].S += seg[k].S;
    seg[k].S = 0;
    seg[k].F = assign(v, a, b, 2 * k, x, d)
               + assign(v, a, b, 2 * k + 1, d + 1, y);
    return seg[k].F;
}

// Function to calculate sum in a range using segment tree
int sum(int a, int b, int k, int x, int y)
{
    if (b < x || a > y)
        return 0;
    if (a <= x && b >= y) {
        return seg[k].F + (y - x + 1) * seg[k].S;
    }
    push(k);
    seg[k].F += (y - x + 1) * seg[k].S;
    seg[2 * k].S += seg[k].S, seg[2 * k + 1].S += seg[k].S;
    seg[k].S = 0;
    int d = (x + y) / 2;
    return sum(a, b, 2 * k, x, d)
           + sum(a, b, 2 * k + 1, d + 1, y);
}

signed main()
{

    // Input string
    cin >> S;
    // Size of the string
    N = S.size();
    // Construct suffix array
    suffix();
    // Construct longest common prefix array
    build_lcp();
    // Given k value for substring extraction
    int k;
      cin >> k;

    // Calculate the k-th smallest lexicographically suffix
    // Calculate the position from the last
    k = N * (N + 1) / 2 - k + 1;

    // Construct a segment tree
    // Calculate the size of the segment tree array
    int K = 1 << (int)ceil(log2(N + 1));
    // Initialize current position
    int cur = 0;
    for (int i = N - 1; i >= 0; i--) {
        // Update the segment tree
        update(1, 1, N - sa[i], 1, 0, K - 1);
        // Get the previous longest common prefix
        int prev = (i ? lcp[i - 1] : 0);
        // Set the search range for the binary search
        int l = prev + 1, r = N - sa[i];
        // Initialize answer variable
        int ans = -1;
        // Binary search to find the longest common prefix
        // that satisfies the condition
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (cur + sum(m, N - sa[i], 1, 0, K - 1) >= k) {
                ans = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        // If answer is found, print the substring and exit
        // the loop
        if (ans != -1) {
            return cout << S.substr(sa[i], ans), 0;
        }
        // Update the current position and mark the segment
        // tree
        cur += sum(prev + 1, N - sa[i], 1, 0, K - 1);
        assign(0, prev + 1, N - sa[i], 1, 0, K - 1);
    }
}