#include <iostream>
#include <vector>
#include <string>
using namespace std;

long long find_first(vector<long long> &arr, long long x, long long n)
{
    long long left = 0;
    long long right = n;

    while (left < right)
    {
        long long mid = (left + right) / 2;
        if (arr[mid] < x)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return left;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    cin >> n;

    vector<long long> arr(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    long long k;
    cin >> k;

    long long req;
    for (long long i = 0; i < k; i++)
    {
        cin >> req;

        long long l = find_first(arr, req, n);
        if (l == n)
        {
            cout << "0 " << n << ' ' << n << '\n';
            continue;
        }

        long long r = find_first(arr, req + 1, n);

        if (arr[l] == req)
        {
            cout << "1 " << l << ' ' << r << '\n';
        }
        else
        {
            cout << "0 " << l << ' ' << r << '\n';
        }
    }

    return 0;
}