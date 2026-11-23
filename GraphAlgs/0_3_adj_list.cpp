#include <fstream>
#include <vector>

using namespace std;

class Solution {
   private:
    int n;
    vector<vector<int>> arr;

   public:
    Solution(int n) : n(n), arr(n, vector<int>()) {}

    void insert(int u, int v) {
        arr[u - 1].push_back(v);
        arr[v - 1].push_back(u);
    }

    void print(ofstream& out) {
        for (int i = 0; i < n; i++) {
            out << arr[i].size() << ' ';
            for (int elem : arr[i]) {
                out << elem << ' ';
            }
            out << '\n';
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;

    Solution s(n);

    int m;
    in >> m;

    int u, v;
    for (int i = 0; i < m; i++) {
        in >> u >> v;
        s.insert(u, v);
    }

    s.print(out);
    return 0;
}