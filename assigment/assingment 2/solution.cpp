#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// ==========================================
// PART A: Fixed-Size Sliding Window
// ==========================================
class FixedWindow {
public:
    // 1. Reference / Brute-Force Solution O(n * K)
    static long long referenceMaxSum(const vector<int>& a, int k) {
        int n = a.size();
        if (k <= 0 || k > n) return -1;
        long long maxSum = LLONG_MIN;
        for (int i = 0; i <= n - k; ++i) {
            long long currentSum = 0;
            for (int j = i; j < i + k; ++j) {
                currentSum += a[j];
            }
            maxSum = max(maxSum, currentSum);
        }
        return maxSum;
    }

    // 2. Optimized Sliding Window Solution O(n)
    static long long optimizedMaxSum(const vector<int>& a, int k) {
        int n = a.size();
        if (k <= 0 || k > n) return -1;
        
        // Initialize first window sum
        long long currentSum = 0;
        for (int i = 0; i < k; ++i) {
            currentSum += a[i];
        }
        long long maxSum = currentSum;

        // Slide the window: add entering element, subtract leaving element
        for (int i = k; i < n; ++i) {
            currentSum += a[i] - a[i - k];
            maxSum = max(maxSum, currentSum);
        }
        return maxSum;
    }
};

// ==========================================
// PART B: Variable-Size Sliding Window
// ==========================================
class VariableWindow {
public:
    struct Result {
        int length;
        int startIdx;
        int endIdx;
    };

    // 1. Reference / Brute-Force Solution O(n^2)
    static Result referenceLongestSubarray(const vector<int>& a, int limit) {
        int n = a.size();
        int maxLen = 0;
        int bestStart = -1, bestEnd = -1;
        
        for (int i = 0; i < n; ++i) {
            long long currentSum = 0;
            for (int j = i; j < n; ++j) {
                currentSum += a[j];
                if (currentSum <= limit) {
                    int len = j - i + 1;
                    if (len > maxLen) {
                        maxLen = len;
                        bestStart = i;
                        bestEnd = j;
                    }
                } else {
                    break; // Non-negative constraint allows breaking early
                }
            }
        }
        return {maxLen, bestStart, bestEnd};
    }

    // 2. Optimized Variable-Size Sliding Window Solution O(n)
    static Result optimizedLongestSubarray(const vector<int>& a, int limit) {
        int n = a.size();
        int maxLen = 0;
        int bestStart = -1, bestEnd = -1;
        long long currentSum = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            currentSum += a[right]; // Expand right boundary
            
            // Contract left boundary while sum exceeds limit
            while (currentSum > limit && left <= right) {
                currentSum -= a[left];
                left++;
            }
            
            // Update best result if valid
            if (currentSum <= limit) {
                int len = right - left + 1;
                if (len > maxLen) {
                    maxLen = len;
                    bestStart = left;
                    bestEnd = right;
                }
            }
        }
        return {maxLen, bestStart, bestEnd};
    }
};

// ==========================================
// Test Runner
// ==========================================
int main() {
    cout << "================ C++ TESTS ================" << endl;
    
    // Fixed Window Test Cases
    vector<pair<vector<int>, int>> fixedTests = {
        {{2, 1, 5, 1, 3, 2}, 3}, // Expected: 9
        {{-4, -2, -7}, 2},       // Expected: -6
        {{6}, 1},                // Expected: 6
        {{1, 2, 3}, 3}           // Expected: 6
    };
    
    for (size_t i = 0; i < fixedTests.size(); ++i) {
        long long ref = FixedWindow::referenceMaxSum(fixedTests[i].first, fixedTests[i].second);
        long long opt = FixedWindow::optimizedMaxSum(fixedTests[i].first, fixedTests[i].second);
        cout << "Fixed Test " << i+1 << " -> Ref: " << ref << ", Opt: " << opt 
             << (ref == opt ? " [PASS]" : " [FAIL]") << endl;
    }

    // Variable Window Test Cases
    vector<pair<vector<int>, int>> varTests = {
        {{1, 2, 1, 1, 3}, 4}, // Expected length: 3
        {{5, 1, 1}, 2},       // Expected length: 2
        {{4, 2, 1}, 0},       // Expected length: 0
        {{0, 0, 1, 0}, 1}     // Expected length: 4
    };

    for (size_t i = 0; i < varTests.size(); ++i) {
        auto refRes = VariableWindow::referenceLongestSubarray(varTests[i].first, varTests[i].second);
        auto optRes = VariableWindow::optimizedLongestSubarray(varTests[i].first, varTests[i].second);
        cout << "Var Test " << i+1 << "   -> Ref Len: " << refRes.length << ", Opt Len: " << optRes.length 
             << (refRes.length == optRes.length ? " [PASS]" : " [FAIL]") << endl;
    }

    return 0;
}