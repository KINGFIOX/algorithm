#include <cstdio>
#include <iostream>

class Solution {
public:
    static int tableSizeFor(int n)
    {
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        // 因为是 32 位 整数，所以只用 n |= n >> 16;
        // 这里相当于是：最高位一下的所有的位，全部变成 1
        return (n < 0) ? 1 : n + 1;
    }
};

int main(void)
{
    int cap = 120;
    std::cout << Solution::tableSizeFor(cap) << std::endl;
    short int b = -10;
    short int c = b >> 2;
    printf("%x\n%x", b, c);
}