#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void insert(int num, vector<int>& memo);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream in("input.txt");

    int n;
    in >> n;

    vector<int> memo;
    memo.reserve(n);

    int curr;
    for (int _ = 0; _ < n; _++) {
        in >> curr;
        insert(curr, memo);
    }

    ofstream out("output.txt");
    out << memo.size();

    return 0;
}

void insert(int num, vector<int>& memo) {
    int left = 0;
    int right = memo.size();

    while (left < right) {
        int mid = (left + right) / 2;

        if (memo[mid] < num) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (left == memo.size()) {
        memo.push_back(num);
    } else {
        memo[left] = num;
    }
}