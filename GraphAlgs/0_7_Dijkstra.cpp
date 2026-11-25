#include <climits>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

using namespace std;
template <typename T>
using MinQ = priority_queue<T, vector<T>, greater<T>>;

class Solution {
   private:
    int n, m;
    vector<map<int, int>> arr;
    vector<char> visited;
    vector<long long> dist;

   public:
    Solution(int n, int m) : n(n), m(m), arr(n), visited(n, 0), dist(n, LONG_LONG_MAX) {}

    void fill(ifstream& in) {
        int u, v, w;

        for (int i = 0; i < m; i++) {
            in >> u >> v >> w;

            u--;
            v--;

            if (arr[u].count(v)) {
                w = min(arr[u][v], w);
            }

            arr[u][v] = w;
            arr[v][u] = w;
        }
    }

    void solve() {
        dist[0] = 0;

        using Pair = pair<long long, int>;
        MinQ<Pair> q;

        q.push({0, 0});

        while (!q.empty()) {
            auto [d, v] = q.top();
            q.pop();

            if (visited[v]) continue;

            visited[v] = 1;

            for (const auto& el : arr[v]) {
                int i = el.first;
                int w = el.second;

                if (!visited[i] && d + w < dist[i]) {
                    dist[i] = d + w;
                    q.push({d + w, i});
                }
            }
        }
    }

    void print(ofstream& out) {
        out << dist[n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    in >> n >> m;

    Solution s(n, m);

    s.fill(in);
    s.solve();
    s.print(out);

    return 0;
}