#include <iostream>
#include <stdio.h>
#include <vector>

int main() {
    std::vector<std::vector<char>> array;
    for (int i = 0; i < 200; i++) {
        array.push_back({'.'});
        for ( int j = 0; j < 1200; j++ ) 
            array[i].push_back({'.'});
    }
    std::string line;
    int y_max = 0;
    while (getline(std::cin,line)) {
        int sx, sy, i = 0;
        int ni = line.find(',',i);
        sx = stoi(line.substr(i, ni));
        sy = stoi(line.substr(ni + 1, line.find ('-', ni) -2 ));
        i = line.find('-',ni);
        while ( i != std::string::npos) {
            ni = line.find(',',i);
            int nx = stoi(line.substr(i + 3, ni -1));
            int ny = stoi(line.substr(ni + 1, line.find ( '-', ni ) - 2));
            if ( sx < nx ) {
                for ( int j = sx; j <= nx; j++ )
                    array[sy][j] = '#';
            } else if ( nx < sx ) {
                for ( int j = nx; j <= sx; j++ )
                    array[sy][j] = '#';
            } else if ( sy < ny ) {
                for ( int j = sy; j <= ny; j++ )
                    array[j][sx] = '#';
            } else if ( ny < sy ) {
                for ( int j = ny; j <= sy; j++ )
                    array[j][sx] = '#';
            }
            i = line.find('-', ni);
            sx = nx;
            sy = ny;
            if (sy > y_max)
                y_max = sy;
        }
    }
    for (int i = 0; i < 1200; i++)
        array[y_max+2][i] = '#';
    bool fail_s = 0, fail_g = 0;
    int silver = 0, gold = 0;
    
    while (!(fail_s & fail_g)){
        int sand_x = 500, sand_y = 0;
        silver += !fail_s;
        gold ++;
        while (true) {
            if ( sand_y > y_max )
                fail_s = 1;
            if ( array[sand_y+1][sand_x] == '.'){
                sand_y++;
                continue;
            }
            if (array[sand_y+1][sand_x-1] == '.') {
                sand_x--;
                continue;
            }
            if (array[sand_y+1][sand_x+1] == '.') {
                sand_x++;    
                continue;
            }
            if (sand_y == 0 && array[sand_y][sand_x] == 'o') {
                fail_g = 1;
                break;
            }
            array[sand_y][sand_x] = 'o';
            break;
        }
    }

    std::cout<<silver-1<< " "<< gold -1<<std::endl;
}
