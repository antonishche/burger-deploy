#include <fstream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> arr;
    int count;

   public:
    Solution(int n) {
        arr.resize(n + 1, -1);
        count = n;
    };

    int buildRoad(int u, int v) {
        int U = getParent(u);
        int V = getParent(v);

        if (U != V) {
            if (arr[U] > arr[V]) swap(U, V);
            arr[U] += arr[V];
            arr[V] = U;
            count--;
        }

        return count;
    }

    int getParent(int x) {
        int root = x;
        while (arr[root] > 0) root = arr[root];

        while (x != root) {
            int next = arr[x];
            arr[x] = root;
            x = next;
        }

        return root;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;

    Solution s(n);

    int q;
    in >> q;

    int u, v;
    for (int i = 0; i < q; i++) {
        in >> u >> v;
        out << s.buildRoad(u, v) << '\n';
    }
    return 0;
}