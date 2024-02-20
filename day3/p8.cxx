#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <unordered_map>
class Solution {
public:
    static int dial(int i1, int i2, int size)
    {
        // 自己推下标变化去
        return std::min(std::abs(i1 - i2), std::min(i1, i2) + size - std::max(i1, i2));
    }

    /**
     * @brief 直接递归
     *
     * @param preButton 指针指向上一个按键
     * @param keyIndex 此时目标要搞定哪一个字符
     * @param str 要搞定的字符串
     * @param map 每种字符 在那些位置 * @param N 电话机的大小 ---> 这两个参数搞定了：表盘
     * @return int
     */
    static int process(int preButton, int keyIndex, std::string& str, std::unordered_map<char, std::list<int>>& map, int N)
    {
        if (keyIndex == str.size()) { // base case ，结束了
            return 0;
        }

        // 还有字符需要搞定
        char cur = str[keyIndex];
        std::list<int> nextPositions = map.at(cur);

        int ans = INT_MAX;
        for (int next : nextPositions) {
            int cost = dial(preButton, next, N) + 1 + process(next, keyIndex + 1, str, map, N);
            ans = std::min(ans, cost);
        }

        return ans;
    }

    static int findRotateSteps(std::string r, std::string k)
    {
        int N = r.size();
        std::unordered_map<char, std::list<int>> map;
        for (int i = 0; i < N; i++) {
            if (!map.contains(r[i])) {
                map.emplace(r[i], std::list<int>());
            }
            map.at(r[i]).push_back(i);
        }
        return process(0, 0, k, map, N);
    }
};