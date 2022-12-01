#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
int main() {
    std::string str = "", input;
    std::ifstream file("input.txt");
    unsigned long sum=0, sum2=0;
    std::vector<unsigned long> scores;
    while (file.good()) {
        sum2=0;
        str = "";
        input = "";
        std::getline(file,input);
        
        char bad = ' ';
        for (auto c : input) {
        switch (c) {
            case '(':
                str+=c;
                break;
            case '[':
                str+=c;
                break;
            case '{':
                str+=c;
                break;
            case '<':
                str+=c;
                break;
            case ')':
                if (str.back() != '(') {
                    sum += 3;
                    bad = c;
                    break;
                } else {
                    str.pop_back();
                    break;
                }
            case ']':
                if (str.back() != '[') {
                    sum += 57;
                    bad = c;
                    break;
                } else {
                    str.pop_back();
                    break;
                }
            case '}':
                if (str.back() != '{') {
                    sum += 1197;
                    bad = c;
                    break;
                } else {
                    str.pop_back();
                    break;
                }
            case '>':
                if (str.back() != '<') {
                    sum += 25137;
                    bad = c;
                    break;
                } else {
                    str.pop_back();
                    break;
                }
            }
        if (bad != ' ') 
            break;
        }
        if (str.length()>0 && bad == ' ') {
            while (str.length() > 0) {
                switch (str.back()) {
                    case '(':
                        sum2 *= 5;
                        sum2 += 1;
                        break;
                    case '[':
                        sum2 *= 5;
                        sum2 += 2;
                        break;
                    case '{':
                        sum2 *= 5;
                        sum2 += 3;
                        break;
                    case '<':
                        sum2 *= 5;
                        sum2 += 4;
                        break;
                }
                str.pop_back();
            }
            scores.push_back(sum2);
        }
    }
    std::sort(scores.begin(), scores.end());
    
    std::cout<<"Part 1: "<<sum<<"\n";
    std::cout<<"Part 2: "<<scores[scores.size()/2];
}
