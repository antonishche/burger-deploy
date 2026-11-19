#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void fill_arr(vector<int> &arr, int n);
void solve(vector<int> &A, vector<int> &B, int n);
void print_stack(stack<int> &s);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> A(n);
    vector<int> B(n);
    fill_arr(A, n);
    fill_arr(B, n);

    solve(A, B, n);
    return 0;
}

void solve(vector<int> &A, vector<int> &B, int n)
{
    vector<vector<int>> memory(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                memory[i][j] = memory[i - 1][j - 1] + 1;
            }
            else
            {
                memory[i][j] = max(memory[i - 1][j], memory[i][j - 1]);
            }
        }
    }

    stack<int> indA;
    stack<int> indB;

    int str = n, col = n;

    while (str > 0 && col > 0)
    {
        if (A[str - 1] == B[col - 1])
        {
            indA.push(str - 1);
            indB.push(col - 1);
            str--;
            col--;
        }
        else if (memory[str][col] == memory[str - 1][col])
        {
            str--;
        }
        else
        {
            col--;
        }
    }

    cout << memory[n][n] << endl;
    print_stack(indA);
    print_stack(indB);
}

void print_stack(stack<int> &s)
{
    while (!s.empty())
    {
        cout << s.top() << ' ';
        s.pop();
    }
    cout << endl;
}

void fill_arr(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
}