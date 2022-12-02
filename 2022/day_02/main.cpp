#include <iostream>
#include <stdio.h>

int main() {
    freopen ("input","r",stdin);
    int score = 0;
    while (!std::cin.eof()) {
        char attack, response;
        std::cin>>attack>>response;
        std::cout<<attack<<" "<<response;
        switch (attack) { // A - Rock, B - Paper, C - Scissors | Y - Paper, X - Rock, Z - Scissors
            case ('A'):
                score+=((response == 'Y') * 4) + ((response == 'X') * 3) + ((response == 'Z') * 8);
                std::cout<<score<<std::endl;
                break;
            case ('B'):
                score+=((response == 'Y') * 5) + ((response == 'X') * 1) + ((response == 'Z') * 9);
                std::cout<<score<<std::endl;
                break;
            case ('C'):
                score+=((response == 'Y') * 6) + ((response == 'X') * 2) + ((response == 'Z') * 7);
                std::cout<<score<<std::endl;
                break;
        }
    }
    std::cout<<score;

}
