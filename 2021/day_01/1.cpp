#include<iostream>
#include<cstdio>
using namespace std;

int main() {
    int count=0,prev,curr;
    freopen("1.txt","r",stdin);
    cin>>prev;
    while(!cin.eof()) {
        cin>>curr; 
        count += (curr > prev);
        prev = curr;
    }
    cout<<count;
}
