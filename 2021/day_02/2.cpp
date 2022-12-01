#include<iostream>
#include<cstdio>

int main() {
    freopen ("input.txt","r",stdin);
    int depth=0, horizontal=0;
    std::string operation;
    int diff;
    for (int i=0;i<1000;i++) {
        std::cin>>operation>>diff; 
        if (operation[0] == 'f')
            horizontal += diff;
        if (operation[0] == 'd' ) 
            depth += diff;
        if (operation[0] == 'u')
            depth -= diff;
    }
    std::cout<<horizontal<<" "<<depth<<" "<<horizontal*depth;
}
