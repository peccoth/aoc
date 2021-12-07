#include<iostream>
#include<sstream>
#include<algorithm>

int main() {
    freopen("input.txt","r",stdin);
    int arr[1000][1000] = {0};
    int x1,y1,x2,y2, lowerX, lowerY, upperX, upperY;
    std::string input;
    for (int i=0;i<500;i++) {
        getline(std::cin,input); 
        std::replace(input.begin(),input.end(),',',' ');
        std::stringstream ss;
        ss << input;
        ss >> x1 >> y1 >> input >> x2 >> y2;
        lowerX = (x1 <= x2) * x1 + (x1 > x2) * x2;
        lowerY = (y1 < y2) * y1 + (y1 > y2) * y2;
        upperX = (x1 >= x2) * x1 + (x1 < x2) * x2;
        upperY = (y1 > y2) * y1 + (y1 < y2) * y2;
        for (int j=lowerX, k = lowerY;
             j < upperX || k < upperY;
             j+=(j < upperX), k += (k < upperY) ) {
            arr[j][k]++;
        }
    }
    int counter = 0;
    for (int i=0;i<1000;i++) {
        for (int j=0;j<1000;j++)
            counter += arr[i][j] > 1;
    }
    std::cout<<counter<<"\n";

}
