#include<iostream>
#include<cstdio>
int main() {
    freopen("input.txt","r",stdin); 
    std::string in;
    int data[12] = {0};
    for (int i=0;i<1000;i++) {
        std::cin>>in; 
        std::cout<<in<<" ";
        for (int j=0;j<12;j++) {
            if (in[j] == '1')
                data[j]++ ;
        }
        for (int j=0;j<12;j++) 
            std::cout<<data[j]<<" ";
        std::cout<<" \n";
    }
    int epsilon=0, gamma=0;
    for (int i=0;i<12;i++) 
        std::cout<<(int)(data[i] > 500);
    std::cout<<"\n";
    for (int i=0;i<12;i++) {
        epsilon += (data[i] > 500);
        epsilon = epsilon << 1;
    }
    epsilon = epsilon >> 1;
    std::cout<<"\n"<<epsilon<<" " << gamma<<"\n";
}
