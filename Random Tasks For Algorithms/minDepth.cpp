#include <iostream>
#include <queue>

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}
};

int minDepth(Node* node) {
    if (!node) {
        return 0;
    }
    int minDepth = 0;
    std::queue<Node*> s;
    s.push(node);

    while (!s.empty()) {
        int size = s.size();
        minDepth++;
        while (size--) {
            Node* curr = s.front();
            s.pop();
            if (curr->left) {
                s.push(curr->left);
            }
            if (curr->right) {
                s.push(curr->right);
            }
            if (!curr->left && !curr->right) {
                return minDepth;
            }
        }
    }
}