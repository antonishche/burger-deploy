#include <fstream>
#include <iostream>

using namespace std;

struct Node {
    int num;
    Node* left;
    Node* right;

    Node(int value) : num(value), left(nullptr), right(nullptr) {}

    bool hasLeft() { return left != nullptr; }
    bool hasRight() { return right != nullptr; }
};

void insert(Node* root, int num);
void printTree(Node* root, ofstream& out);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream in("input.txt");
    int num;
    in >> num;

    Node* root = new Node(num);

    while (in >> num) {
        insert(root, num);
    }

    ofstream out("output.txt");
    printTree(root, out);

    return 0;
}

void insert(Node* root, int num) {
    Node* cur = root;

    bool inserted = false;
    while (!inserted) {
        if (cur == nullptr) {
            cur->num = num;
            break;
        }

        if (num == cur->num) {
            break;
        }

        if (num < cur->num) {
            if (cur->hasLeft()) {
                cur = cur->left;
                continue;
            }

            Node* newNode = new Node(num);
            cur->left = newNode;
            break;
        } else {
            if (cur->hasRight()) {
                cur = cur->right;
                continue;
            }
            Node* newNode = new Node(num);
            cur->right = newNode;
            break;
        }
    }
}

void printTree(Node* root, ofstream& out) {
    if (root == nullptr) return;

    out << root->num << '\n';

    if (root->hasLeft()) {
        printTree(root->left, out);
    }

    if (root->hasRight()) {
        printTree(root->right, out);
    }
}