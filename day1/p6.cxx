#include <algorithm>
#include <array>
#include <iostream>
#include <span>
#include <vector>

class Solution {
public:
    static int longestIncreasingPath(std::vector<std::vector<int>> m)
    {
        if (m.empty() || m.size() == 0 || m[0].size() == 0) {
            return 0;
        }

        // int** dp = new int*[m.size()];
        // for (int i = 0; i < m.size(); i++) {
        //     dp[i] = new int[m[0].size()];
        // }

        int ans = 0;

        size_t N = m.size();
        size_t M = m[0].size();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ans = std::max(ans, process(m, i, j));
            }
        }

        return ans;
    }

    // 从 m[i][j] 开始走，走出来的最长递增链，返回
    static int process(std::vector<std::vector<int>> m, size_t i, size_t j)
    {
        // if (i < 0 || i == m.size() || j < 0 || j == m[0].size()) { // base case，越界位置
        //     return 0;
        // }
        // 因为我下面，已经判断是不是 越界位置了，所以上面的 base case 已经不会进去了

        // (i, j) 不越界

        int up = i > 0 && m[i][j] < m[i - 1][j] ? process(m, i - 1, j) : 0;
        int down = i < m.size() - 1 && m[i][j] < m[i + 1][j] ? process(m, i + 1, j) : 0;
        int left = j > 0 && m[i][j] < m[i][j - 1] ? process(m, i, j - 1) : 0;
        int right = j < m[0].size() - 1 && m[i][j] < m[i][j + 1] ? process(m, i, j + 1) : 0;

        return std::max(std::max(up, down), std::max(left, right)) + 1;
    }
};

int main(void)
{
    std::vector<std::vector<int>> m = { { 9, 9, 4 }, { 6, 6, 8 }, { 2, 1, 1 } };
    // 讲真，这种方法真不优雅
    std::cout << Solution::longestIncreasingPath(m) << std::endl;
}