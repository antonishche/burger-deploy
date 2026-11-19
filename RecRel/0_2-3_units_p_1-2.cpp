#include <iostream>
using namespace std;

void solve(long long del);

long long fact_mod(long long n, long long del);
long long mul_mod(long long a, long long b, long long del);
long long pow(long long num, long long deg, long long del);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long del = 1e9 + 7;
    solve(del);

    return 0;
}

void solve(long long del)
{
    long long n, k, g;
    if (!(cin >> n >> k))
    {
        cout << "заглушка";
        n = 10;
        k = 2;
    }

    g = n - k;

    long long a, b;

    if (g > k)
    {
        a = mul_mod(g + 1, n, del);
        b = fact_mod(k, del);
    }
    else
    {
        a = mul_mod(k + 1, n, del);
        b = fact_mod(g, del);
    }

    long long new_b = pow(b, del - 2, del);
    long long res = (a * new_b) % del;

    cout << res;
}

long long fact_mod(long long num, long long del)
{
    long long res = 1;

    for (long long i = 1; i <= num; i++)
    {
        res *= i;
        res %= del;
    }

    return res;
}

long long mul_mod(long long a, long long b, long long del)
{
    long long res = 1;

    for (long long i = a; i <= b; i++)
    {
        res *= i;
        res %= del;
    }

    return res;
}

long long pow(long long num, long long deg, long long del)
{
    long long res = 1;

    while (deg > 0)
    {
        if (deg % 2 == 1)
        {
            res *= num;
            res %= del;
        }

        num = num * num;
        num %= del;
        deg = (long long)(deg / 2);
    }

    return res;
}