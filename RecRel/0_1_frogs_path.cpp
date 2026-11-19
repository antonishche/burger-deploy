#include <iostream>
#include <vector>
using namespace std;

vector<int> find_positions(vector<int> &arr, int n)
{
    arr[1] = 0;
    arr[2] = arr[2] + arr[0];

    for (int i = 3; i < n; i++)
    {
        arr[i] += max(arr[i - 2], arr[i - 3]);
    }

    vector<int> positions;
    positions.push_back(n);
    int pos = n - 1;
    while (pos > 2)
    {
        if (arr[pos - 2] > arr[pos - 3])
        {
            pos -= 2;
            positions.push_back(pos + 1);
        }
        else
        {
            pos -= 3;
            positions.push_back(pos + 1);
        }
    }

    if (pos == 2)
    {
        positions.push_back(1);
    }

    return positions;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> lilies(n);
    for (int i = 0; i < n; i++)
    {
        cin >> lilies[i];
    }

    if (lilies.size() == 2)
    {
        cout << -1;
        return 0;
    }

    if (lilies.size() == 1)
    {
        cout << lilies[0] << '\n';
        cout << 1;
        return 0;
    }

    vector<int> positions = find_positions(lilies, n);
    cout << lilies[n - 1] << '\n';
    for (int i = positions.size() - 1; i >= 0; i--)
    {
        cout << positions[i] << ' ';
    }

    return 0;
}