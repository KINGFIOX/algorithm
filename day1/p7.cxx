#include "SegmentTree.hxx"

#include <cstddef>
#include <iostream>
#include <span>
#include <vector>

class Solution {
public:
    static int minAoe(std::span<int> x, std::span<int> hp, int range)
    {
        size_t n = x.size();
        std::vector<int> cover(n);

        int r = 0;

        // i 是 技能的左侧
        // r 是 技能的最右侧
        // cover 是 放技能的点
        for (int i = 0; i < n; i++) {
            while (r < n && x[r] - x[i] <= range) {
                r++;
            }
            cover[i] = r - 1;
        }

        SegmentTree* st = new SegmentTree(hp);

        int ans = 0;

        for (int i = 1; i <= n; i++) {
            int leftHP = st->query(i, i); // 获取：最左侧 怪物的血量
            if (leftHP > 0) {
                ans += leftHP;
                st->add(i, cover[i - 1] + 1, -leftHP);
            }
        }

        return ans;
    }
};