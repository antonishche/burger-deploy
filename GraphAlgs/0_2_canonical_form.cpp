#include <fstream>
#include <vector>

using namespace std;

class Solution {
   private:
    int n;
    vector<int> arr;

   public:
    Solution(int n) : n(n), arr(n, 0) {}

    void connect(int u, int v) {
        arr[v - 1] = u;
    }

    void print(ofstream& out) {
        for (int el : arr) {
            out << el << ' ';
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

    int u, v;
    for (int i = 1; i < n; i++) {
        in >> u >> v;
        s.connect(u, v);
    }

    s.print(out);
    return 0;
}