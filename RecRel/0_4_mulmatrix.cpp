#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream in("input.txt");

    int n;
    in >> n;

    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++)
        in >> arr[i].first >> arr[i].second;

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            dp[i][j] = 1e9;

            for (int div = i; div < j; div++)
            {
                int cost = (arr[i].first * arr[div].second * arr[j].second +
                            dp[i][div] +
                            dp[div + 1][j]);
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    ofstream out("output.txt");
    out << dp[0][n - 1];

    return 0;
}