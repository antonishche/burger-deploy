#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class Solution {
   private:
    int m;
    int n;
    int bits;
    vector<vector<int>> friends;
    vector<int> result;
    const int BASE = 1000000000;

   public:
    Solution(int m, int n) : m(m), n(n) {};

    void solve() {
        bits = 1 << m;
        friends.assign(bits, {});

        for (int i = 0; i < bits; i++) {
            for (int j = i; j < bits; j++) {
                if (OK(i, j)) {
                    friends[i].push_back(j);
                    if (i != j) friends[j].push_back(i);
                }
            }
        }

        vector<vector<int>> dp(bits, {1});
        vector<vector<int>> next_dp(bits);

        for (int i = 1; i < n; i++) {
            next_dp.assign(bits, {});
            for (int prev = 0; prev < bits; prev++) {
                for (int next : friends[prev]) {
                    add(next_dp[next], dp[prev]);
                }
            }
            dp = move(next_dp);
        }

        for (int i = 0; i < dp.size(); i++) {
            add(result, dp[i]);
        }
    }

    void add(vector<int>& a, const vector<int>& b) {
        int carry = 0;
        for (int i = 0; i < a.size() || i < b.size() || carry; i++) {
            int sum = carry;
            if (i < a.size()) sum += a[i];
            if (i < b.size()) sum += b[i];

            if (i < a.size()) {
                a[i] = sum % BASE;
            } else {
                a.push_back(sum % BASE);
            }
            carry = sum / BASE;
        }
    }

    bool OK(int colA, int colB) {
        bool ok = true;

        bool bip = false;
        int bipColor = 42;
        for (int i = 0; i < m; i++) {
            int a = colA & 1;
            int b = colB & 1;

            colA >>= 1;
            colB >>= 1;

            if (a == b) {
                if (bip && bipColor == a) {
                    ok = false;
                    break;
                } else {
                    bip = true;
                    bipColor = a;
                }
            } else {
                bip = false;
            }
        }

        return ok;
    }

    void print(ofstream& out) {
        out << result.back();
        for (int i = result.size() - 2; i >= 0; i--) {
            out << setw(9) << setfill('0') << result[i];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    ifstream in("in.txt");
    ofstream out("out.txt");

    int m = 4, n = 2;
    in >> m >> n;

    if (m > n) swap(m, n);

    Solution s(m, n);
    s.solve();

    s.print(out);
    return 0;
}