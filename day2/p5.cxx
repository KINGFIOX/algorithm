#include <iostream>
#include <span>

void giveRest(std::span<int> qian, std::span<int> zhang, int i, int oneTimeRest, int times)
{
    for (; i < 3; i++) {
        zhang[i] += (oneTimeRest / qian[i]) * times;
        oneTimeRest = oneTimeRest % qian[i];
    }
}

int buy(std::span<int> qian, std::span<int> zhang, int rest)
{
    int first = -1;
    for (int i = 0; i < 3; i++) {
        if (qian[i] != 0) {
            first = i;
            break;
        }
    }
    if (first == -1) {
        return -1;
    }
    if (qian[first] >= rest) {
        zhang[first]--;
        giveRest(qian, zhang, first + 1, qian[first] - rest, 1);
        return 1;
    } else {
        zhang[first]--;
        int next = buy(qian, zhang, rest - qian[first]);
        if (next == -1) {
            return -1;
        }
        return 1 + next;
    }
}

/**
 * @brief 暴力解
 *
 * @param m 需要购买的可乐数量
 * @param a
 * @param b
 * @param c
 * @param x
 * @return int
 */
int right(int m, int a, int b, int c, int x)
{
    int qian[] = { 100, 500, 10 };
    int zhang[] = { c, b, a };
    int puts = 0;
    while (m != 0) {
        int cur = buy(qian, zhang, x);
        if (cur == -1) {
            return -1;
        }
        puts += cur;
        m--;
    }
    return puts;
}