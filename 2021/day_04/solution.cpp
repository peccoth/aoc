#include<iostream>
#include<sstream>
#include<algorithm>
#include<vector>
struct bingo {
    int nums[5][5] = { 0 };
    bool checked[5][5]= {0};
};
bingo tables[100];
void printTable(bingo in) {
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            std::cout<<in.nums[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            std::cout<<in.checked[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}
bool checkTable(bingo in) {
    bool prev = 1;
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            if (in.checked[i][j] == 0) {
                prev = 0;
                break;
            }
        }
        if (prev)
            return 1;
        prev = 1;
    }
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            if (in.checked[j][i] == 0) {
                prev = 0;
                break;
            }
        }
        if (prev)
            return 1;
        prev = 1;
    }
    return 0;
}
int iterateTables(int x) {
    for (int i=0;i<100;i++)
        for (int j=0;j<5;j++) {
            for (int k=0;k<5;k++)
                if (tables[i].nums[j][k] == x){
                    tables[i].checked[j][k] = 1;
                    if (checkTable(tables[i])) {
                        std::cout<<x<<" "<<checkTable(tables[i])<<"\n";
                        return i;
                    }
                }
        }
    return 0;
}
int sumTable(bingo in) {
    int sum=0;
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            if (!in.checked[i][j]) {
                sum+=in.nums[i][j];
            }
        }
    }
    return sum;
}

int main() {
    freopen("input.txt","r",stdin);
    std::string in;
    std::getline(std::cin,in);
    std::stringstream ss;
    std::replace(in.begin(),in.end(),',',' ');
    ss << in;
    std::vector<int> nums;
    int a;
    while (ss) {
        ss >> a;
        nums.push_back(a);
    }
    int n;
    for (int i=0;i<100;i++)
    for (int j=0;j<5;j++) {
        for (int k=0;k<5;k++) {
            std::cin>>n;
            tables[i].nums[j][k] = n;
        }
    }
    int winner, sum, out;
    for (auto x : nums) {
        winner = iterateTables(x);
        if (winner) {
            sum = sumTable(tables[winner]);
            out = sum * x;
            break;
        }
    }
    std::cout<<"\nwinning table: "<<winner<<" "<<sum<<" "<<out<<"\n";
}
