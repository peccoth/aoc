#include<iostream>
#include<queue>
#include<cstring>

int arr[10][10];
int flashed[10][10] = { 0 }; 
int counter = 0;
int row[] = {-1, 0, 1, 0,-1,-1, 1, 1};
int col[] = { 0,-1, 0, 1,-1, 1,-1, 1};
bool is_safe(int y, int x) {
    return y >= 0 && x >= 0 && y < 10 && x < 10 && !flashed[y][x]; 
}
void flood(int y, int x) {
    std::queue<std::pair<int,int>> q;
    q.push({y,x});
    while (!q.empty()) {
        std::pair<int,int> node = q.front(); 
        q.pop();
        arr[node.first][node.second]+= !flashed[node.first][node.second];
        if (arr[node.first][node.second] > 9) {
            counter ++;
            flashed[node.first][node.second] = 1;
            arr[node.first][node.second] = 0;
            for (int k = 0; k<8;k++) 
                if (is_safe(node.first + row[k],node.second + col[k]))
                        q.push({node.first + row[k], node.second + col[k]});
        }
    }
}
bool check_sync() {
    for (int i=0;i<10;i++)
        for (int j=0;j<10;j++)
            if (!flashed[i][j])
                return 0;
    return 1;
}
int main() {
    freopen("input.txt", "r", stdin);
    char c;
    for (int i=0;i<10;i++) {
        for (int j=0;j<10;j++) {
            std::cin.get(c);
            arr[i][j] = c - 48;
        }
        std::cin.get();
    }
    int k = 1;
    while (!check_sync()) {
        memset(flashed, 0, sizeof(flashed));
        for (int i=0;i<10;i++) {
            for (int j=0;j<10;j++) {
                flood(i,j);
            }
        }
        if (k == 100)
            std::cout<<counter<<"\n";
        k++;
    }
    std::cout<<k; 
            
}
