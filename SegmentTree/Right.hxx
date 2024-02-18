#ifndef __RIGHT_HXX__
#define __RIGHT_HXX__

#include <memory>
#include <span>

class Right {
public:
    std::unique_ptr<int[]> arr;

    Right(std::span<int> origin)
        : arr(std::make_unique<int[]>(origin.size()))
    {
        for (int i = 0; i < origin.size(); i++) {
            arr[i] = origin[i];
        }
    }

    void update(size_t L, size_t R, int C)
    {
        for (size_t i = L; i <= R; ++i) {
            arr[i] = C;
        }
    }

    void add(size_t L, size_t R, int C)
    {
        for (size_t i = L; i <= R; ++i) {
            arr[i] += C;
        }
    }

    long query(size_t L, size_t R)
    {
        long ans = 0;
        for (size_t i = L; i <= R; ++i) {
            ans += arr[i];
        }
        return ans;
    }
};

#endif // __RIGHT_HXX__