#include <cstdio>
#include <string>
#include <unordered_map>
#include <utility>

class Node {
public:
    std::string info;
    Node* next;
    Node(std::string str)
        : next(NULL)
    {
        info = str;
    }
};

class MessageBox {
private:
    std::unordered_map<int, Node*> headMap;
    std::unordered_map<int, Node*> tailMap;
    int waitPoint;

public:
    MessageBox()
        : waitPoint(1)
    {
    }

    void receive(int num, std::string info)
    {
        if (num < 1) {
            return;
        }
        Node* cur = new Node(info);
        headMap.insert(std::make_pair(num, cur));
        tailMap.insert(std::make_pair(num, cur));

        if (tailMap.contains(num - 1)) {
            tailMap.at(num - 1)->next = cur;
            tailMap.erase(num - 1);
            headMap.erase(num);
        }

        if (headMap.contains(num + 1)) {
            cur->next = headMap.at(num + 1);
            tailMap.erase(num);
            headMap.erase(num + 1);
        }

        if (num == waitPoint) {
            print();
        }
    }

private:
    void print()
    {
        Node* node = headMap.at(waitPoint);
        headMap.erase(waitPoint);
        while (node != NULL) {
            printf("%s ", node->info.c_str());

            Node* tmp = node;
            node = node->next;
            delete tmp;

            waitPoint++;
        }
        tailMap.erase(waitPoint - 1);
        printf("\n");
    }
};