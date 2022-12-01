#include<iostream>

int main() {
    std::string input ="413243144111524421234124345113121411341251422111315312111141112213131345122111415131341323444345131351111124121115112131423443113531152411351431142111111311111451253113111151251111113513211111114511315111133111441141214411343541141311551212123113112113431133512141121311111114551114111212131311111115"; 
    unsigned long fishes[9] = {0};
    unsigned long temp[9] = {0};
    for (auto x : input)
        fishes[(int)x - 48] ++;
    for (int i=0;i<256;i++) {    
        temp[8] = fishes[0];
        temp[7] = fishes[8];
        temp[6] = fishes[0] + fishes[7];
        for (int i=0;i<6;i++) 
            temp[i] = fishes[i+1];
        for (int i=0;i<9;i++)
            fishes[i] = temp[i];
    }
    unsigned long long int count = 0;
    for (int i=0;i<9;i++)
        count += fishes[i];
    std::cout<<count;
}
