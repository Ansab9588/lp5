#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <omp.h>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

class Node{
    public:
    int key;
    Node *left;
    Node *right;

    Node(int k){

        key = k;
        left=right=NULL;
    }
};



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
                    cout << current->key << " ";

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

    Node *root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);

    std::cout << "Parallel BFS traversal: ";
    auto start = high_resolution_clock::now();
    parallelBFS(root);
    std::cout << std::endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
    cout << "Parallel BFS Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;

    return 0;
}
