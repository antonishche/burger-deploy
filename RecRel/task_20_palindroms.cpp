#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //
    // ifstream in("input.txt");
    // ofstream out("output.txt");
    //

    string s;
    // in >> s;
    cin >> s;

    int n = s.length();
    vector<vector<short>> arr(n + 1, vector<short>(n + 1, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int id = i + 1;
            int jd = j + 1;

            if (s[i] == s[n - 1 - j]) {
                arr[id][jd] = arr[i][j] + 1;
            } else {
                arr[id][jd] = max(arr[id][j], arr[i][jd]);
            }
        }
    }

    int max_length = arr[n][n];
    bool odd = max_length % 2;

    int half_length = max_length / 2;
    if (odd) half_length++;

    string minS = "";
    string maxS = "";

    int i = n;
    int j = n;
    while (minS.length() < half_length) {
        if (s[i - 1] == s[n - j]) {
            minS += s[i - 1];
            i--;
            j--;
        } else {
            if (arr[i][j - 1] > arr[i - 1][j]) {
                j--;
            } else if (arr[i][j - 1] < arr[i - 1][j]) {
                i--;
            } else {
                for (int letter = 'a' + 0; letter <= 'z' + 0; letter++) {
                    int il = i;
                    int jl = j;
                    while (il > 0 && s[il - 1] != letter) il--;
                    while (jl > 0 && s[n - jl] != letter) jl--;

                    if (il == 0 || jl == 0) continue;

                    if (arr[il][jl] == arr[i][j]) {
                        i = il;
                        j = jl;
                        break;
                    }
                }
            }
        }
    }

    i = n;
    j = n;
    while (maxS.length() < half_length) {
        if (s[i - 1] == s[n - j]) {
            maxS += s[i - 1];
            i--;
            j--;
        } else {
            if (arr[i][j - 1] > arr[i - 1][j]) {
                j--;
            } else if (arr[i][j - 1] < arr[i - 1][j]) {
                i--;
            } else {
                for (int letter = 'z' + 0; letter >= 'a' + 0; letter--) {
                    int il = i;
                    int jl = j;
                    while (il > 0 && s[il - 1] != letter) il--;
                    while (jl > 0 && s[n - jl] != letter) jl--;

                    if (il == 0 || jl == 0) continue;

                    if (arr[il][jl] == arr[i][j]) {
                        i = il;
                        j = jl;
                        break;
                    }
                }
            }
        }
    }

    for (int i = max_length / 2 - 1; i >= 0; i--) {
        minS += minS[i];
        maxS += maxS[i];
    }

    // out << minS << '\n';
    // out << maxS << '\n';

    cout << minS << '\n';
    cout << maxS << '\n';

    // for (int i = 0; i <= n; i++) {
    //     for (int j = 0; j <= n; j++) {
    //         if (i == 0 && j == 0) {
    //             out << "  ";
    //         } else if (i == 0) {
    //             out << s[n - j] << ' ';
    //         } else if (j == 0) {
    //             out << s[i - 1] << ' ';
    //         } else {
    //             out << arr[i][j] << ' ';
    //         }
    //     }
    //     out << '\n';
    // }

    return 0;
}