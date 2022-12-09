#include<iostream>
#include<set>
#include<utility>

int main() {
    int tx = 0, ty = 0;
    int hx = 0, hy = 0;
    std::set<std::pair<int,int>> unique;
    char direction;
    int distance;
    while (std::cin.peek() != EOF) {
        std::cin>>direction>>distance;
        switch (direction) {
            case 'U':
                while (distance --> 0) {
                    hy += 1;
                    tx += (hx-tx) > 0 & (hy-ty) > 1;
                    tx -= (tx-hx) > 0 & (hy-ty) > 1;
                    ty += (hy-ty) > 1;
                    unique.insert({ty,tx});
                    std::cout<<hy<<" "<<hx<<std::endl;
                    std::cout<<ty<<" "<<tx<<std::endl<<std::endl;
                }
                break;
            case 'D':
                while (distance --> 0) {
                    hy -= 1;
                    tx += (hx-tx) > 0 & (ty-hy) > 1;
                    tx -= (tx-hx) > 0 & (ty-hy) > 1;
                    ty -= (ty-hy) > 1;
                    unique.insert({ty,tx});
                    std::cout<<hy<<" "<<hx<<std::endl;
                    std::cout<<ty<<" "<<tx<<std::endl<<std::endl;
                }
                break;
            case 'L':
                while (distance --> 0) {
                    hx -= 1;
                    ty += (hy-ty) > 0 & (tx-hx) > 1 ;
                    ty -= (ty-hy) > 0 & (tx-hx) > 1 ;
                    tx -= (tx-hx) > 1;
                    unique.insert({ty,tx});
                    std::cout<<hy<<" "<<hx<<std::endl;
                    std::cout<<ty<<" "<<tx<<std::endl<<std::endl;
                }
                break;
            case 'R':
                while (distance --> 0) {
                    hx += 1;
                    ty += (hy-ty) > 0 & (hx-tx) > 1 ;
                    ty -= (ty-hy) > 0 & (hx-tx) > 1 ;
                    std::cout<<ty-hy<<std::endl;
                    tx += (hx-tx) > 1;
                    unique.insert({ty,tx});
                    std::cout<<hy<<" "<<hx<<std::endl;
                    std::cout<<ty<<" "<<tx<<std::endl<<std::endl;
                }
                break;

        }
    }
    std::cout<<unique.size();

}
