#include <iostream>

class Solution {
public:
    static int minStep(std::string s)
    {
        if (s.empty() || s == "") {
            return 0;
        }
        const char* str = s.c_str();

        /* 看 G */
        int step1 = 0;
        int gi = 0;
        for (int i = 0; i < s.size(); i++) {
            if (str[i] == 'G') {
                step1 += i - gi;
                gi++;
            }
        }

        /* 看 B */
        int step2 = 0;
        int bi = 0;
        for (int i = 0; i < s.size(); i++) {
            if (str[i] == 'B') {
                step2 += i - bi;
                bi++;
            }
        }

        return std::min(step1, step2);
    }
};