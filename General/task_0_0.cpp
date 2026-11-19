#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int main()
{
    ifstream input_file = ifstream("input.txt");
    long long sum = 0;
    set<int> elems;

    int elem = 0;
    while (input_file >> elem)
    {
        if (elems.find(elem) == elems.end())
        {
            elems.insert(elem);
            sum += elem;
        }
    }

    ofstream output_file = ofstream("output.txt");
    output_file << sum;

    return 0;
}