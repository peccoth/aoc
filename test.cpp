#include<iostream>
#include<vector>

int main() {
    std::vector<int> test = {1,23,4,5,654};
    for (auto x : test) {
        std::cout<<x<<"\n";
    }
}
