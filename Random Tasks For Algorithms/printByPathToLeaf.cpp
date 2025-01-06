#include <iostream>
#include <queue>

struct Node {
    int data;
    std::vector<Node*> children;
};

void print(Node* node, std::string& str) {
    if (!node) {
        return;
    }
    str.push_back(node->data);
    if (node->children.empty()) {
        std::cout << str << std::endl;
    }
    else {
        for (size_t i = 0; i < node->children.size(); i++)
        {
            print(node->children[i], str);
        }
    }
    str.pop_back();
}

int main() {
    Node* root = new Node{ 'a' };

    root->children.push_back(new Node{ 'b' });
    root->children.push_back(new Node{ 'c' });
    root->children.push_back(new Node{ 'd' });
    root->children.at(0)->children.push_back(new Node{ 'x' });
    root->children.at(0)->children.push_back(new Node{ 'y' });

    std::string str;
    print(root, str);
}