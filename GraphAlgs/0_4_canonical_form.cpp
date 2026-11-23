#include <fstream>
#include <vector>

using namespace std;

class Solution {
   private:
    int n;
    vector<int> arr;

   public:
    Solution(int n) : n(n), arr(n, 0) {}

    void insert(int u, int v) {
        // u -> v
        arr[v] = u + 1;
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

    int pos;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> pos;
            if (pos) {
                s.insert(i, j);
            }
        }
    }

    s.print(out);
    return 0;
}