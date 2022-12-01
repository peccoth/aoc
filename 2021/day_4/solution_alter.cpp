#include<iostream>
#include<sstream>
#include<algorithm>
#include<vector>
struct bingo {
    int nums[5][5] = { 0 };
    bool checked[5][5]= {0};
};
struct triple {
    int first;
    int second;
    int third;
};
bingo tables[100];
std::vector<triple> winners;
int sumTable(bingo in);
void addToWinners(int n, int x) {
    for (auto x : winners) {
        if (x.first == n)
            return;
    }
    winners.push_back({n, x, sumTable(tables[n])});
}
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
void iterateTables(int x) {
    for (int i=0;i<100;i++)
        for (int j=0;j<5;j++) {
            for (int k=0;k<5;k++)
                if (tables[i].nums[j][k] == x){
                    tables[i].checked[j][k] = 1;
                    if (checkTable(tables[i])) {
                        //std::cout<<x<<" "<<checkTable(tables[i])<<"\n";
                        addToWinners(i, x);
                    }
                }
        }
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
    for (auto x : nums) {
        iterateTables(x);
    }
    for (auto x : winners) 
        std::cout<<x.first<<" "<<x.second<<" "<<x.third<<" "<<x.second * x.third<<"\n";
}
