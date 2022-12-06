#include<iostream>
#include<stdlib.h>
int solve(char *in, int size) {
    int result = 0;
    for (result=0; in[result + size] != '\0'; result++){
        bool found[26] = { 0 };
        int success = 0;
        for (int i = 0; i < size; i++)
            found[in[result + i] - 'a'] = 1;
        for (int i = 0; i < 26; i++)
            success += found[i];
        if (success > size - 1)
            return result + size;
    }
    return -1;
}

int main() {
    char * str = (char*)calloc(100000001, sizeof(char));
    std::cin>>str;
    str[100000000] = '\0';

    int silver = solve(str,4);
    int gold = solve(str,14);

    std::cout<<silver<<" "<<gold<<std::endl;
}
