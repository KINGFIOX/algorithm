#include <cstdlib>
#include <iostream>
#include <vector>

#include "Right.hxx"`
#include "SegmentTree.hxx"

bool test(int len = 100, int max = 1000, int testTimes = 1000, int AddUpdateTimes = 1000, int queryTimes = 500)
{
    auto genRandArr = [](int len, int max) {
        int size = random() % len + 1;
        std::vector<int> v(size);
        for (int i = 0; i < size; i++) {
            v[i] = random() % max;
        }
        return v;
    };

    int ErrCNT = 0; // 执行错误的次数

    for (int i = 0; i < testTimes; i++) {
        std::vector<int> origin = genRandArr(len, max);
        int size = origin.size();
        SegmentTree* s = new SegmentTree(origin);
        Right* r = new Right(origin);
        for (int j = 0; j < AddUpdateTimes; j++) {
            int L = 0;
            int R = -1;
            while (R < L) {
                L = random() % size;
                R = random() % size;
            }
            int C = random() % max;
            int action = random() % 2;
            if (action) {
                s->add(L, R, C);
                r->add(L, R, C);
            } else {
                s->update(L, R, C);
                r->update(L, R, C);
            }
        }

        int e = 0; // 查询错误的次数

        for (int j = 0; j < random() % queryTimes; j++) {
            int e = 0;
            int L = 0;
            int R = -1;
            while (R < L) {
                L = random() % size;
                R = random() % size;
            }
            long res1 = s->query(L, R);
            long res2 = s->query(L, R);
            if (res1 != res2) {
                e++;
            }
        }
        if (e != 0) {
            ErrCNT++;
        }
    }
    if (ErrCNT != 0) {
        return false;
    } else {
        return true;
    }
}

int main(void)
{
    bool correct = test();
    std::cout << correct << std::endl;
}