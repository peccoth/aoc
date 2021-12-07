#include<iostream>

int main() {
    char *fishes ="413243144111524421234124345113121411341251422111315312111141112213131345122111415131341323444345131351111124121115112131423443113531152411351431142111111311111451253113111151251111113513211111114511315111133111441141214411343541141311551212123113112113431133512141121311111114551114111212131311111115"; 
    char *temp; 
    for (int i=0;i<256;i++) {
        for (unsigned long long i = 0;i<sizeof(fishes) / sizeof(char);i++) {
            if ((int)fishes[i] == 48) {
                temp += '6'; 
                temp += '8'; 
                continue;
            }
            temp + (char)(int)fishes[i] - 1; 
        }
        fishes = temp;
        temp = "";
    }
    std::cout<<sizeof(fishes)/sizeof(char);
}
