#include <iostream>
#include <queue>

struct Node {
    int data;
    std::vector<Node*> children;
};

void printByLevels(Node* node) {
    if (!node) {
        return;
    }
    std::queue<const Node*> q;
    q.push(node);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            auto curr = q.front();
            q.pop();
            std::cout << curr->data << ' ';
            for (size_t i = 0; i < curr->children.size(); i++)
            {
                q.push(curr->children[i]);
            }
        }
        std::cout << std::endl;
    }
}