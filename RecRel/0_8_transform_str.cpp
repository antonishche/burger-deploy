#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream in("in.txt");

    int x, y, z;
    in >> x >> y >> z;

    if (z > x + y) {
        z = x + y;
    }

    string A, B;
    in >> A >> B;

    vector<vector<int>> memo(A.size() + 1, vector<int>(B.size() + 1, 0));

    for (int str = 1; str < memo.size(); str++) memo[str][0] = str * x;

    for (int col = 1; col < memo[0].size(); col++) memo[0][col] = col * y;

    for (int i = 1; i < memo.size(); i++) {
        for (int j = 1; j < memo[0].size(); j++) {
            if (A[i - 1] != B[j - 1]) {
                memo[i][j] = min({
                    memo[i - 1][j - 1] + z,
                    memo[i][j - 1] + y,
                    memo[i - 1][j] + x,
                });
            } else {
                memo[i][j] = memo[i - 1][j - 1];
            }
        }
    }

    ofstream out("out.txt");
    out << memo[memo.size() - 1][memo[0].size() - 1];

    return 0;
}