#include<iostream>
#include<map>

struct node {
    int value;
    node *ancestor;
    std::map<std::string, node> children;
};
int sum_below (node* in) {
    if (in -> children.empty())
        return in -> value;
    for ( auto [ dir, n ] : in -> children) {
        in-> value += sum_below (&n);
    }
    return in -> value;
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
    for ( auto [ dir , n ] : root -> children ) {
        std::cout<<dir<<" "<<n.value<<std::endl;
        if (!n.children.empty()) {
            for (auto [dir2, n2] : n.children )
                std::cout<<dir2<<" "<<n2.value<<std::endl;
        }
    }
    sum_below(root);
}
