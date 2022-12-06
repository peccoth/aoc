#include<iostream>
#include<list>
using std::prev;
bool doublecheck(std::list<char> in) {  
    bool out = 0;
    int i=0, j=0;
    for (auto x : in) {
        for (auto y : in) {
            if (i == j)
                continue;
            if (x == y)
                out = 1;
            j++;
        }
        i++;
        j=0;
    }
    return out;
}

int main() {
    char c;
    std::list<char> last14;
    std::list<char> last4;
    int silver = 14, gold = 14;
    for (int i = 0; i<14; i++) {
        c = std::cin.get(); 
        last14.push_back(c);
    }
    auto it = last14.end();
    it = prev(it,1);
    last4.push_front(*it);
    it = prev(it,1);
    last4.push_front(*it);
    it = prev(it,1);
    last4.push_front(*it);
    it = prev(it,1);
    last4.push_front(*it);

    bool a = 0, b = 0;
    bool silver_done = 0;
    while (1) {
        c = std::cin.get(); 
        silver+= (!silver_done);
        gold++;

        last4.pop_front();
        for (auto x : last4) {
            if ( x == c)
                a = 1;
        }
        last4.push_back(c);
        
        last14.pop_front();
        for (auto x : last14) {
            if ( x == c)
                b = 1;
        }
        last14.push_back(c);
        
        if (a==0 && silver_done == 0) {
            if (doublecheck(last4) == 0) 
                silver_done = 1;
        }
        if (b==0 ) {
            if (doublecheck(last14) == 0) 
                break;
        }

        if (c == EOF) {
            std::cout<<"Reached end of file! \n";
            break;
        }

        a = 0;
        b = 0;
    }

    std::cout<<silver<<" "<<gold<<std::endl;
}
