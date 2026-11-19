#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    int n, m;
    vector<vector<int>> arr;
    unordered_multimap<int, pair<int, int>> near;
    vector<vector<uint8_t>> used;
    int mainColor = -42;

   public:
    Solution(int n, int m, ifstream& in) : n(n), m(m), arr(n + 2, vector<int>(m + 2, 0)), used(n + 2, vector<uint8_t>(m + 2, 0)) {
        fill(in);

        int startColor = arr[1][1];

        arr[1][1] = -1;
        used[1][1] = 1;

        near.insert({arr[1][2], {1, 2}});
        used[1][2] = 1;

        near.insert({arr[2][1], {2, 1}});
        used[2][1] = 1;

        makemove(startColor);
    }

    void fill(ifstream& in) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                in >> arr[i][j];
    }

    void makemove(int color) {
        if (color == mainColor) return;

        auto it = near.find(color);
        while (it != near.end()) {
            int x = it->second.first;
            int y = it->second.second;

            near.erase(it);
            arr[x][y] = -1;

            vector<pair<int, int>> neighbours{{x - 1, y}, {x + 1, y}, {x, y + 1}, {x, y - 1}};

            for (auto neighbour : neighbours) {
                int nx = neighbour.first;
                int ny = neighbour.second;

                if (!used[nx][ny]) {
                    used[nx][ny] = 1;
                    near.insert({arr[nx][ny], neighbour});
                }
            }

            it = near.find(color);
        }
        mainColor = color;
    }

    void print(ofstream& out) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (arr[i][j] == -1) {
                    out << mainColor << ' ';
                } else {
                    out << arr[i][j] << ' ';
                }
            }
            out << '\n';
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    ifstream in("floodit.in");
    ofstream out("floodit.out");

    int n, m;
    in >> n >> m;

    int k;
    in >> k;

    int t;
    in >> t;

    Solution s(n, m, in);

    int color;
    for (int i = 0; i < t; i++) {
        in >> color;
        s.makemove(color);
    }

    s.print(out);

    return 0;
}