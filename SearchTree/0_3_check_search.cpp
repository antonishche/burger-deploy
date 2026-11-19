#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

struct James {
    int64_t l;
    int64_t h;
    Node* node;
    James(Node* node, int64_t l, int64_t h) : node(node), l(l), h(h) {}

    bool isBad() {
        return (node->val < l || node->val > h);
    }
};

bool isLegit(Node* root, int64_t min, int64_t max) {
    if (!root) return true;
    vector<James*> bonds;
    bonds.push_back(new James(root, min, max));

    while (!bonds.empty()) {
        James* bond = bonds.back();
        bonds.pop_back();

        if (bond->isBad()) return false;

        if (bond->node->left) {
            bonds.push_back(new James(
                bond->node->left,
                bond->l,
                (int64_t)bond->node->val - 1
            ));
        }
        if (bond->node->right) {
            bonds.push_back(new James(
                bond->node->right,
                (int64_t)bond->node->val,
                bond->h
            ));
        }
    }

    return true;
}

int main() {
    ifstream in("bst.in");

    int n;
    int m;
    int p;
    char c;
    int64_t min = INT_MIN;
    int64_t max = INT_MAX;

    in >> n;
    vector<Node*> tree(n);

    in >> m;
    tree[0] = new Node(m);

    for (int i = 1; i < n; i++) {
        in >> m >> p >> c;

        tree[i] = new Node(m);

        if (c == 'L') {
            tree[p - 1]->left = tree[i];
        } else {
            tree[p - 1]->right = tree[i];
        }
    }

    ofstream out("bst.out");

    if (isLegit(tree[0], min, max)) {
        out << "YES";
    } else {
        out << "NO";
    }

    return 0;
}