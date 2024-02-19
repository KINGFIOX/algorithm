#include <algorithm>
#include <array>
#include <string>

class Solution {
public:
    static int lengthOfLongestSubstring(const std::string& str)
    {
        if (str.empty()) {
            return 0;
        }

        std::array<int, 127> map; // 因为 ascii 字符是 0 ~ 127 （这里是 256），这是水桶
        for (int i = 0; i < 127; i++) {
            map[i] = -1;
        }

        int ans = 1; // 至少是 1 了

        int pre = 1; // 这个就是 dp 数组，状态压缩了
                     // 上一个位置向左推了多长

        int cur = 0; // 当前位置，
        map[str[0]] = 0;
        for (int i = 1; i < str.length(); i++) {
            int p1 = i - map[str[i]]; // 我自己最多能推多长，str[17] = a，str[13] = a，那么就是 4（17 16 15 14）
            int p2 = pre + 1; // 比方说：上一个位置最多能推 8，再加上当前位置 这一个元素
            int cur = std::min(p1, p2);
            ans = std::max(ans, cur);
            pre = cur; // 为下一次做准备
            map[str[i]] = i;
        }

        return ans;
    }
};