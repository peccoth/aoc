#include<iostream>
#include<sstream>
#include<algorithm>
#include<set>

int main() {
    std::freopen("input.txt","r",stdin);
    std::string str;
    int x,y, width = 0, height = 0;
    std::set<std::pair<int,int>> data;
    
    while (std::getline(std::cin, str)) {
        if (!str.size()) break;
        std::replace(str.begin(),str.end(),',',' ');
        std::stringstream ss(str);
        ss>>x;
        ss>>y;
        data.insert({y,x});
        if (x > width)
            width = x;
        if (y > height)
            height = y;
    }
    std::set<std::pair<int,int>> folded;
    while (std::getline(std::cin, str)) {
        folded.clear();
        std::stringstream ss(str.substr(13));
        int FOLD;
        ss >> FOLD;
        int size = FOLD * 2;
        if (str[11] == 'y') {
        for (auto x : data) {
            folded.insert({x.first < FOLD ? x.first : size - x.first,x.second});
        }
            width = FOLD;
        }
        else {
        for (auto x : data) {
            folded.insert({x.first,x.second < FOLD ? x.second : size - x.second});
        }
        height = FOLD;
        }
        data = folded;
    }
    auto next = data.begin();
    for (int y=0;y<height/4;y++) {
        int x = 0;
        while (next != data.end() && (*next).first == y) {
            for (;x<(*next).second;x++) std::cout<<" ";
            std::cout<<"#";
            x++;
            next++;
        }
        for (;x<width;x++) std::cout<<" ";
        std::cout<<"\n";
    }
}
