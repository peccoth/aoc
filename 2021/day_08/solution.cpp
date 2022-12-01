#include<iostream>
#include<algorithm>
#include<vector>
#include<array>
int count_simple(std::vector<std::array<std::string,14>> in) {
    int counter = 0;
    for (auto x : in) {
        for (int j = 10;j<14;j++)
        switch (x[j].length()){
            case (2):
                counter ++;
                break;
            case (3):
                counter ++;
                break;
            case (4):
                counter ++;
                break;
            case (7):
                counter ++;
                break;
        }
    }
    return counter;
}
int decode(std::array<std::string,14> in) {
    std::vector<std::string> l5, l6;
    std::string solved[10];

    for (int i=0;i<10;i++) {
        switch (in[i].length()) {
            case 2:
                solved[1] = in[i];
                break;
            case 3:
                solved[7] = in[i];
                break;
            case 4:
                solved[4] = in[i];
                break;
            case 7:
                solved[8] = in[i];
                break;
            case 5:
                    l5.push_back(in[i]);
                break;
            case 6:
                    l6.push_back(in[i]);
                break;
        }
    }

    char a;
    for (auto x : solved[7]) {
        bool exists = 0;
        for (auto y : solved[1]) {
            if ( x == y )
                exists = 1;
        }
        if (!exists)
            a = x;
    }


    std::string eg = "";
    for (auto x : solved[8]) {
        bool exists = 0;
        for (auto y : solved[4])
            if (x == y)
                exists = 1;
        if (x == a)
            exists = 1;
        if (!exists)
            eg += x;
    }
    
    for (auto x : l5) {
        int ok = 0;
        for (int j=0;j<5;j++)
            for (auto y : solved[1]) 
                if (x[j] == y)
                    ok ++;
        if (ok > 1)
            solved[3] = x;
    }

    for (auto x : l5) {
        int ok = 0;
        for (int i=0;i<5;i++)
            for (auto y : eg)
                if (x[i] == y)
                    ok ++;
        if (ok > 1)
            solved[2] = x;
    }

    for (auto x : l5)
        if (x != solved[2] && x != solved[3])
            solved[5] = x;

    for (auto x : l6) {
        int ok = 0;
        for (int i=0;i<6;i++) {
            for (auto y : eg)
                if (x[i] == y)
                    ok ++;
            for (auto y : solved[1])
                if (x[i] == y)
                    ok ++;
        }
        if (ok > 3)
            solved[0] = x;
    }
    for (auto x : l6) {
        int ok = 0, ok1=0;
        for (int i=0;i<6;i++) {
            for (auto y : eg)
                if (x[i] == y)
                    ok ++;
            for (auto y : solved[1])
                if (x[i] == y)
                    ok1 ++;
        }
        if (ok > 1 && ok1 == 1)
            solved[6] = x;
    }

    for (auto x : l6)
        if (x != solved[6] && x != solved[0]) 
            solved[9] = x;

    for (int i = 0;i<10;i++)
        std::sort(solved[i].begin(),solved[i].end());

    int out = 0;
    for (int i=10;i<14;i++) {
        std::sort(in[i].begin(),in[i].end());
        for (int j=0;j<10;j++) 
            if (in[i] == solved[j]) 
                out= out*10 + j;
    }

    return out;
}

int main() {
    freopen("input.txt","r",stdin);
    std::vector<std::array<std::string,14>> a;
    std::string dump;
    for  (int i=0;i<200;i++) {
        a.push_back({});
        for (int j=0;j<10;j++) {
            std::cin>>a.back()[j];
        }
        std::cin>>dump;
        for (int j=10;j<14;j++) {
            std::cin>>a.back()[j];
        }
    }
    
    std::cout<<"Part 1: "<<count_simple(a)<<"\n";
    unsigned long sum = 0;
    for (int i=0;i<200;i++)
        sum += decode(a[i]);
    std::cout<<"Part 2: "<<sum<<"\n";
}
