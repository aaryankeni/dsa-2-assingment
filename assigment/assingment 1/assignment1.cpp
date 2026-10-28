#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

// ==========================================
// PART A: REMOVE DUPLICATES FROM SORTED ARRAY
// ==========================================

// Reference Solution: Uses auxiliary vector (O(N) Space)
int removeDuplicatesReference(const std::vector<int>& nums) {
    if (nums.empty()) return 0;
    std::vector<int> result;
    for (int num : nums) {
        if (result.empty() || result.back() != num) {
            result.push_back(num);
        }
    }
    return result.size();
}

// Optimized Solution: Slow and Fast Pointers (In-Place, O(1) Space)
int removeDuplicatesOptimized(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    int slow = 0;
    for (int fast = 1; fast < (int)nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    return slow + 1;
}

// ==========================================
// PART B: PAIR SUM IN SORTED ARRAY
// ==========================================

// Brute-Force Solution: Nested loops (O(N^2) Time)
std::pair<int, int> pairSumBruteForce(const std::vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Optimized Solution: Opposite-End Pointers (O(N) Time)
std::pair<int, int> pairSumOptimized(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = (int)nums.size() - 1;
    while (left < right) {
        int currentSum = nums[left] + nums[right];
        if (currentSum == target) {
            return {left, right};
        } else if (currentSum < target) {
            left++;
        } else {
            right--;
        }
    }
    return {-1, -1};
}

int main() {
    std::cout << "=== Part A: Remove Duplicates Test ===" << std::endl;
    std::vector<int> arr1 = {1, 1, 2, 2, 2, 3, 4, 4};
    int k = removeDuplicatesOptimized(arr1);
    std::cout << "k = " << k << ", Unique Prefix: ";
    for (int i = 0; i < k; i++) std::cout << arr1[i] << " ";
    
    std::cout << "\n\n=== Part B: Pair Sum Test ===" << std::endl;
    std::vector<int> arr2 = {1, 2, 4, 7, 11, 15};
    auto res = pairSumOptimized(arr2, 15);
    std::cout << "Target 15 -> Indices: (" << res.first << ", " << res.second << ")\n";
    
    return 0;
}