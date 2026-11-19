#include <fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    uint64_t n;
    in >> n;

    int count = 0;
    while (n > 0) {
        if (n & 1) {
            out << count << '\n';
        }
        n >>= 1;
        count++;
    }

    return 0;
}
