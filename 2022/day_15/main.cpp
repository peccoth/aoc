#include<iostream>
#include<math.h>
#include<climits>
#define TARGET 2000000

using std::cin;

int main() {
    std::string s;
    int min = INT_MAX, max = INT_MIN;
    while (cin.peek() != EOF) {
        cin>>s>>s>>s;
        int sx = stoi(s.substr(s.find('=')+1,s.find(',')-1));
        cin>>s;
        int sy = stoi(s.substr(s.find('=')+1,s.find(':')-1));
        cin>>s>>s>>s>>s>>s;
        int bx = stoi(s.substr(s.find('=')+1,s.find(',')-1));
        cin>>s;
        int by = stoi(s.substr(s.find('=')+1,s.find(':')-1));


        int d = abs(sx - bx) + abs(sy - by);

        if ( sy <= TARGET ) {
            if (sy + d >= TARGET ) {
                min = sx - (sy + d - TARGET) < min ? sx - (sy + d - TARGET) : min;
                max = sx + (sy + d - TARGET) > max ? sx + (sy + d - TARGET) : max;
            }
        }


        if ( sy >= TARGET ) {
            if (sy - d <= TARGET ) {
                min = sx - (TARGET - (sy - d)) < min ? sx - (TARGET - (sy - d)) : min;
                max = sx - (TARGET - (sy - d)) > max ? sx - (TARGET - (sy - d)) : max;
            }
        }
    }
    int silver = abs(min) + abs(max);
    std::cout<<silver<<std::endl;

}
