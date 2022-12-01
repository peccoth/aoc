#include<iostream>
#include<cstdio>
#include<vector>

int main() {
    freopen("1.txt","r",stdin);
    std::vector<int> input;
    int in, count =0;
    while (!std::cin.eof()) {
        std::cin>>in; 
        input.push_back(in);
    }
    int prev = input[0] + input[1] + input [2], curr;
    for (size_t i = 2; i<input.size() - 1;i++) {
        curr = input[i-1] + input[i] + input[i+1]; 
        count+=curr>prev;
        prev = curr;
    }
    std::cout<<count;
}
