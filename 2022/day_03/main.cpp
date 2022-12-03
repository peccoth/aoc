#include<iostream>
#include<fstream>
#include<string>

int main() {
    std::ifstream input("input");
    int priority_sum = 0;

    std::string line;
    size_t dupe;
    while (getline(input,line)) {
        std::string already_found = "";
        for (int i=0;i<line.length()/2;i++) {
            dupe = line.find(line[i],line.length()/2);
            if (already_found.find(line[dupe]) != std::string::npos) {
                break;
            }
            if (dupe != std::string::npos) {
                already_found += line[dupe];
                priority_sum += (int)line[dupe] > 97 ? (int)line[dupe] - 96 : (int)line[dupe] - 38;
            }

        }
    }
    std::cout<<priority_sum<<std::endl;

    input.clear();
    input.seekg(0,std::ios::beg);
    std::string potential_badges = "";
    std::string new_potential_badges = "";
    int n = 0, score = 0;
    size_t unique;
    while (getline(input,line)) {
        if (n % 3 == 0) {
            potential_badges = line;
            new_potential_badges = "";
            n++;
            continue;
        }

        for (int i = 0; i<potential_badges.length();i++) {
            unique = line.find(potential_badges[i]);
            if (unique != std::string::npos) {
                new_potential_badges += line[unique];
            }
        }
        if (n % 3 == 2) {
            score += (int)new_potential_badges[0] > 97 ? (int)new_potential_badges[0] - 96 : (int)new_potential_badges[0] - 38;
        }
        potential_badges = new_potential_badges;
        new_potential_badges = "";
        n++;
    }
    std::cout<<score<<std::endl;
}
