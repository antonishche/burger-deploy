#include <fstream>
#include <set>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> arr;
    int count;

   public:
    Solution(int n) {
        this->arr.resize(n + 1, -1);
        count = n;
    }

    int getCount() {
        return this->count;
    }

    void buildRoad(int u, int v) {
        int U = getParent(u);
        int V = getParent(v);

        if (U != V) {
            if (arr[U] > arr[V]) swap(U, V);
            arr[U] += arr[V];
            arr[V] = U;
            count--;
        }
    }

    int getParent(int x) {
        int root = x;

        while (arr[root] > 0) {
            root = arr[root];
        }

        while (x != root) {
            int next = arr[x];
            arr[x] = root;
            x = next;
        }

        return root;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;
    Solution s(n);

    int m, q;
    in >> m >> q;

    vector<pair<int, int>> roads(m + 1);
    int u, v;
    for (int i = 1; i <= m; i++) {
        in >> u >> v;
        roads[i] = {u, v};
    }

    vector<int> destroyedNumbers(q);
    set<int> destroyedNumbersSet;
    int id;
    for (int i = 0; i < q; i++) {
        in >> id;
        destroyedNumbers[i] = id;
        destroyedNumbersSet.insert(id);
    }

    for (int i = 1; i < roads.size(); i++) {
        if (destroyedNumbersSet.count(i) == 0) {
            s.buildRoad(roads[i].first, roads[i].second);

            if (s.getCount() == 1) {
                for (int i = 0; i < q; i++) out << 1;
                return 0;
            }
        }
    }

    for (int i = q - 1; i >= 0; i--) {
        int road_id = destroyedNumbers[i];
        s.buildRoad(roads[road_id].first, roads[road_id].second);

        if (s.getCount() == 1) {
            int j = 0;
            while (j < i) {
                out << 1;
                j++;
            }
            while (j < q) {
                out << 0;
                j++;
            }
            return 0;
        }
    }

    for (int i = 0; i < q; i++) out << 0;
    return 0;
}