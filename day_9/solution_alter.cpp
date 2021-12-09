#include<iostream>
#include<fstream>
#include<vector>

#define SIZE_X 10
#define SIZE_Y 5

int checked[SIZE_Y][SIZE_X] = { 0 };
void print_checked() {
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++)
            std::cout<<checked[i][j];
        std::cout<<"\n";
    }
}

bool check_around(int y, int x) {
    int count = 0;
    if (y == 0)
        count++;
    else if (y == SIZE_Y - 1)
        count++;
    if (checked[y-1][x])
        count++;
    if (checked[y+1][x])
        count++;
    if (x == 0)
        count++;

    else if (x == SIZE_X - 1)
        count++;
    if (checked[y][x-1])
        count++;
    if (checked[y][x+1])
        count++;
    std::cout<<count<<"\n";

    return count>3;

}
int min(std::vector<int> arr) {
    int min = arr[0];
    for (auto x  = arr.begin() + 1; x < arr.end(); x ++)
        if (*x <= min)
            return -1;
    return min;
}
int basin_size(int y, int x, int arr[SIZE_Y][SIZE_X]) {
    int initial_y = y, initial_x = x;
    int size = 1;
    checked[y][x] = 1;
    while (1) {
        std::cout<<"\n";
        print_checked();
        std::cout<<"\n";
        int prev_y = y; prev_x = x;
        
        if (arr[y][x+1] != 9 && x < SIZE_X - 1) {
            checked[y][x+1] = 1;
            x ++;
            size ++;
            continue;
        }
        if (arr[y+1][x] != 9 && y < SIZE_Y - 1) {
            checked[y+1][x] = 1;
            y ++;
            size ++;
            continue;
        }
        if (arr[y][x-1] != 9 && x > 0) {
            checked[y][x-1] = 1;
            x --;
            size ++;
            continue;
        }
        if (arr[y-1][x] != 9 && y > 0) {
            checked[y-1][x] = 1;
            y --;
            size ++;
            continue;
        }
        y = initial_y;
        x = initial_x;
        if (prev_y == y && prev_x == x)
            break;
    }
     
    return size;
}

int main() {
    std::ifstream in("sample.txt");
    int arr[SIZE_Y][SIZE_X];
    int a;
    for (int i=0;i<SIZE_Y;i++) {
        for (int j=0;j<SIZE_X;j++) {
            a = in.get() - 48;
            arr[i][j] = a;
        }
        in.get();
    }
    std::vector<int> to_test;
    int sum = 0;
    //for (int i = 0; i < SIZE_Y; i++) {
    //    for (int j = 0; j < SIZE_X; j++)
    //        std::cout<<arr[i][j];
    //    std::cout<<"\n";
    //}

    for (int j=0;j<SIZE_Y;j++) {
        for (int i=0;i<SIZE_X;i++) {
            to_test.clear();
            to_test.push_back(arr[j][i]);
            if (j != 0)
                to_test.push_back(arr[j-1][i]);
            if (j != SIZE_Y - 1)
                to_test.push_back(arr[j+1][i]);
            if (i != 0)
                to_test.push_back(arr[j][i-1]);
            if (i != SIZE_X - 1)
                to_test.push_back(arr[j][i+1]);
            if (arr[j][i] == min(to_test)) {
                sum += arr[j][i] + 1;
                //std::cout<<j<<" "<<i<<" "<<arr[j][i] + 1<<"\n";
                std::cout<<basin_size(j,i,arr)<<"\n";
                print_checked();
            }
        }
    }
    std::cout<<sum<<"\n";
}
