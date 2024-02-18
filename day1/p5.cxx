#include <iostream>
#include <memory>
#include <span>
#include <unordered_map>
#include <valarray>
#include <vector>

#if 0

class Solution {
public:
    static int findTargetSumWays(std::span<int> arr, int s)
    {
        return process1(arr, 0, s);
    }

    // 可以自由使用 arr[index...] 所有的数字
    // 搞出 rest 这个数，方法数有多少种，返回
    static int process1(std::span<int> arr, int index, int rest)
    {
        if (index == arr.size()) { // base case：没有数了
            return rest == 0 ? 1 : 0;
        }

        // 还有数
        return process1(arr, index + 1, rest - arr[index]) + process1(arr, index + 1, rest + arr[index]);
    }
};

#endif

#if 1

class Solution {
public:
    static int findTargetSumWays(std::span<int> arr, int s)
    {
        std::unordered_map<int, std::unordered_map<int, int>> dp;
        return process2(arr, 0, s, dp);
    }

    static int process2(std::span<int> arr, int index, int rest, std::unordered_map<int, std::unordered_map<int, int>> dp)
    {
        if (dp.contains(index) && dp.at(index).contains(rest)) {
            return dp[index][rest];
        }
        int ans = 0;
        if (index == arr.size()) {
            ans = rest == 0 ? 1 : 0;
        } else {
            ans = process2(arr, index + 1, rest - arr[index], dp) + process2(arr, index + 1, rest + arr[index], dp);
        }
        /* 塞入 缓存中 */
        dp[index][rest] = ans;
        return ans;
    }
};

#endif

#if 0

class Solution {
public:
    static int findTargetSumWays(std::span<int> arr, int target)
    {
        int sum = 0;
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = std::abs(arr[i]);
            sum += arr[i];
        }
        return std::abs(sum) < std::abs(target) || ((target & 1) ^ (sum & 1)) != 0 ? 0 : subset(arr, (target + sum) >> 1);
    }

    static int subset(std::span<int> nums, int s)
    {
        std::vector<int> dp(s + 1);
        dp[0] = 1;
        for (int n : nums) {
            for (int i = s; i >= n; i--) { // 从右往左，0/1 背包问题
                dp[i] += dp[i - n];
            }
        }
        return dp[s];
    }
};

#endif

int main(void)
{
    // int nums[] = { 1, 1, 1, 1, 1 };
    // int target = 3;
    int nums[] = { 100 };
    int target = -200;
    std::cout << Solution::findTargetSumWays(nums, target) << std::endl;
}