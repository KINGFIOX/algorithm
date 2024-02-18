#include <algorithm>
#include <iostream>
#include <span>

#if 0

class Solution {
public:
    static int maxPoint(std::span<int> arr, int L)
    {
        int res = 1;
        for (int i = 0; i < arr.size(); i++) {
            // arr[i] - L 表示： 绳子的右端放到 第 i 个点上，绳子左端能达到的距离
            // 看 最接近 value 的右边那个点的下标
            int nearest = nearestIndex(arr, i, arr[i] - L);
            res = std::max(res, i - nearest + 1); // 计算中间有多少个点，植树问题
        }
        return res;
    }

    static int nearestIndex(std::span<int> arr, int R, int value)
    {
        int L = 0;
        int index = R;
        while (L <= R) {
            int mid = L + ((R - L) >> 1);
            if (arr[mid] >= value) {
                index = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        return index;
    }
};

#else

class Solution {
public:
    static int maxPoint(std::span<int> arr, int L)
    {
        int left = 0;
        int right = 0;
        int N = arr.size();
        int max = 0;
        while (left < N) {
            while (right < N && arr[right] - arr[left] <= L) {
                // 1. 还能往右加
                // 2. 绳子还够长
                right++;
            }
            max = std::max(max, right - left);
            left++;
        }
        return max;
    }
};

#endif