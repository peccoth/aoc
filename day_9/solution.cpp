#include<iostream>
#include<fstream>
#include<vector>

#define SIZE_X 100
#define SIZE_Y 100
int min(std::vector<int> arr) {
    int min = arr[0];
    for (auto x  = arr.begin() + 1; x < arr.end(); x ++)
        if (*x <= min)
            return -1;
    return min;
}
int basin_size(int y, int x, int arr[SIZE_Y][SIZE_X]) {
    int size = 1;
    int checked[SIZE_Y][SIZE_X] = { 0 };
    checked[y][x] = 1;
    int i = y, j = x;
    while (1) {
        if (arr[i + 1][j] == 9)
            arr[i + 1][j] = 1;
        if (arr[i - 1][j] == 9)
            arr[i - 1][j] = 1;
        if (arr[i][j + 1] == 9)
            arr[i][j + 1] = 1;
        if (arr[i][j - 1] == 9)
            arr[i][j - 1] = 1;

        if (arr[i+1][j] != 9 && i < SIZE_Y - 1 && !checked[i-1][j]) {
            i++;
            checked[i][j] = 1;
            size++;
        } else if (arr[i-1][j] != 9 && i > 0) {
            i--;
            checked[i][j] = 1;
            size++;
        } else if (arr[i][j + 1] != 9 && i < SIZE_X - 1 && !checked[i][j + 1]) {
            j++;
            checked[i][j] = 1;
            size++;
        } else if (arr[i][j - 1] != 9 && i > 0 && !checked[i][j - 1]) {
            j--;
            checked[i][j] = 1;
            size++;
        } else {   
            i = y;
            j = x;
        }
        if (checked[y+1][x] && checked[y-1][x] && checked[y][x+1] && checked[y][x+1])
            break;
    }
    return size;
}

int main() {
    std::ifstream in("input.txt");
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
                std::cout<<j<<" "<<i<<" "<<arr[j][i] + 1<<"\n";
                std::cout<<basin_size(j,i,arr);
            }
        }
    }
    std::cout<<sum<<"\n";
}
