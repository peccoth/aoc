#include<iostream>
#include<map>
#define DISK_SIZE 70000000
#define REQUIRED_SPACE 30000000

struct node {
    int value;
    node *ancestor;
    std::map<std::string, node> children;
};
int sum_below (node* in) { if (in -> children.empty())
        return in -> value;
    for ( auto& [ dir, n ] : in -> children) {
        in-> value += sum_below (&n);
    }
    return in -> value;
}
int silver = 0;
void silver_check (node* in) {
    if (in -> value < 100000)
        silver += in -> value;
    if (!in -> children.empty() ) {
        for (auto& [dir, n] : in -> children) {
            silver_check(&n);
        }
    }
}
int smallest_size = DISK_SIZE;
int space_left = DISK_SIZE;
void gold_check (node* in) {
    if ( space_left + in -> value >= REQUIRED_SPACE ) {
        if (smallest_size > in -> value)
            smallest_size = in -> value;
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
    
    //std::cout<<silver<<std::endl;
    space_left -= root -> value;
    gold_check(root);
    std::cout<<space_left<<" "<<smallest_size<<std::endl;
}
