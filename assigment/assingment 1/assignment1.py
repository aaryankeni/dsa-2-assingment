# ==========================================
# PART A: REMOVE DUPLICATES FROM SORTED ARRAY
# ==========================================

# Reference Solution: Uses auxiliary list (O(N) Space)
def remove_duplicates_reference(nums):
    if not nums:
        return 0
    result = []
    for num in nums:
        if not result or result[-1] != num:
            result.append(num)
    return len(result)

# Optimized Solution: Slow and Fast Pointers (In-Place, O(1) Space)
def remove_duplicates_optimized(nums):
    if not nums:
        return 0
    slow = 0
    for fast in range(1, len(nums)):
        if nums[fast] != nums[slow]:
            slow += 1
            nums[slow] = nums[fast]
    return slow + 1


# ==========================================
# PART B: PAIR SUM IN SORTED ARRAY
# ==========================================

# Brute-Force Solution: Nested loops (O(N^2) Time)
def pair_sum_brute_force(nums, target):
    n = len(nums)
    for i in range(n):
        for j in range(i + 1, n):
            if nums[i] + nums[j] == target:
                return (i, j)
    return (-1, -1)

# Optimized Solution: Opposite-End Pointers (O(N) Time)
def pair_sum_optimized(nums, target):
    left = 0
    right = len(nums) - 1
    while left < right:
        current_sum = nums[left] + nums[right]
        if current_sum == target:
            return (left, right)
        elif current_sum < target:
            left += 1
        else:
            right -= 1
    return (-1, -1)


if __name__ == "__main__":
    print("=== Part A: Remove Duplicates Test ===")
    arr1 = [1, 1, 2, 2, 2, 3, 4, 4]
    k = remove_duplicates_optimized(arr1)
    print(f"k = {k}, Unique Prefix: {arr1[:k]}")

    print("\n=== Part B: Pair Sum Test ===")
    arr2 = [1, 2, 4, 7, 11, 15]
    res = pair_sum_optimized(arr2, 15)
    print(f"Target 15 -> Indices: {res}")