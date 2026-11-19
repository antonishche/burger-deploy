#include <fstream>
#include <iostream>

using namespace std;

struct Node {
    int num;
    Node* left;
    Node* right;

    Node(int val) : num(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int num);
Node* deleteNode(Node* root, int num);
void printTree(Node* root, ofstream& out);
Node* getMin(Node* root);

int main() {
    ifstream in("input.txt");

    int keyToDelete;
    in >> keyToDelete;

    Node* root = nullptr;
    int val;
    while (in >> val) {
        root = insert(root, val);
    }

    root = deleteNode(root, keyToDelete);

    ofstream out("output.txt");
    printTree(root, out);

    return 0;
}

Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }

    if (val < root->num) {
        root->left = insert(root->left, val);
    } else if (val > root->num) {
        root->right = insert(root->right, val);
    }

    return root;
}

Node* deleteNode(Node* root, int val) {
    if (root == nullptr) return nullptr;

    if (val > root->num) {
        root->right = deleteNode(root->right, val);
    } else if (val < root->num) {
        root->left = deleteNode(root->left, val);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* min = getMin(root->right);
        root->num = min->num;
        root->right = deleteNode(root->right, min->num);
    }

    return root;
}

Node* getMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

void printTree(Node* root, ofstream& out) {
    if (root == nullptr) return;
    out << root->num << endl;
    printTree(root->left, out);
    printTree(root->right, out);
}
