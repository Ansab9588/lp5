#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

// Node structure for the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Function to create a new node
Node* createNode(int value) {
    return new Node(value);
}

// Function to insert a new node into the binary tree
void insertNode(Node*& root, int value) {
    if (root == nullptr) {
        root = createNode(value);
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->left == nullptr) {
            temp->left = createNode(value);
            return;
        } else {
            q.push(temp->left);
        }

        if (temp->right == nullptr) {
            temp->right = createNode(value);
            return;
        } else {
            q.push(temp->right);
        }
    }
}

// Parallel BFS on a binary tree
void parallelBFS(Node* root) {
    if (root == nullptr)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                while (!q.empty()) {
                    Node* current = q.front();
                    q.pop();
                    cout << current->data << " ";

                    if (current->left != nullptr)
                        q.push(current->left);

                    if (current->right != nullptr)
                        q.push(current->right);
                }
            }
        }
    }
}

int main() {
    Node* root = createNode(1);
    insertNode(root, 2);
    insertNode(root, 3);
    insertNode(root, 4);
    insertNode(root, 5);
    insertNode(root->left, 6);
    insertNode(root->left, 7);

    cout << "Parallel BFS traversal: ";
    parallelBFS(root);
    cout << endl;

    return 0;
}
