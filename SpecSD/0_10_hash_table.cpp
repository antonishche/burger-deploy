#include <fstream>
#include <set>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> arr;
    set<int> elems;
    int m;
    int c;

    int h(int rest, int attempt) {
        return ((rest) + c * attempt) % m;
    }

   public:
    Solution(int m, int c) : m(m), c(c), arr(m, -1), elems() {}

    void insert(int key) {
        if (elems.count(key)) return;

        int attempt = 0;
        int rest = key % m;
        while (true) {
            int id = h(rest, attempt);

            if (arr[id] == -1) {
                arr[id] = key;
                elems.insert(key);
                break;
            } else {
                attempt++;
            }
        }
    }

    void printTable(ofstream& out) {
        for (int el : arr) out << el << ' ';
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    ifstream in("input.txt");
    ofstream out("output.txt");

    int m, c;
    in >> m >> c;

    Solution s(m, c);

    int n;
    in >> n;

    int key;
    for (int i = 0; i < n; i++) {
        in >> key;
        s.insert(key);
    }

    s.printTable(out);
    return 0;
}