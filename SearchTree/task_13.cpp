#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Node;

struct End {
    int h, d, val;
    Node* node;
};

struct Node {
    int val;
    Node* left;
    Node* right;
    int depth;
    int height;
    End top[2];
    int count;
    Node(int key, int d) : val(key), depth(d), left(nullptr), right(nullptr), count(0) {}
};

// base
void insert(Node* root, int key);
void collect(vector<Node*>& nodes, Node* root);
int calcHeight(Node* root);
void printTree(Node* root, ofstream& out);
void execute(vector<Node*>& nodes, Node*& root);
void fillTop(vector<Node*>& nodes);
// helpers
Node* getLCA(Node* root, Node* a, Node* b);
void collectPath(Node* lca, int target, vector<int>& keys);
Node* delNode(Node* root, int key);
int getMin(Node* root);
int getMedian(Node* lca, int a, int b);
bool better(const End& a, const End& b);

int main() {
    ios_base::sync_with_stdio(false);
    ifstream in("tst.in");

    int key;
    in >> key;

    Node* root = new Node(key, 0);
    while (in >> key) insert(root, key);

    vector<Node*> nodes;
    collect(nodes, root);

    calcHeight(root);
    fillTop(nodes);

    execute(nodes, root);

    ofstream out("tst.out");
    printTree(root, out);

    return 0;
}

void insert(Node* root, int key) {
    Node* cur = root;
    while (true) {
        if (key == cur->val) return;
        if (key < cur->val) {
            if (cur->left)
                cur = cur->left;
            else {
                cur->left = new Node(key, cur->depth + 1);
                return;
            }
        } else if (key > cur->val) {
            if (cur->right)
                cur = cur->right;
            else {
                cur->right = new Node(key, cur->depth + 1);
                return;
            }
        }
    }
}

void collect(vector<Node*>& nodes, Node* root) {
    if (!root) return;
    nodes.push_back(root);
    collect(nodes, root->left);
    collect(nodes, root->right);
}

int calcHeight(Node* root) {
    if (!root) return -1;
    int lh = calcHeight(root->left);
    int rh = calcHeight(root->right);
    root->height = 1 + max(lh, rh);
    return root->height;
}

void printTree(Node* root, ofstream& out) {
    if (!root) return;
    out << root->val << '\n';
    printTree(root->left, out);
    printTree(root->right, out);
}

Node* getLCA(Node* root, Node* a, Node* b) {
    while (root) {
        if (a->val < root->val && b->val < root->val)
            root = root->left;
        else if (a->val > root->val && b->val > root->val)
            root = root->right;
        else
            return root;
    }
    return nullptr;
}

void execute(vector<Node*>& nodes, Node*& root) {
    if (nodes.size() < 3) return;

    int bestLen = -1;
    long long bestSum = 0;
    Node* bestLCA = nullptr;
    int bestA;
    int bestB;
    bool needToDelete = true;

    for (int i = nodes.size() - 1; i >= 0; i--) {
        Node* v = nodes[i];
        End self = {v->height, v->depth, v->val, v};

        auto consider = [&](const End& a, const End& b) {
            if (a.h == b.h) return;
            int len = a.d + b.d - 2 * v->depth;
            long long sum = (long long)a.val + b.val;

            if (len > bestLen ||
                len == bestLen && sum < bestSum ||
                len == bestLen && sum == bestSum && (bestLCA == nullptr || v->val < bestLCA->val)) {
                bestLen = len;
                bestSum = sum;
                bestLCA = v;
                bestA = a.val;
                bestB = b.val;
                needToDelete = (bestLen + 1) % 2;
            }

            else if (needToDelete && len == bestLen && sum == bestSum && v->val == bestLCA->val) {
                int bestMedian = getMedian(bestLCA, bestA, bestB);
                int median = getMedian(v, a.val, b.val);
                if (median != bestMedian) needToDelete = false;
            }
        };

        if (v->left)
            for (int j = 0; j < v->left->count; j++) consider(self, v->left->top[j]);
        if (v->right)
            for (int j = 0; j < v->right->count; j++) consider(self, v->right->top[j]);
        if (v->left && v->right) {
            for (int jl = 0; jl < v->left->count; jl++)
                for (int jr = 0; jr < v->right->count; jr++)
                    consider(v->left->top[jl], v->right->top[jr]);
        }
    }

    if (bestLCA && needToDelete) {
        int median = getMedian(bestLCA, bestA, bestB);
        root = delNode(root, median);
    }
}

void collectPath(Node* root, int target, vector<int>& keys) {
    while (root) {
        keys.push_back(root->val);
        if (root->val == target) return;

        if (target < root->val) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
}

Node* delNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->val)
        root->left = delNode(root->left, key);
    else if (key > root->val)
        root->right = delNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            int minVal = getMin(root->right);
            root->val = minVal;
            root->right = delNode(root->right, minVal);
        }
    }
    return root;
}

int getMin(Node* root) {
    while (root->left) {
        root = root->left;
    }
    return root->val;
}

int getMedian(Node* lca, int a, int b) {
    vector<int> pathA, pathB;
    collectPath(lca, a, pathA);
    collectPath(lca, b, pathB);

    vector<int> fullPath = pathA;
    for (int i = 1; i < pathB.size(); i++) {
        fullPath.push_back(pathB[i]);
    }

    sort(fullPath.begin(), fullPath.end());
    int median = fullPath[fullPath.size() / 2];
    return median;
}

void fillTop(vector<Node*>& nodes) {
    for (int i = nodes.size() - 1; i >= 0; i--) {
        Node* v = nodes[i];
        Node* L = v->left;
        Node* R = v->right;

        End cand[5];
        int m = 0;
        cand[m++] = {v->height, v->depth, v->val, v};
        if (L)
            for (int i = 0; i < L->count; i++) cand[m++] = L->top[i];
        if (R)
            for (int i = 0; i < R->count; i++) cand[m++] = R->top[i];

        for (int i = 0; i < m; i++)
            for (int j = i; j > 0 && better(cand[j], cand[j - 1]); j--)
                swap(cand[j], cand[j - 1]);

        v->count = 0;
        for (int i = 0; i < m && v->count < 2; i++) {
            if (v->count == 0 || cand[i].h != v->top[0].h) {
                v->top[v->count++] = cand[i];
            }
        }
    }
}

bool better(const End& a, const End& b) {
    if (a.d != b.d) return a.d > b.d;
    return a.val < b.val;
}