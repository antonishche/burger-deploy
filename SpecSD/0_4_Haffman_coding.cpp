#include <fstream>
#include <queue>

using namespace std;

uint64_t getMin(queue<uint64_t>& q) {
    uint64_t temp = q.front();
    q.pop();
    return temp;
}

uint64_t getMin(queue<uint64_t>& q1, queue<uint64_t>& q2) {
    if (q1.empty()) {
        return getMin(q2);
    }

    if (q2.empty()) {
        return getMin(q1);
    }

    if (q1.front() < q2.front()) {
        return getMin(q1);
    } else {
        return getMin(q2);
    }
}

int main() {
    ifstream in("huffman.in");
    ofstream out("huffman.out");

    int n;
    in >> n;

    queue<uint64_t> q1;
    queue<uint64_t> q2;

    uint64_t p;
    for (int i = 0; i < n; i++) {
        in >> p;
        q1.push(p);
    }

    uint64_t sum = 0;

    while (!q1.empty() || q2.size() > 1) {
        uint64_t a = getMin(q1, q2);
        uint64_t b = getMin(q1, q2);
        uint64_t temp_sum = a + b;
        q2.push(temp_sum);
        sum += temp_sum;
    }

    out << sum;

    return 0;
}