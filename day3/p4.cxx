#include <cstddef>
#include <iostream>
#include <span>
#include <unordered_set>

class Solution {
public:
    static size_t type(std::span<std::string> arr)
    {
        std::unordered_set<size_t> types;
        for (auto str : arr) {
            size_t key = 0;
            for (int i = 0; i < str.size(); i++) {
                key |= (1 << (str[i] - 'a'));
            }
            types.emplace(key);
        }
        return types.size();
    }
};