import java.util.*;

public class Solution {

    // ==========================================
    // PART A: Fixed-Size Sliding Window
    // ==========================================
    public static class FixedWindow {
        public static long referenceMaxSum(int[] a, int k) {
            int n = a.length;
            if (k <= 0 || k > n) return -1;
            long maxSum = Long.MIN_VALUE;
            for (int i = 0; i <= n - k; i++) {
                long currentSum = 0;
                for (int j = i; j < i + k; j++) {
                    currentSum += a[j];
                }
                maxSum = Math.max(maxSum, currentSum);
            }
            return maxSum;
        }

        public static long optimizedMaxSum(int[] a, int k) {
            int n = a.length;
            if (k <= 0 || k > n) return -1;
            long currentSum = 0;
            for (int i = 0; i < k; i++) {
                currentSum += a[i];
            }
            long maxSum = currentSum;
            for (int i = k; i < n; i++) {
                currentSum += a[i] - a[i - k];
                maxSum = Math.max(maxSum, currentSum);
            }
            return maxSum;
        }
    }

    // ==========================================
    // PART B: Variable-Size Sliding Window
    // ==========================================
    public static class Result {
        public int length;
        public int startIdx;
        public int endIdx;

        public Result(int length, int startIdx, int endIdx) {
            this.length = length;
            this.startIdx = startIdx;
            this.endIdx = endIdx;
        }
    }

    public static class VariableWindow {
        public static Result referenceLongestSubarray(int[] a, int limit) {
            int n = a.length;
            int maxLen = 0;
            int bestStart = -1, bestEnd = -1;
            for (int i = 0; i < n; i++) {
                long currentSum = 0;
                for (int j = i; j < n; j++) {
                    currentSum += a[j];
                    if (currentSum <= limit) {
                        int len = j - i + 1;
                        if (len > maxLen) {
                            maxLen = len;
                            bestStart = i;
                            bestEnd = j;
                        }
                    } else {
                        break;
                    }
                }
            }
            return new Result(maxLen, bestStart, bestEnd);
        }

        public static Result optimizedLongestSubarray(int[] a, int limit) {
            int n = a.length;
            int maxLen = 0;
            int bestStart = -1, bestEnd = -1;
            long currentSum = 0;
            int left = 0;

            for (int right = 0; right < n; right++) {
                currentSum += a[right];
                while (currentSum > limit && left <= right) {
                    currentSum -= a[left];
                    left++;
                }
                if (currentSum <= limit) {
                    int len = right - left + 1;
                    if (len > maxLen) {
                        maxLen = len;
                        bestStart = left;
                        bestEnd = right;
                    }
                }
            }
            return new Result(maxLen, bestStart, bestEnd);
        }
    }

    // ==========================================
    // Test Runner
    // ==========================================
    public static void main(String[] args) {
        System.out.println("================ JAVA TESTS ================");

        int[][] fixedArrays = {{2, 1, 5, 1, 3, 2}, {-4, -2, -7}, {6}, {1, 2, 3}};
        int[] fixedK = {3, 2, 1, 3};

        for (int i = 0; i < fixedArrays.length; i++) {
            long ref = FixedWindow.referenceMaxSum(fixedArrays[i], fixedK[i]);
            long opt = FixedWindow.optimizedMaxSum(fixedArrays[i], fixedK[i]);
            System.out.println("Fixed Test " + (i+1) + " -> Ref: " + ref + ", Opt: " + opt 
                + (ref == opt ? " [PASS]" : " [FAIL]"));
        }

        int[][] varArrays = {{1, 2, 1, 1, 3}, {5, 1, 1}, {4, 2, 1}, {0, 0, 1, 0}};
        int[] limits = {4, 2, 0, 1};

        for (int i = 0; i < varArrays.length; i++) {
            Result refRes = VariableWindow.referenceLongestSubarray(varArrays[i], limits[i]);
            Result optRes = VariableWindow.optimizedLongestSubarray(varArrays[i], limits[i]);
            System.out.println("Var Test " + (i+1) + "   -> Ref Len: " + refRes.length + ", Opt Len: " + optRes.length 
                + (refRes.length == optRes.length ? " [PASS]" : " [FAIL]"));
        }
    }
}