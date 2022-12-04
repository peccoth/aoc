#include<iostream>
#include<string>
#include<utility>
using std::cin, std::cout, std::string, std::endl, std::pair;
pair<int,int> split(string in) {
    size_t delim = in.find('-');
    return { std::stoi(in.substr(0,delim)), std::stoi(in.substr(delim+1))};
}

int main() {
    string a;
    pair<int,int> elf1;
    pair<int,int> elf2;

    int silver = 0, gold = 0;
    while (cin>>a) {
        size_t delim = a.find(',');
        elf1 = split(a.substr(0,delim));
        elf2 = split(a.substr(delim+1));
        silver += (elf1.first <= elf2.first && elf1.second >= elf2.second) || (elf2.first <= elf1.first && elf2.second >= elf1.second);
        gold += (elf1.first <= elf2.first && elf1.second >= elf2.first) || (elf1.first <= elf2.second && elf1.second >= elf2.second) ||
                (elf2.first <= elf1.first && elf2.second >= elf1.first) || (elf2.first <= elf1.second && elf2.second >= elf1.second);
    }
    cout<<silver<<endl<<gold<<endl;
}
