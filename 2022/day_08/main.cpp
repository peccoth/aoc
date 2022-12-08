#include<iostream>
#define SIZE 99 
using std::cin;


int main() {
    int grid[SIZE][SIZE];
    int silver = SIZE * 2 + (SIZE - 2) * 2;
    int gold = 0;
    for ( int i = 0; i < SIZE; i++ ) {
        for (int j = 0; j < SIZE; j++ ) {
            grid[i][j] = cin.get() - '0';
        }
        cin.get();
    }
    for ( int y = 1; y < SIZE -1; y++ ) {
        for ( int x = 1; x < SIZE -1; x++ ) {
            int scenic_score = 1;
            int distance = 0;
            bool visible_top = 1;
            for ( int k = y - 1; k > -1; k-- ) {
                distance++;
                if ( grid[y][x] <= grid[k][x] ) {
                    visible_top = 0;
                    break;
                }
            }
            scenic_score *= distance, distance = 0;
            bool visible_bottom = 1;
            for ( int k = y + 1; k < SIZE; k++ ) {
                distance++;
                if ( grid[y][x] <= grid[k][x] ) {
                    visible_bottom = 0;
                    break;
                }
            }
            scenic_score *= distance, distance = 0;
            bool visible_left = 1;
            for ( int k = x - 1; k > -1; k-- ) {
                distance++;
                if ( grid[y][x] <= grid[y][k] ) {
                    visible_left = 0;
                    break;
                }
            }
            scenic_score *= distance, distance = 0;
            bool visible_right = 1;
            for ( int k = x + 1; k < SIZE; k++ ) {
                distance++;
                if ( grid[y][x] <= grid[y][k] ) {
                    visible_right = 0;
                    break;
                }
            }
            scenic_score *= distance;
            silver += visible_top || visible_bottom || visible_left || visible_right;
            gold = scenic_score > gold ? scenic_score : gold;
        }
    }
    std::cout<<silver<<std::endl<<gold<<std::endl;
}
