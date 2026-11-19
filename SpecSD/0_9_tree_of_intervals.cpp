#include <climits>
#include <fstream>
#include <vector>

using namespace std;

struct Data {
    long long sum = 0;
    long long mn = 0;
    long long mx = 0;
    long long lazy = 0;
};

class Solution {
   private:
    int n;
    vector<Data> tree;

    void _add(int id, int l, int r, int a, int b, long long v);
    void _set(int id, int l, int r, int pos, long long v);
    long long _getSum(int id, int l, int r, int a, int b);
    long long _getMin(int id, int l, int r, int a, int b);
    long long _getMax(int id, int l, int r, int a, int b);

   public:
    Solution(int n) : n(n), tree(4 * n) {}

    void setValId(int i, long long v);
    void addValDiap(int a, int b, long long v);
    long long getSumDiap(int a, int b);
    long long getMinDiap(int a, int b);
    long long getMaxDiap(int a, int b);

    void patch(int id, int l, int r, long long v) {
        tree[id].sum += v * (r - l + 1);
        tree[id].mn += v;
        tree[id].mx += v;
        tree[id].lazy += v;
    }

    void push(int id, int l, int r) {
        if (tree[id].lazy == 0) return;
        int mid = (l + r) / 2;
        patch(id * 2, l, mid, tree[id].lazy);
        patch(id * 2 + 1, mid + 1, r, tree[id].lazy);
        tree[id].lazy = 0;
    }

    void pull(int id) {
        tree[id].sum = tree[id * 2].sum + tree[id * 2 + 1].sum;
        tree[id].mn = min(tree[id * 2].mn, tree[id * 2 + 1].mn);
        tree[id].mx = max(tree[id * 2].mx, tree[id * 2 + 1].mx);
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;

    Solution s(n);

    int requestType = 42;
    long long v;
    int i, a, b;

    while (requestType != 0) {
        in >> requestType;

        switch (requestType) {
            case 1:
                in >> i >> v;
                s.setValId(i, v);
                break;
            case 2:
                in >> a >> b >> v;
                s.addValDiap(a, b, v);
                break;
            case 3:
                in >> a >> b;
                out << s.getSumDiap(a, b) << '\n';
                break;
            case 4:
                in >> a >> b;
                out << s.getMinDiap(a, b) << '\n';
                break;
            case 5:
                in >> a >> b;
                out << s.getMaxDiap(a, b) << '\n';
                break;
            default:
                break;
        }
    }

    return 0;
}

void Solution::_add(int id, int l, int r, int a, int b, long long v) {
    if (b < l || a > r) return;
    if (a <= l && r <= b) {
        patch(id, l, r, v);
        return;
    }
    push(id, l, r);
    int mid = (l + r) / 2;
    _add(id * 2, l, mid, a, b, v);
    _add(id * 2 + 1, mid + 1, r, a, b, v);
    pull(id);
}

void Solution::_set(int id, int l, int r, int pos, long long v) {
    if (l == r) {
        tree[id].sum = v;
        tree[id].mn = v;
        tree[id].mx = v;
        tree[id].lazy = 0;
        return;
    }
    push(id, l, r);
    int mid = (l + r) / 2;
    if (pos <= mid)
        _set(id * 2, l, mid, pos, v);
    else
        _set(id * 2 + 1, mid + 1, r, pos, v);
    pull(id);
}

long long Solution::_getSum(int id, int l, int r, int a, int b) {
    if (b < l || a > r) return 0;
    if (a <= l && r <= b) return tree[id].sum;
    push(id, l, r);
    int mid = (l + r) / 2;
    return Solution::_getSum(id * 2, l, mid, a, b) + Solution::_getSum(id * 2 + 1, mid + 1, r, a, b);
}

long long Solution::_getMin(int id, int l, int r, int a, int b) {
    if (b < l || a > r) return LLONG_MAX;
    if (a <= l && r <= b) return tree[id].mn;
    push(id, l, r);
    int mid = (l + r) / 2;
    return min(Solution::_getMin(id * 2, l, mid, a, b), Solution::_getMin(id * 2 + 1, mid + 1, r, a, b));
}

long long Solution::_getMax(int id, int l, int r, int a, int b) {
    if (b < l || a > r) return LLONG_MIN;
    if (a <= l && r <= b) return tree[id].mx;
    push(id, l, r);
    int mid = (l + r) / 2;
    return max(Solution::_getMax(id * 2, l, mid, a, b), Solution::_getMax(id * 2 + 1, mid + 1, r, a, b));
}

void Solution::setValId(int i, long long v) {
    Solution::_set(1, 0, n - 1, i, v);
}

void Solution::addValDiap(int a, int b, long long v) {
    Solution::_add(1, 0, n - 1, a, b, v);
}

long long Solution::getSumDiap(int a, int b) {
    return Solution::_getSum(1, 0, n - 1, a, b);
}

long long Solution::getMinDiap(int a, int b) {
    return Solution::_getMin(1, 0, n - 1, a, b);
}

long long Solution::getMaxDiap(int a, int b) {
    return Solution::_getMax(1, 0, n - 1, a, b);
}
