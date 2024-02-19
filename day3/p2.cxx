#include <algorithm>
#include <span>

class Solution2 {
public:
    static int maxPairNum(std::span<int> arr, int k)
    {
        if (k < 0 || arr.size() < 2) {
            return 0;
        }
        std::sort(arr.begin(), arr.end());
        int ans = 0;
        int N = arr.size();
        int L = 0;
        int R = 0;
        bool* usedR = new bool[N];
        while (L < N && R < N) {
            if (usedR[L]) {
                L++;
            } else if (L >= R) {
                R++; // 不能和自己 打
            } else {
                int distance = arr[R] - arr[L];
                if (distance == k) {
                    ans++;
                    usedR[R++] = true;
                    L++;
                } else if (distance < k) {
                    R++;
                } else {
                    L++;
                }
            }
        }
    }
};