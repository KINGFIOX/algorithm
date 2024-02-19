#include <algorithm>
#include <iostream>
#include <span>

class Solution {

    /**
     * @brief 找零
     *
     * @param qian
     * @param zhang
     * @param i 当前第 i 面额的钱
     * @param oneTimeRest
     * @param times
     */
    static void giveRest(std::span<int> qian, std::span<int> zhang, int i, int oneTimeRest, int times)
    {
        for (; i < 3; i++) {
            zhang[i] += (oneTimeRest / qian[i]) * times;
            oneTimeRest = oneTimeRest % qian[i];
        }
    }

    /**
     * @brief
     *
     * @param qian facade
     * @param zhang 还有几张
     * @param rest 传入还要多少钱才能 购买完整的一瓶
     * @return int 返回：用了几张钱
     */
    static int buy(std::span<int> qian, std::span<int> zhang, int rest)
    {
        int first = -1; // 找到第一张 没有用完的 面额
        for (int i = 0; i < 3; i++) {
            if (qian[i] != 0) {
                first = i;
                break;
            }
        }
        if (first == -1) {
            return -1; // 如果都没钱了，那么返回 -1，程序即将结束
        }
        if (qian[first] >= rest) {
            zhang[first]--; // 可以买了
            giveRest(qian, zhang, first + 1, qian[first] - rest, 1); // 全款买下，找零
                                                                     // 肯定是 i + 1 号面额的找钱，不然这次投币没啥意义
            return 1;
        } else {
            zhang[first]--; // 还不够买一瓶，继续投钱
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
     * @param a * @param b * @param c
     * @param x 可乐的价钱
     * @return int 用了几张钱
     */
    static int right(int m, int a, int b, int c, int x)
    {
        int qian[] = { 100, 500, 10 };
        int zhang[] = { c, b, a };

        int puts = 0; // 用了几张钱

        while (m != 0) {
            int cur = buy(qian, zhang, x); // 购买一次
            if (cur == -1) {
                return -1;
            }
            puts += cur;
            m--;
        }
        return puts;
    }

    /**
     * @brief 优化解
     *
     * @param m
     * @param a * @param b * @param c
     * @param x
     * @return int
     */
    static int putTimes(int m, int a, int b, int c, int x)
    {
        int qian[] = { 100, 500, 10 };
        int zhang[] = { c, b, a };

        int puts = 0; // 用了几张钱

        int preQianRest = 0; // 之前面值的钱 还剩下 多少总数
        int preQianZhang = 0; // 之前面值的钱，还剩下多少张总数的

        for (int i = 0; i < 3 && m != 0; i++) {
            // (x - preQianZhang) / qian[i] 可能会凑出一瓶可乐
            // (x - preQianZhang + qian[i] - 1) 这后面的是一个 coding 处理 ---> 向上取整，因为只有向上取整的才能购买
            // TODO coding 技巧：(m + x - 1) / x ，加上一个 除数 - 1，就是向上取整
            int curQianFirstBuyZhang = (x - preQianZhang + qian[i] - 1) / qian[i];
            if (zhang[i] > curQianFirstBuyZhang) {
                // 买了一瓶，肯定是用 下一个面额来找钱的
                giveRest(qian, zhang, i + 1, (qian[i] * curQianFirstBuyZhang) - x, 1);
                // 全款拿下！！!
                puts += curQianFirstBuyZhang + preQianRest;
                zhang[i] -= curQianFirstBuyZhang;
                m--;
            } else {
                // 历史信息 + 当前面值的所有的钱，都解决不了一瓶 cola
                // 历史信息 = 历史信息 + 当前面值所有的钱 ---> 跳到下一个面值，处理你的烂摊子
                preQianRest += qian[i] * zhang[i];
                preQianZhang += zhang[i];
                continue;
            }

            /**
             * 买了第一瓶了，第一瓶是特殊的，因为可能含有 上一个面值导致的历史信息。
             * 下面看看，就用当前的 面额，看看能够买几瓶可乐
             */

            // 向上取整 （边界处理）
            // 看看，买一瓶可乐，需要多少张 当前面额的钱
            int curQianBuyOneColaZhang = (x + qian[i] - 1) / qian[i];

            // 看看一共可以买几瓶 可乐呢 （又是边界处理）
            int curQianBuyColas = std::min(zhang[i] / curQianFirstBuyZhang, m);

            // 每用 当前面额搞定一瓶可乐，会吐出多少零钱（零钱总价钱）
            int oneTimeRest = qian[i] * curQianBuyOneColaZhang - x;

            // 买出一瓶可乐，需要找一次钱
            giveRest(qian, zhang, i + 1, oneTimeRest, curQianBuyColas);

            // 投了几次币 += 买了几瓶可乐 + 每买一瓶可乐需要几张 当前面额的钱
            puts += curQianBuyColas * curQianBuyOneColaZhang;

            // 还需要买几瓶可乐
            m -= curQianBuyColas;

            // 剩下的当前面额的张数，不足以支撑 再买一瓶可乐 ---> 一股脑塞进去，称为历史a信息
            zhang[i] -= curQianBuyColas * curQianBuyOneColaZhang;

            preQianZhang = qian[i] * zhang[i];
            preQianZhang = zhang[i];
            zhang[i] = 0; // 这个可有可无
        }

        // m 能买完吗？
        // 买完了 ---> 返回 puts
        // 买不完 ---> -1 错误
        return m == 0 ? puts : -1;
    }
};

int main(void)
{
}
