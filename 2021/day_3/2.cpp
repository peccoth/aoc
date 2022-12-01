#include<iostream>
#include<cstdio>
#include<vector>
int binarytoint(std::string in) {
    int out=0;
    for (auto x : in) {
        out += x == '1';
        out = out << 1;
    }
    return out >> 1;
}
int main() {
    freopen("input.txt","r",stdin);
    std::vector<std::string> data, oxygenData, co2Data;
    std::string in;
    int oLevel, co2Level;

    for (int i=0;i<1000;i++) {
        std::cin>>in;    
        data.push_back(in);
    }
    
    oxygenData = data;
    std::vector<std::string> temp;
    int countZero = 0, countOne = 0;
    for (int i=0;i<12;i++) {
        temp.clear();
        countZero = 0, countOne = 0;
        for (auto x : oxygenData) 
            if (x[i] == '1') 
                countOne++;
            else 
                countZero++;
        if (countOne>=countZero)
        for (auto x : oxygenData) {
            if (x[i] == '1') 
                temp.push_back(x);
        } 
        else
        for (auto x : oxygenData) {
            if (x[i] == '0') 
                temp.push_back(x);
        }
        if (temp.size() < 2)
            break;
        oxygenData = temp;
    }
    oLevel = binarytoint(temp[0]);
    co2Data = data;
    for (int i=0;i<12;i++) {
        countZero = 0, countOne = 0;
        temp.clear();
        for (auto x : co2Data) 
            if (x[i] == '1') 
                countOne++;
            else 
                countZero++;
        if (countOne<countZero)
        for (auto x : co2Data) {
            if (x[i] == '1') 
                temp.push_back(x);
        } 
        else
        for (auto x : co2Data) {
            if (x[i] == '0') 
                temp.push_back(x);
        }
        if (temp.size() < 2)
            break;
        co2Data = temp;
    }
    co2Level = binarytoint(temp[0]);
    std::cout<<oLevel<<" "<<co2Level<<" "<<oLevel * co2Level<<"\n";
}
