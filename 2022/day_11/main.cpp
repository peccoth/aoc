#include <iostream>
#include <queue>
#define MONKEY_AMOUNT 8
#define ull unsigned long long
#define DIVIDE 1

ull modulus = 1;
struct monkey {
    std::queue<ull> items;
    int divisibility;
    char op;
    int m;
    ull inspections = 0;
    short target_true;
    short target_false;
    ull operation() { 
        switch (op) {
            case '^':
                return (this -> items.front() * this -> items.front())% modulus / DIVIDE ;
            case '*':  
                return (this -> items.front() * m)% modulus / DIVIDE;
            case '+':
                return (this -> items.front() + m)% modulus / DIVIDE;
        }
        return 0;
    };
};

int main() {
    std::string str;
    monkey monkeys[MONKEY_AMOUNT];
    for ( int i = 0; i < MONKEY_AMOUNT; i++) {
        getline(std::cin,str);
        getline(std::cin,str);
        size_t c=str.find(':');
        while ( c != std::string::npos) {
            monkeys[i].items.push(stoi(str.substr(c+1,str.find(',')-1)));
            c = str.find(',',c+1);
        }
        getline(std::cin,str);
        
        if (str.substr(str.find_last_of(' ')+1) == "old")
            monkeys[i].op = '^';
        else {
            monkeys[i].m = stoi(str.substr(str.find_last_of(' ')));
            monkeys[i].op = str[23];
        }

        getline(std::cin,str);
        monkeys[i].divisibility = stoi(str.substr(str.find_last_of(' ')));
        getline(std::cin,str);
        monkeys[i].target_true = stoi(str.substr(str.find_last_of(' ')));
        getline(std::cin,str);
        monkeys[i].target_false = stoi(str.substr(str.find_last_of(' ')));
        getline(std::cin,str);
    }
    for ( int i = 0; i<MONKEY_AMOUNT; i++)
        modulus *= monkeys[i].divisibility;
    for (int i = 0; i < 10000; i++) {
        for ( int j = 0; j < MONKEY_AMOUNT; j++) {
            while ( !monkeys[j].items.empty() ) {
                monkeys[j].inspections++;
                if (monkeys[j].operation() % monkeys[j].divisibility == 0) {
                    monkeys[monkeys[j].target_true].items.push(monkeys[j].operation());
                    monkeys[j].items.pop();
                } else {
                    monkeys[monkeys[j].target_false].items.push(monkeys[j].operation());
                    monkeys[j].items.pop();
                }
            }
        }
    }
    ull max = 0, top2 = 0;
    for ( int i = 0; i < MONKEY_AMOUNT; i++) {
        if ( monkeys[i].inspections > top2 ) 
            if (monkeys[i].inspections > max ) {
                top2 = max;
                max = monkeys[i].inspections;
            }
        else
            top2 = monkeys[i].inspections;
    }
    std::cout<<modulus<<std::endl;
    for ( int i = 0; i< MONKEY_AMOUNT;i++)
        std::cout<<monkeys[i].inspections<<std::endl;
    std::cout<<max*top2<<std::endl;
}
