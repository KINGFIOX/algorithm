#include <algorithm>
#include <iostream>
#include <map>
#include <span>
#include <vector>

class Job {
public:
    int money;
    int hard;

    Job(int m, int h)
        : money(m)
        , hard(h)
    {
    }
};

template <typename K, typename V>
K floorKey(const std::map<K, V>& m, K key)
{
    auto it = m.lower_bound(key);
    if (it == m.begin()) {
        if (it->first == key) {
            return key; // 键正好存在
        }
        throw std::runtime_error("No floor key found"); // 没有小于给定键的键
    } else {
        if (it == m.end() || it->first > key) {
            --it; // 如果大于给定键，回退一位
        }
        return it->first; // 返回找到的键
    }
}

class Solution {
public:
    std::vector<int> getMoneys(std::span<Job> job, std::span<int> ability)
    {
        std::sort(job.begin(), job.end(), [](Job a, Job b) {
            return a.hard != b.hard ? (a.hard - b.hard) : (b.money - a.money);
        });

        std::map<int, int> map;
        map.insert(job[0].hard, job[0].money);
        Job pre = job[0];
        // 拍完序以后，难度从小到大，money 从 大 到 小
        // 因此，同样的 hard，就可以直接跳过了；
        // 如果是不同的 hard（那么一定是 job[i].hard > pre.hard 了），
        // 并且只有：后面钱 比 前面的钱多，才插入到 map 中
        for (int i = 1; i < job.size(); i++) {
            if (job[i].hard != pre.hard && job[i].money > pre.money) {
                pre = job[i];
                map.insert(pre.hard, pre.money);
            }
        }

        // 下面就开始 查找了
        std::vector<int> ans(ability.size());

        for (int i = 0; i < ability.size(); i++) {
            try {
                int key = floorKey(map, ability[i]);
                ans[i] = map.at(key);
            } catch (...) {
                ans[i] = 0;
            }
        }

        return ans;
    }
};