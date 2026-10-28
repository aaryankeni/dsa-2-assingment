import java.util.ArrayList;
import java.util.List;

public class Assignment1 {

    // ==========================================
    // PART A: REMOVE DUPLICATES FROM SORTED ARRAY
    // ==========================================

    // Reference Solution: Uses auxiliary list (O(N) Space)
    public static int removeDuplicatesReference(List<Integer> nums) {
        if (nums == null || nums.isEmpty()) return 0;
        List<Integer> result = new ArrayList<>();
        for (int num : nums) {
            if (result.isEmpty() || result.get(result.size() - 1) != num) {
                result.add(num);
            }
        }
        return result.size();
    }

    // Optimized Solution: Slow and Fast Pointers (In-Place, O(1) Space)
    public static int removeDuplicatesOptimized(int[] nums) {
        if (nums == null || nums.length == 0) return 0;
        int slow = 0;
        for (int fast = 1; fast < nums.length; fast++) {
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
    public static int[] pairSumBruteForce(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] + nums[j] == target) {
                    return new int[]{i, j};
                }
            }
        }
        return new int[]{-1, -1};
    }

    // Optimized Solution: Opposite-End Pointers (O(N) Time)
    public static int[] pairSumOptimized(int[] nums, int target) {
        int left = 0;
        int right = nums.length - 1;
        while (left < right) {
            int currentSum = nums[left] + nums[right];
            if (currentSum == target) {
                return new int[]{left, right};
            } else if (currentSum < target) {
                left++;
            } else {
                right--;
            }
        }
        return new int[]{-1, -1};
    }

    public static void main(String[] args) {
        System.out.println("=== Part A: Remove Duplicates Test ===");
        int[] arr1 = {1, 1, 2, 2, 2, 3, 4, 4};
        int k = removeDuplicatesOptimized(arr1);
        System.out.print("k = " + k + ", Unique Prefix: ");
        for (int i = 0; i < k; i++) {
            System.out.print(arr1[i] + " ");
        }
        System.out.println("\n\n=== Part B: Pair Sum Test ===");
        int[] arr2 = {1, 2, 4, 7, 11, 15};
        int[] res = pairSumOptimized(arr2, 15);
        System.out.println("Target 15 -> Indices: (" + res[0] + ", " + res[1] + ")");
    }
}