# ==========================================
# PART A: Fixed-Size Sliding Window
# ==========================================
class FixedWindow:
    @staticmethod
    def reference_max_sum(a, k):
        n = len(a)
        if k <= 0 or k > n:
            return -1
        max_sum = float('-inf')
        for i in range(n - k + 1):
            current_sum = sum(a[i:i + k])
            if current_sum > max_sum:
                max_sum = current_sum
        return max_sum

    @staticmethod
    def optimized_max_sum(a, k):
        n = len(a)
        if k <= 0 or k > n:
            return -1
        current_sum = sum(a[:k])
        max_sum = current_sum
        for i in range(k, n):
            current_sum += a[i] - a[i - k]
            if current_sum > max_sum:
                max_sum = current_sum
        return max_sum


# ==========================================
# PART B: Variable-Size Sliding Window
# ==========================================
class VariableWindow:
    @staticmethod
    def reference_longest_subarray(a, limit):
        n = len(a)
        max_len = 0
        best_start, best_end = -1, -1
        for i in range(n):
            current_sum = 0
            for j in range(i, n):
                current_sum += a[j]
                if current_sum <= limit:
                    length = j - i + 1
                    if length > max_len:
                        max_len = length
                        best_start = i
                        best_end = j
                else:
                    break
        return max_len, best_start, best_end

    @staticmethod
    def optimized_longest_subarray(a, limit):
        n = len(a)
        max_len = 0
        best_start, best_end = -1, -1
        current_sum = 0
        left = 0

        for right in range(n):
            current_sum += a[right]
            while current_sum > limit and left <= right:
                current_sum -= a[left]
                left += 1
            if current_sum <= limit:
                length = right - left + 1
                if length > max_len:
                    max_len = length
                    best_start = left
                    best_end = right
        return max_len, best_start, best_end


# ==========================================
# Test Runner
# ==========================================
def run_tests():
    print("================ PYTHON ================")
    
    fixed_tests = [
        ([2, 1, 5, 1, 3, 2], 3),
        ([-4, -2, -7], 2),
        ([6], 1),
        ([1, 2, 3], 3)
    ]
    
    for idx, (arr, k) in enumerate(fixed_tests):
        ref = FixedWindow.reference_max_sum(arr, k)
        opt = FixedWindow.optimized_max_sum(arr, k)
        status = "[PASS]" if ref == opt else "[FAIL]"
        print(f"Fixed Test {idx+1} -> Ref: {ref}, Opt: {opt} {status}")

    var_tests = [
        ([1, 2, 1, 1, 3], 4),
        ([5, 1, 1], 2),
        ([4, 2, 1], 0),
        ([0, 0, 1, 0], 1)
    ]

    for idx, (arr, limit) in enumerate(var_tests):
        ref_len, _, _ = VariableWindow.reference_longest_subarray(arr, limit)
        opt_len, _, _ = VariableWindow.optimized_longest_subarray(arr, limit)
        status = "[PASS]" if ref_len == opt_len else "[FAIL]"
        print(f"Var Test {idx+1}   -> Ref Len: {ref_len}, Opt Len: {opt_len} {status}")

if __name__ == "__main__":
    run_tests()
    