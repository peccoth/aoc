#include<iostream>
#include<unordered_set>
int solve(std::string &in, int size) {
    int result = 0;
    std::unordered_set<char> set;
    for (result=0; result < in.length(); result++){
        for (int i = 0; i < size; i++)
            set.insert(in[result + i]);

        if (set.size() == size)
            return result + size;
        else 
            set.clear();
    }
    return 0;
}

int main() {
    std::string str;
    std::cin>>str;
    int silver = solve(str,4);
    int gold = solve(str,14);

    std::cout<<silver<<" "<<gold<<std::endl;
}
