#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");

    int n;
    in >> n;

    vector<int> arr(n + 1);

    for (int i = 1; i < n + 1; i++)
        in >> arr[i];

    bool flag = true;
    for (int i = 1; i <= (n + 1) / 2; i++) {
        int fCID = 2 * i, sCID = fCID + 1;
        if (fCID < n + 1 && arr[i] > arr[fCID]) {
            flag = false;
            break;
        }
        if (sCID < n + 1 && arr[i] > arr[sCID]) {
            flag = false;
            break;
        }
    }

    ofstream out("output.txt");

    if (flag) {
        out << "Yes";
    } else {
        out << "No";
    }

    return 0;
}