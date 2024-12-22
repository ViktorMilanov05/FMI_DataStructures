#include <iostream>

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int data_, Node* left_ = nullptr, Node* right_ = nullptr) :
        data(data_),
        left(left_),
        right(right_) {
    }
};

Node* leftRotation(Node* node) {
    if (!node || !node->right) {
        return nullptr;
    }
    Node* currRight = node->right;
    node->right = currRight->left;
    currRight->left = node;
    return currRight;
}

Node* rightRotation(Node* node) {
    if (!node || !node->left)
        return nullptr;
    Node* currLeft = node->left;
    node->left = currLeft->right;
    currLeft->right = node;
    return currLeft;
}

int main()
{
    Node* example = new Node(2, new Node(1), new Node(3));
    example = leftRotation(example);
    example = rightRotation(example);

    std::cout << example->data << " " << example->left->data << " " << example->right->data;
}

