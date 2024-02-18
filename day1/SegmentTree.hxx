#ifndef __SegmentTree_HXX__
#define __SegmentTree_HXX__

#include <memory>
#include <span>

class SegmentTree {
private:
    // int* arr;
    // int* sum;
    // int* lazy;
    // int* change;
    // bool* is_update;
    std::unique_ptr<int[]> arr;
    std::unique_ptr<int[]> sum;
    std::unique_ptr<int[]> lazy;
    std::unique_ptr<int[]> change;
    std::unique_ptr<bool[]> is_update;
    size_t boundLeft;
    size_t boundRight;
    size_t treeRoot;

public:
    SegmentTree(std::span<int> origin)
        // : arr(new int[origin.size() + 1]) // 原序列的信息，下标从 1 开始
        // , sum(new int[(origin.size() + 1) << 2]) // 累加和数组
        // , lazy(new int[(origin.size() + 1) << 2]) // 懒数组
        // , change(new int[(origin.size() + 1) << 2]) // 一个范围上，所有的东西被更新成了 xxx
        // , is_update(new bool[(origin.size() + 1) << 2]) // 就是 change=0，意味着：是变成了 0，还是不 change
        : arr(std::make_unique<int[]>(origin.size() + 1))
        , sum(std::make_unique<int[]>((origin.size() + 1) << 2))
        , lazy(std::make_unique<int[]>((origin.size() + 1) << 2))
        , change(std::make_unique<int[]>((origin.size() + 1) << 2))
        , is_update(std::make_unique<bool[]>((origin.size() + 1) << 2))
        , boundLeft(1)
        , boundRight(origin.size())
        , treeRoot(1)
    {
        for (size_t i = 1; i < origin.size() + 1; i++) {
            arr[i] = origin[i - 1];
        }
        _build(1, origin.size(), 1);
    }

    ~SegmentTree()
    {
    }

private:
    /**
     * @brief 左孩子 + 右孩子
     *
     * @param rt root
     */
    inline void _pushUp(size_t rt)
    {
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    }

    /**
     * @brief
     *
     * @param root 当前节点是 root
     * @param ln 左孩子上有几个数
     * @param rn 右 ~
     */
    inline void _pushDown(size_t root, size_t ln, size_t rn)
    {
        if (is_update[root]) {
            is_update[root << 1] = true;
            is_update[root << 1 | 1] = true;
            change[root << 1] = change[root];
            change[root << 1 | 1] = change[root];
            lazy[root << 1] = 0;
            lazy[root << 1 | 1] = 0;
            sum[root << 1] = change[root] * static_cast<int>(ln);
            sum[root << 1 | 1] = change[root] * static_cast<int>(rn);
            is_update[root] = false;
        }
        // 向下分发，只分发一层
        if (lazy[root] != 0) {
            lazy[root << 1] += lazy[root]; // 左孩子的 懒信息 加上我自己的
            sum[root << 1] += lazy[root] * static_cast<int>(ln);
            lazy[root << 1 | 1] += lazy[root]; // 右 ～
            sum[root << 1 | 1] += lazy[root] * static_cast<int>(rn);
            lazy[root] = 0; // 左右孩子 接住了，可以就可以清空当前节点了
        }
    }

    /**
     * @brief 构建 线段树
     *
     * @param l
     * @param r
     * @param rt
     */
    void _build(size_t left, size_t right, int root)
    {
        if (left == right) {
            sum[root] = arr[left];
            return;
        }
        size_t mid = left + ((right - left) >> 1);
        _build(left, mid, root << 1); // 构建 left
        _build(mid + 1, right, root << 1 | 1); // 构建 right
        _pushUp(root); // 后序遍历，构建 线段树
    }

    /**
     * @brief
     *
     * @param L * @param R * @param C 表示 接受的任务
     * @param left * @param right // 当前格子 是 哪一个范围
     * @param root  // 当前来到了哪一个格子
     */
    void _add(size_t L, size_t R, int C, size_t left, size_t right, size_t root)
    {
        // 任务已经 把当前格子 全包了
        if (L <= left && right <= R) {
            sum[root] += C * static_cast<int>(right - left + 1);
            lazy[root] += C; // 合并 懒更新
            return;
        }

        // 任务没有把当前格子全包（没有揽住），那么就向下分发

        size_t mid = left + ((right - left) >> 1);

        _pushDown(root, mid - left + 1, right - mid); // 懒更新 向下分发一层

        // 左孩子 是否 接受 任务
        if (L <= mid) {
            _add(L, R, C, left, mid, root << 1);
        }

        // 右孩子是否接受任务
        if (R > mid) {
            _add(L, R, C, mid + 1, right, root << 1 | 1);
        }

        // 左边的累加和调整对了，右边的累加和调整对了 ---> 调整自己的累加和
        _pushUp(root);
    }

    /**
     * @brief
     *
     * @param L * @param R * @param C
     * @param left * @param right
     * @param root
     */
    void _update(size_t L, size_t R, int C, size_t left, size_t right, size_t root)
    {
        // 包住了
        if (L <= left && right <= R) {
            is_update[root] = true;
            change[root] = C;
            sum[root] = C * static_cast<int>(right - left + 1);
            lazy[root] = 0; // 清空之前的 揽
            return;
        }

        size_t mid = left + ((right - left) >> 1);

        // 如果 不能全保住，那么就是得往下分发了
        // 这里 既会 分发：更新，也会分发 累加
        _pushDown(root, mid - left + 1, right - mid);

        if (L <= mid) {
            _update(L, R, C, left, mid, root << 1);
        }

        if (R > mid) {
            _update(L, R, C, mid + 1, right, root << 1 | 1);
        }

        _pushUp(root);
    }

    /**
     * @brief 查询这段 L~R 这段范围的 和
     *
     * @param L * @param R
     * @param left * @param right
     * @param root
     * @return int
     */
    long _query(size_t L, size_t R, size_t left, size_t right, size_t root)
    {
        if (L <= left && right <= R) {
            return sum[root];
        }

        size_t mid = left + ((right - left) >> 1);

        _pushDown(root, mid - left + 1, right - mid);

        long ans = 0;
        if (L <= mid) {
            ans += _query(L, R, left, mid, root << 1);
        }
        if (R > mid) {
            ans += _query(L, R, mid + 1, right, root << 1 | 1);
        }
        return ans;
    }

public:
    void add(size_t L, size_t R, int C)
    {
        _add(L + 1, R + 1, C, boundLeft, boundRight, treeRoot);
    }

    void update(size_t L, size_t R, int C)
    {
        _update(L + 1, R + 1, C, boundLeft, boundRight, treeRoot);
    }

    long query(size_t L, size_t R)
    {
        return _query(L + 1, R + 1, boundLeft, boundRight, treeRoot);
    }
};

#endif // __SegmentTree_HXX__