#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>

class Solution {
public:
    template <int M, int N>
    static int largestBorderedSquare(std::array<std::array<int, M>, N> m) // N * M 的矩阵，外层是 行
    {
        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < M; j++) { // 枚举了 顶点的所有可能
        //         for (int border = 1; border <= std::min(N - i, M - j); border++) { // 枚举所有边长
        //             // 我希望能够验证边框 能不能用的话，这个过程时间复杂度是 O(1)
        //             // 想要知道正方形是否满足：我想要知道任何一个点 (i, j) 右方 下方 是否都是 1，(i + border, j) 右方，(i, j + border) 下方
        //             // 那么我可以先缓存了，缓存的时间复杂度不过是 O(N^2)
        //         }
        //     }
        // }

        std::array<std::array<int, M>, N> right;
        std::array<std::array<int, M>, N> down;
        setBorderMap<M, N>(m, right, down);

        for (int border = std::min(N, M); border != 0; border--) {
            if (hasSizeOfBorder<M, N>(border, m, right, down)) {
                return border * border;
            }
        }

        return 0;
    }

    template <int M, int N>
    static bool hasSizeOfBorder(size_t border, std::array<std::array<int, M>, N>& m,
        std::array<std::array<int, M>, N>& right,
        std::array<std::array<int, M>, N>& down)
    {

        for (int i = 0; i != N - border + 1; i++) {
            for (int j = 0; j != M - border + 1; j++) {
                if (right[i][j] >= border && down[i][j] && right[i + border - 1][j] >= border && down[i][j + border - 1] >= border) {
                    return true;
                }
            }
        }
        return false;
    }

    template <int M, int N>
    static void setBorderMap(std::array<std::array<int, M>, N>& m,
        std::array<std::array<int, M>, N>& right,
        std::array<std::array<int, M>, N>& down)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                right[i][j] = 0;
                down[i][j] = 0;
            }
        }
        int r = N;
        int c = M;
        if (m[r - 1][c - 1] == 1) { // 右下角
            right[r - 1][c - 1] = 1;
            down[r - 1][c - 1] = 1;
        }

        for (int i = r - 2; i != -1; i--) { // 右边界
            if (m[i][c - 1] == 1) {
                right[i][c - 1] = 1;
                down[i][c - 1] = down[i + 1][c - 1] + 1;
            }
        }

        for (int j = c - 2; j != -1; j--) { // 右边界
            if (m[r - 1][j] == 1) {
                down[r - 1][j] = 1;
                right[r - 1][j] = right[r - 1][j + 1] + 1;
            }
        }

        for (int i = r - 2; i != -1; i--) {
            for (int j = c - 2; j != -1; j--) {
                if (m[i][j] == 1) {
                    right[i][j] = right[i][j + 1] + 1;
                    down[i][j] = down[i + 1][j] + 1;
                }
            }
        }
    }
};

int main(void)
{
    std::array<std::array<int, 3>, 3> m = {
        std::array<int, 3> { 1, 1, 1 },
        std::array<int, 3> { 1, 0, 1 },
        std::array<int, 3> { 1, 1, 1 }
    };
    std::cout << Solution::largestBorderedSquare<3, 3>(m) << std::endl;
}