#include <iostream>
#include <stdio.h>
#include <vector>

int main() {
    freopen ("input.txt", "r", stdin);
    std::vector<int> food = { 0 };
    int temp;

    while ( !std::cin.eof() ) {
        std::cin >> temp;
        std::cin.get();
        char peek = std::cin.peek();
        food.back() += temp;
        if (peek == '\n') 
            food.push_back(0);
    }
    int max = 0;
    for ( auto x : food )
        if ( x > max )
            max = x;
    std::cout<<max<<std::endl;;

    int top[3] = { 0,0,0 };
    for ( auto x : food )
        if ( x > top[2] ) {
            if ( x > top[1] ) {
                if ( x > top[0] ) {
                    top[2] = top[1];
                    top[1] = top[0];
                    top[0] = x;
                    continue;
                }
                top[2] = top[1];
                top[1] = x;
                continue;
            }
            top[2] = x;
        }
    std::cout<<top[0] + top[1] + top[2]<<std::endl;
}
