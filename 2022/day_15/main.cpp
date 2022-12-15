#include<iostream>
#include<unordered_set>
#include<math.h>
#define TARGET 2000000

using std::cin;

int main() {
    std::string s;
    std::unordered_set<int> covered;
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
                for ( int i = sx - (sy + d - TARGET); i < sx + (sy + d - TARGET); i++)
                    covered.insert(i);
            }
        }


        if ( sy >= TARGET ) {
            if (sy - d <= TARGET ) {
                for ( int i = sx - (TARGET - (sy - d)); i < sx + (TARGET - (sy - d)); i++)
                    covered.insert(i);
            }
        }
    }
    //for ( auto x : covered) 
        //std::cout<<x<<" ";
    std::cout<<std::endl<<covered.size()<<std::endl;

}
