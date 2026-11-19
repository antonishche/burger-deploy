#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream in("input.txt");

    int n;
    in >> n;

    vector<int> arr(n);
    int num;
    for (int i = 0; i < n; i++) {
        in >> num;
        arr[num - 1] = i;
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;

            dp[i][j] = 1e9;

            for (int div = i; div < j; div++) {
                int cost =
                    (dp[i][div] + dp[div + 1][j] + abs(arr[div] - arr[j]));

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    ofstream out("output.txt");
    out << dp[0][n - 1];

    return 0;
}