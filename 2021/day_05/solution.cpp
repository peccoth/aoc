#include<iostream>
#include<algorithm>
#include<sstream>
#include<fstream>

void print_arr(int arr[][10]) {
    for (int i=0;i<10;i++) {
        for (int j =0;j<10;j++)
            std::cout<<arr[j][i]<<" ";
        std::cout<<"\n";
    }

}
int count_arr(int arr[][1000]) {
    int counter =0;
    for (int i=0;i<1000;i++) {
        for (int j =0;j<1000;j++)
            if (arr[j][i] > 1) counter++;
    }
    return counter;
}

int main() {
    std::ifstream input("input.txt", std::ifstream::in);
    std::string line;
    int arr[1000][1000] = {0};
    int x1,y1,x2,y2;
    int lX, hX, lY, hY;

    while (std::getline(input, line)) {
        std::replace(line.begin(),line.end(),',',' ');
        std::istringstream ss(line);
        ss >> x1 >> y1 >> line >> x2 >> y2;
        lX = (x1 >= x2) * x2 + (x1 < x2) * x1;
        hX = (x1 <= x2) * x2 + (x1 > x2) * x1;
        lY = (y1 >= y2) * y2 + (y1 < y2) * y1; 
        hY = (y1 <= y2) * y2 + (y1 > y2) * y1;

        if (x1 < x2 && y1 < y2) {
            for (int i=x1, j=y1; i<=x2; i++, j++)
                arr[i][j]++;
        }
        if (x1 > x2 && y1 > y2) {
            for (int i=x1, j=y1; i>=x2; i--, j--)
                arr[i][j]++;
        }
        if (x1 < x2 && y1 > y2) {
            for (int i=x1, j=y1; i<=x2; i++, j--)
                arr[i][j]++;
        }
        if (x1 > x2 && y1 < y2) {
            for (int i=x1, j=y1; i>=x2; i--, j++)
                arr[i][j]++;
        }

        if (lX == hX)
            for (int i=lY; i <= hY; i++) 
                arr[lX][i]++;
        if (lY == hY)
            for (int i=lX; i <= hX; i++) 
                arr[i][lY]++;
        std::cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
    }
    std::cout<<"\n";
    //print_arr(arr);

    std::cout<<count_arr(arr);
}
