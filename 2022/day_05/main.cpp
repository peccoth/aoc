#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using std::cin, std::string;
struct action {
    int move;
    int from;
    int to;
};

action parse(string in) {
    action out;
    std::stringstream ss ;
    string temp;
    ss << in;
    ss >> temp >> out.move >> temp >> out.from >> temp >> out.to;
    return out;
}

int main() {
    char c;
    int row = 7, column = 0, l = 0;
    char frey[9][46] = { ' ' };
    char freg[9][46] = { ' ' };
    while (1) {
        column++;
        c = cin.get();
        if ( c == '\n' ) {
            l++;
            row--;
            column = 0;
        }
        if ( l > 8)
            break;
        if ( (column - 2) % 4 == 0)
            frey[(column-2)/4][row] = c;
    }
    int heights[9] = {0};
    for (int i = 0; i < 9; i++) 
        for ( int j=0; j<9; j++ ) 
            heights[i] += (frey[i][j] > 64);

    int heightsg[9] = {0};
    memcpy(freg,frey,sizeof(frey));
    memcpy(heightsg,heights,sizeof(heights));
    string line;
    while (getline(cin,line)) {
        action parsed = parse(line);
        for(int i=0;i<parsed.move;i++) {
            frey[parsed.to-1][heights[parsed.to-1]] = frey[parsed.from-1][heights[parsed.from-1]-1];
            frey[parsed.from-1][heights[parsed.from-1]-1] = ' ';
            heights[parsed.from-1]--;
            heights[parsed.to-1]++;
        }
        for(int i=parsed.move;i>0;i--) {
            freg[parsed.to-1][heightsg[parsed.to-1]+i-1] = freg[parsed.from-1][heightsg[parsed.from-1]-1];
            freg[parsed.from-1][heightsg[parsed.from-1]-1] = ' ';
            heightsg[parsed.from-1]--;
        }
        heightsg[parsed.to-1] += parsed.move;

    }
    for (int i=0;i<9;i++)
        printf("%c",frey[i][heights[i]-1]);
    printf("\n");
    for (int i=0;i<9;i++)
        printf("%c",freg[i][heightsg[i]-1]);
    printf("\n");
}
