# day3

## distanceKNodes

给定三个参数：

二叉树的头节点 head，树上某个节点 target，正数 k 从 target 开始，
可以向上或者向下走。返回与 target 的 距离是 K 的所有节点

我的想法，这题没啥算法，直接递归完事儿了（当然要有父结点的指针），
然后还要保存一个东西：就是上一个位置的坐标，不走回头路。

1. 生成一个 父结点的 map
2. 就变成了一个图的 宽度优先遍历 了（通过一个登记表，来记录是否进入过队列）
3. 距离为 K，那么第 K 层队列，搜集结果就行了

两个点：

1. 生成 parents 的技巧
2. 宽度优先遍历

### coding 技巧：宽度优先 标记层次

获取：一批操作以后，队列的长度。
初始状态，队列的 size 一定是 1。那么我操作 1 次。

![](image/2024-02-19-18-07-21.png)

弹出一次以后，将周围的几点加入队列，加入完毕以后，统计队列大小为 2， 那么下一批只操作 2 次

```cxx
while (!q.empty()) {
	int size = q.size();
	while (size-- > 0) {
		Node* cur = q.front();
		q.pop();
		if (curLevel == K) {
			ans.push_back(cur);
		}
		if (cur->left != nullptr && !visited.contains(cur->left)) {
			visited.emplace(cur->left);
			q.push(cur->left);
		}
		if (cur->right != nullptr && !visited.contains(cur->right)) {
			visited.emplace(cur->right);
			q.push(cur->right);
		}

		// 如果有 父结点，并且父结点没被访问过
		if (parents.contains(cur) && !visited.contains(parents.at(cur))) {
			visited.emplace(parents.at(cur));
			q.push(parents.at(cur));
		}
	}
	curLevel++;
	if (curLevel > K) {
		break;
	}
}
```

##

给定一个数组 arr 代表每个人的能力值。再给定一个非负数 k。
如果两个人的能力差值正好为 k，那么可以哦凑在一起比赛。
一句比赛只有两个人，返回最多可以同时有多少场比赛。

我的想法：遍历 + 二分查找，时间复杂度为 `O(NLogN)`。（错误的，因为是 最多）

暴力解：全排列，然后两个人划分为一组

这题是一个贪心：

1. 先排序
2. 窗口
   - `a - b < k`，R 右移
   - `a - b > K`，L 右移
   - `a - b = k`，比赛，标记比赛过了，同时右移
   - R 到了 最右边，L 右移。如果 `L == R == 最右边`，停止
