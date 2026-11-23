#include <fstream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> arr;
    int n;

   public:
    Solution(int n) : n(n), arr(n, vector<int>(n, 0)) {}

    void connect(int u, int v) {
        arr[u - 1][v - 1] = 1;
        arr[v - 1][u - 1] = 1;
    }

    void print(ofstream& out) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                out << arr[i][j] << ' ';
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
        s.connect(u, v);
    }

    s.print(out);
    return 0;
}