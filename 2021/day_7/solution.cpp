#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>

#include<vector>
#include<climits>
double absolute(int n) {
    return (n < 0) * n * -1 + (n>0) * n;
}
int calculate_fuel(std::vector<int>& in, int target) {
    int out = 0;
    for (auto x : in) {
        out += ((absolute(x - target) + 1)/2) * absolute(x - target);
    }
    return out;
}

int main() {
    std::ifstream input ("input.txt");
    std::string line;
    std::getline(input,line);
    std::replace(line.begin(),line.end(),',',' ');
    std::stringstream ss(line);
    std::vector<int> in;
    std::vector<int> result;
    unsigned long n, start = 0, stop = 2048;
    unsigned long test_a, test_b;

    while (ss >> n)
        in.push_back(n);

    while (start != stop) {
        test_a = calculate_fuel(in, start);
        test_b = calculate_fuel(in, stop);
        if (test_a < test_b)
            stop = (start+stop) / 2;
        if (test_a > test_b)
            start = (start+stop) / 2;
        if (abs(test_a - test_b) <=2) {
            std::cout<<(test_a < test_b) * test_a + (test_a > test_b) * test_b<<"\n";
            break;
        }
    }
    std::cout<<calculate_fuel(in,start);
}
