#include <cstdio>
#include <iostream>
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

        if (tailMap.find(num - 1) != tailMap.end()) {
            tailMap.at(num - 1)->next = cur;
            tailMap.erase(num - 1);
            headMap.erase(num);
        }

        if (headMap.find(num + 1) != headMap.end()) {
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

int main(void)
{
    // MessageBox only receive 1~N
    MessageBox box;
    // 1....
    std::cout << "这是2来到的时候" << std::endl;
    box.receive(2, "B"); // - 2"
    std::cout << "这是1来到的时候" << std::endl;
    box.receive(1, "A"); // 1 2 -> print, trigger is 1
    box.receive(4, "D"); // - 4
    box.receive(5, "E"); // - 4 5
    box.receive(7, "G"); // - 4 5 - 7
    box.receive(8, "H"); // - 4 5 - 7 8
    box.receive(6, "F"); // - 4 5 6 7 8
    box.receive(3, "C"); // 3 4 5 6 7 8 -> print, trigger is 3
    box.receive(9, "I"); // 9 -> print, trigger is 9
    box.receive(10, "J"); // 10 -> print, trigger is 10
    box.receive(12, "L"); // - 12
    box.receive(13, "M"); // - 12 13
    box.receive(11, "K"); // 11 12 13 -> print, trigger is 11
}