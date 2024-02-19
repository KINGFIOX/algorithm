#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <span>

class Solution {
public:
    static int maxMoney(std::span<std::array<int, 2>> income)
    {
        if (income.size() < 2 || (income.size() & 1) != 0) {
            return 0;
        }

        int N = income.size();
        int M = N >> 1; // 要去 A 区域的人

        return process(income, 0, M);
    }

    /**
     * @brief
     *
     * @tparam ROWS
     * @param income
     * @param index 当前来到了第 index 位司机
     * @param rest 还有几位 去 A 的司机
     * @return int
     */
    static int process(std::span<std::array<int, 2>> income, int index, int rest)
    {
        if (index == income.size()) {
            return 0;
        }

        // 如果剩下 司机的数量，正好等于去 A 的名额 ---> 说明 B 已经满了
        // 剩下的司机都去 A 区域
        if (income.size() - index == rest) {
            int sum = 0;
            for (int i = index; i < income.size(); i++) {
                sum += income[i][0];
            }
            return sum;
        }

        // A 区域没名额了 ---> 都去 B 区域
        if (rest == 0) {
            int sum = 0;
            for (int i = index; i < income.size(); i++) {
                sum += income[i][1];
            }
            return sum;
        }

        // 去 A 区域
        int A = process(income, index + 1, rest - 1) + income[index][0];

        // 去 B 区域
        int B = process(income, index + 1, rest) + income[index][1];

        return std::max(A, B);
    }
};

int main(void)
{
    std::array<std::array<int, 2>, 4> income = {
        std::array<int, 2> { 1, 2 },
        std::array<int, 2> { 3, 4 },
        std::array<int, 2> { 5, 6 },
        std::array<int, 2> { 7, 8 },
    };

    int ans = Solution::maxMoney(income);
    std::cout << ans << std::endl;
}