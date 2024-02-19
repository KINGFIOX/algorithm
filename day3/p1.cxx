#include <array>
#include <cstddef>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int v)
    {
        value = v;
    }
};

class Solution {
public:
    /**
     * @brief 递归创建 父结点列表
     *
     * @param cur
     * @param parents
     */
    static void createParentMap(Node* cur, std::unordered_map<Node*, Node*>& parents)
    {
        if (cur == nullptr) {
            return;
        }
        if (cur->left != nullptr) {
            parents.emplace(cur->left, cur);
            createParentMap(cur->left, parents);
        }
        if (cur->right != nullptr) {
            parents.emplace(cur->right, cur);
            createParentMap(cur->right, parents);
        }
    }

    static std::list<Node*> distanceKNodes(Node* root, Node* target, int K)
    {
        std::unordered_map<Node*, Node*> parents;
        parents.emplace(root, nullptr);
        createParentMap(root, parents);

        std::queue<Node*> q;
        std::unordered_set<Node*> visited;
        std::list<Node*> ans;

        q.push(target);
        visited.emplace(target);
        int curLevel = 0;
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
        return ans;
    }
};