#include <algorithm>
#include <span>

class Solution {
public:
    static int minBoat(std::span<int> arr, int limit)
    {
        if (arr.size() == 0) {
            return 0;
        }
        int N = arr.size();
        std::sort(arr.begin(), arr.end());
        if (arr[N - 1] > limit) {
            return -1;
        }
        int lessR = -1;
        for (int i = N - 1; i >= 0; i--) {
            if (arr[i] <= (limit / 2)) {
                lessR = i;
                break;
            }
        }
        if (lessR == -1) {
            return N;
        }

        int L = lessR;
        int R = lessR + 1;
        int noUsed = 0;

        while (L >= 0) {
            int solved = 0;
            while (R < N && arr[L] + arr[R] <= limit) {
                R++;
                L--;
            }
            if (solved == 0) {
                noUsed++;
                L--;
            } else {
                L = std::max(-1, L - solved);
            }
        }

        int all = lessR + 1;
        int used = all - noUsed;
        int moreUnsolved = (N - all) - used;
        return used + ((noUsed + 1) >> 1) + moreUnsolved;
    }
};