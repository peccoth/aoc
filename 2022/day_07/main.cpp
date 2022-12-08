#include<iostream>
#include<unordered_map>
#define DISK_SIZE 3000000000
//#define DISK_SIZE 70000000
#define REQUIRED_SPACE 700000000
//#define REQUIRED_SPACE 30000000

struct node {
    unsigned long long value;
    node *ancestor;
    std::unordered_map<std::string, node> children;
};
unsigned long long sum_below (node* in) { if (in -> children.empty())
        return in -> value;
    for ( auto& [ dir, n ] : in -> children) {
        in-> value += sum_below (&n);
    }
    return in -> value;
}
unsigned long long silver = 0;
void silver_check (node* in) {
    if (in -> value < 100000)
        silver += in -> value;
    if (!in -> children.empty() ) {
        for (auto& [dir, n] : in -> children) {
            silver_check(&n);
        }
    }
}
unsigned long long gold = DISK_SIZE;
unsigned long long space_left = DISK_SIZE;

void gold_check (node* in) {
    if ( space_left + in -> value >= REQUIRED_SPACE ) {
        if (gold > in -> value)
            gold = in -> value;
    }
    if (!in -> children.empty()) {
        for (auto& [dir, n] : in -> children) {
            gold_check(&n);
        }
    }
}
int main() {
    std::string in;
    node nodes;
    nodes.value = 0;

    node *current_node = &nodes; 
    node *root = &nodes;
    while (getline(std::cin,in)) {
        if (in == "$ ls") {
            while ( std::cin.peek() != '$' && std::cin.peek() != EOF) {
                getline(std::cin,in);
                if (in[0] == 'd') {
                    std::string dirname = in.substr(in.find_last_of(' ') + 1);
                    current_node -> children[dirname].value = 0;
                    current_node -> children[dirname].ancestor = current_node;
                } else {
                    current_node -> value += std::stoi(in.substr(0,in.find(' ')));
                }
            }
        } else if ( in == "$ cd /" ) {
            current_node = root;
        } else if ( in == "$ cd ..") {
            current_node = current_node -> ancestor;
        } else {
            current_node = &(current_node -> children[in.substr(in.find_last_of(' ') +1)]);
        }
    }
    sum_below(root);
    silver_check(root);
    
    space_left -= root -> value;
    gold_check(root);
    std::cout<<silver<<" "<<gold<<std::endl;
}
