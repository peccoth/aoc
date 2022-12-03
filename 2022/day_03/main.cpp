#include<stdio.h>
#include<fstream>
#include<string>
#include<cstring>

int main() {
    std::fstream input("input");
    std::string line;

    int priority_sum = 0;
    bool found[256]={0};
    size_t dupe;

    int n = 0, score = 0;
    bool potential_badges[512] = {0};

    while (getline(input,line)) {
        memset(found,0,sizeof(found));
        for (size_t i = 0; i < line.length()/2; i++) {
            dupe = line.find(line[i], line.length()/2);
            if ( dupe == -1 )
                continue;
            if (found[line[dupe]]) 
                break;
            found[line[dupe]] = 1;
            priority_sum += (int)line[dupe] > 97 ? (int)line[dupe] - 96 : (int)line[dupe] - 38;
        }

        if (n < 2) {
            for (auto x : line) 
                potential_badges[x + 256 * n] = 1;
            n++;
        } else {
            for (auto x : line) {
                if (potential_badges[x] + potential_badges[x + 256] == 2) {
                    score += (int)x > 97 ? (int)x - 96 : (int)x - 38;
                    memset(potential_badges,0,sizeof(potential_badges));
                    n = 0;
                    break;
                }
            }
        }
    }
    printf("%d \n",priority_sum);
    printf("%d \n",score);
}
