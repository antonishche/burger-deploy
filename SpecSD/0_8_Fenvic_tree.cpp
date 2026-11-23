#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
   private:
    int n;
    vector<long long> arr;

    void makeTree() {
        for (int i = 1; i <= n; i++) {
            int p = i + (i & -i);

            if (p <= n) {
                arr[p] += arr[i];
            }
        }
    }

   public:
    Solution(int n) : n(n), arr(n + 1, 0) {}

    void fill() {
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        makeTree();
    }

    void modificate(int i, long long x) {
        while (i <= n) {
            arr[i] += x;
            i += i & -i;
        }
    }

    long long getSum(int i) {
        long long sum = 0;

        while (i > 0) {
            sum += arr[i];
            i -= i & -i;
        }

        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    Solution s(n);
    s.fill();

    int q;
    cin >> q;

    string str;
    int i, a, b;
    long long x;

    for (int _ = 0; _ < q; _++) {
        cin >> str;

        if (str == "Add") {
            cin >> i >> x;
            s.modificate(i + 1, x);
        } else {
            cin >> a >> b;
            long long sum = s.getSum(b) - s.getSum(a);
            cout << sum << '\n';
        }
    }
    return 0;
}