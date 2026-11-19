#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

void solve(string &str, int str_len);
void fill_dp(vector<vector<int>> &dp, string &str, int str_len);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream in("input.txt");
    string str;

    in >> str;
    solve(str, str.size());

    return 0;
}

void solve(string &str, int str_len)
{
    vector<vector<int>> dp(str_len + 1, vector<int>(str_len + 1, 0));
    fill_dp(dp, str, str_len);

    string res = "";
    int s = str_len, c = str_len;

    while (s > 0 && c > 0)
    {
        if (str[s - 1] == str[str_len - c])
        {
            res += str[s - 1];
            s--;
            c--;
        }
        else if (dp[s - 1][c] > dp[s][c - 1])
        {
            s--;
        }
        else
        {
            c--;
        }
    }

    ofstream out("output.txt");
    out << res.size() << endl;
    out << res;
}

void fill_dp(vector<vector<int>> &dp, string &str, int str_len)
{
    for (int i = 1; i <= str_len; i++)
    {
        for (int j = 1; j <= str_len; j++)
        {
            if (str[i - 1] == str[str_len - j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
}