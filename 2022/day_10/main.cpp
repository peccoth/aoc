#include<iostream>
using std::cin, std::cout, std::endl;

int main() {
    int cycle = 0, X = 1, diff;
    std::string op;
    while ( cin >> op) {
        if (op[0] == 'n') {
            cycle = cycle + 1;
            if ( X - 1 == (cycle % 40) || X == (cycle % 40) || X + 1 == (cycle % 40) )
                cout<<'#';
            else
                cout<<'.';
            if (cycle %40 == 0)
                cout<<endl;
            continue;
        }
        cycle = cycle + 1;
        if ( X - 1 == (cycle % 40) || X == (cycle % 40) || X + 1 == (cycle % 40) )
            cout<<'#';
        else
            cout<<'.';
        if (cycle %40 == 0)
            cout<<endl;
        cin >> diff;
        X += diff;
        cycle = cycle + 1;
        if ( X - 1 == (cycle % 40) || X == (cycle % 40) || X + 1 == (cycle % 40) )
            cout<<'#';
        else
            cout<<'.';
        if (cycle %40 == 0)
            cout<<endl;
    }
}
