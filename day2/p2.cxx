#include <algorithm>
#include <span>

class Solution {
public:
    static int getMinLength(std::span<int> arr)
    {
        if (arr.size() < 2) {
            return 0;
        }
        int min = arr[arr.size() - 1];
        int noMinIndex = -1;
        for (int i = arr.size() - 2; i != -1; i--) {
            if (arr[i] > min) {
                noMinIndex = i; // ✅
            } else {
                min = std::min(min, arr[i]);
            }
        }

        if (noMinIndex == -1) {
            // 如果到了这里，说明：从右到左，一次递增
            // 那就是给整个数组排序了，不是子数组了
            return 0;
        }

        int max = arr[0];
        int noMaxIndex = -1;
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < max) {
                noMaxIndex = i;
            } else {
                max = std::max(max, arr[i]);
            }
        }
        return noMaxIndex - noMinIndex + 1;
    }
};