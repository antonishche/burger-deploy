#include <fstream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    int n;
    vector<vector<int>> arr;
    vector<int> visited;
    int counter = 1;

   public:
    Solution(int n) : n(n), arr(n, vector<int>(n)), visited(n, 0) {}

    void print(ofstream& out) {
        for (int el : visited) {
            out << el << ' ';
        }
    }

    void fill(ifstream& in) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                in >> arr[i][j];
            }
        }
    }

    void BFS(int start) {
        queue<int> q;

        visited[start] = counter++;
        q.emplace(start);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int i = 0; i < n; i++) {
                if (arr[cur][i] && !visited[i]) {
                    visited[i] = counter++;
                    q.emplace(i);
                }
            }
        }
    }

    void solve() {
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                BFS(i);
            }
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
    s.fill(in);
    s.solve();

    s.print(out);
    return 0;
}