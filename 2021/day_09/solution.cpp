#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>
#include<vector>

#define SIZE_X 100
#define SIZE_Y 100

int checked[SIZE_Y][SIZE_X] = { 0 };
int arr[SIZE_Y][SIZE_X];

void print_checked() {
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++)
            std::cout<<checked[i][j];
        std::cout<<"\n";
    }
}

int min(std::vector<int> arr) {
    int min = arr[0];
    for (auto x  = arr.begin() + 1; x < arr.end(); x ++)
        if (*x <= min)
            return -1;
    return min;
}
int row[] = {-1, 0, 1, 0};
int col[] = { 0,-1, 0, 1};

bool is_safe(int y, int x) {
    return (y>=0 && x >= 0 && y < SIZE_Y && x < SIZE_X && checked[y][x] == 0 && arr[y][x] != 9);
}
void basin_sum(int y, int x) {
    std::queue<std::pair<int,int>> q;
    q.push({y,x});
    while (!q.empty()) {
        std::pair<int,int> node = q.front(); 
        q.pop();
        checked[node.first][node.second] = 1;
        for (int k = 0; k<4;k++) {
            if (is_safe(node.first + row[k],node.second + col[k]))
                    q.push({node.first + row[k], node.second + col[k]});
        }

    }
}
int count_ones() {
    int counter = 0;
    for (int i=0;i<SIZE_Y;i++)
        for (int j=0;j<SIZE_X;j++)
            if (checked[i][j] == 1)
                counter++;
    return counter;
}

int main() {
    std::ifstream in("input.txt");
    int a;
    for (int i=0;i<SIZE_Y;i++) {
        for (int j=0;j<SIZE_X;j++) {
            a = in.get() - 48;
            arr[i][j] = a;
        }
        in.get();
    }
    std::vector<int> to_test;
    std::vector<int> sums;
    int sum = 0;

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
                int prev_total = count_ones();
                basin_sum(j,i);
                sums.push_back(count_ones() - prev_total);
            }
        }
    }

    std::sort(sums.begin(),sums.end());
    std::cout<<sum<<"\n";
    std::cout<<sums[sums.size()-1] * sums[sums.size()-2] * sums[sums.size()-3];
}
