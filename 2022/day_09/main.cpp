#include<iostream>
#include<set>
#include<array>
#include<utility>
#define LENGTH 10 
#define PX snake[i-1].first
#define PY snake[i-1].second
#define CX snake[i].first
#define CY snake[i].second

int main() {
    std::array<std::pair<int,int>,LENGTH> snake;
    std::set<std::pair<int,int>> gold, silver;
    char direction;
    int distance;
    while (std::cin.peek() != EOF) {
        std::cin>>direction>>distance;
        while (distance --> 0) {
            snake[0].first += direction == 'R';
            snake[0].first -= direction == 'L';
            snake[0].second += direction == 'U';
            snake[0].second -= direction == 'D';

            for (int i = 1; i < LENGTH; i++) {
                if (PX - CX > 1) {
                    CY += PY > CY;
                    CY -= CY > PY;
                    CX++;
                }

                if (CX - PX > 1) {
                    CY += PY > CY;
                    CY -= CY > PY;
                    CX--;
                }

                if (PY - CY > 1) {
                    CX += PX > CX;
                    CX -= CX > PX;
                    CY++;
                }

                if (CY - PY > 1) {
                    CX += PX > CX;
                    CX -= CX > PX;
                    CY--;
                }
            }
            
            silver.insert(snake[1]);
            gold.insert(snake[LENGTH-1]);
        }
    }
    std::cout<<silver.size()<<" "<<gold.size();
}
