#include<iostream>
#include<cstdio>

int main() {
    freopen ("input.txt","r",stdin);
    int depth=0, horizontal=0, aim=0;
    std::string operation;
    int diff;
    for (int i=0;i<1000;i++) {
        std::cin>>operation>>diff; 
        if (operation == "forward") {
            horizontal += diff;
            depth += diff * aim;
        }
        if (operation == "down" ) 
            aim += diff;
        if (operation == "up")
            aim -= diff;
    }
    std::cout<<horizontal<<" "<<depth<<" "<<horizontal*depth;
}
