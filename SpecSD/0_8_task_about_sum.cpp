#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int m = sqrt(n) + 1;
    int block = 0;
    int count = 0;

    vector<long long> b(m, 0);
    for (int i = 0; i < n; i++) {
        if (count == m) {
            block++;
            count = 0;
        }
        b[block] += a[i];
        count++;
    }

    int q;
    cin >> q;

    string str;
    int i_, x;
    int l, r;

    for (int i = 0; i < q; i++) {
        cin >> str;

        if (str == "Add") {
            cin >> i_ >> x;

            a[i_] += x;
            b[i_ / m] += x;
        } else {
            cin >> l >> r;

            int bl = l / m;
            int br = r / m;

            if (bl == br) {
                long long sum = 0;
                for (int i = l; i < r; i++) sum += a[i];
                cout << sum << endl;
            } else {
                long long s1 = 0;
                int end1 = (bl + 1) * m;
                for (int i = l; i < end1; i++) {
                    s1 += a[i];
                }

                long long s2 = 0;
                for (int i = bl + 1; i < br; i++) {
                    s2 += b[i];
                }

                long long s3 = 0;
                int start3 = br * m;
                for (int i = start3; i < r; i++) {
                    s3 += a[i];
                }

                long long sum = s1 + s2 + s3;

                cout << sum << endl;
            }
        }
    }

    return 0;
}