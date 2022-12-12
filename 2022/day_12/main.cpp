#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#define INT_MAX  2147483647
using namespace std;
const int di[4] = {  -1,
                    0,  0,
                      1   };

const int dj[4] = {   0,
                   -1,  1,
                      0   };
bool ok (char a, char b, bool reverse=0) {
    if (reverse)
        return a+1 >= b;
    return a <= b + 1;
}
vector<vector<int>> bfs( vector<string>& in, int si, int sj, bool reverse = 0) {
    vector<vector<int>> dist;
    for ( int i = 0; i < in.size(); i++ ) {
        vector<int> x;
        for ( int j = 0; j < in[i].size(); j++ )
            x.push_back(INT_MAX);
        dist.push_back(x);
    }
    queue<pair<int,int>> q;
    q.push({si,sj});
    dist[si][sj] = 0;
    while (!q.empty()){
        pair<int,int> p = q.front();
        q.pop();
        char c = in[p.first][p.second];
        int ndist = dist[p.first][p.second] + 1;

        for ( int i=0; i<4; i++) {
            int ni = p.first + di[i];
            int nj = p.second + dj[i];
            if ( 0 <= ni && ni < in.size() &&
                 0 <= nj && nj < in[0].size() &&   
                 ndist < dist[ni][nj] ) {
                if (ok(in[ni][nj], c, reverse )) {
                    dist[ni][nj] = ndist;
                    q.push({ni,nj});
                }
            }
        }

    }
    return dist;
}
int main() {
    string s;
    vector<string> input; 
    int si, sj,
        ei, ej;
    while ( getline(cin,s)) {
        input.push_back(s);
        for (int j=0;j<s.length();j++) {
            if (s[j] == 'S') {
                si = input.size() -1, sj = j;
                input[si][sj] = 'a';
            }
            if (s[j] == 'E') {
                ei = input.size() -1, ej = j;
                input[ei][ej] = 'z';
            }
        }
    } 
    
    cout<<bfs(input,si,sj)[ei][ej]<<endl;
    int gold = INT_MAX, bfs_res;
    vector<vector<int>> dist = bfs(input,ei,ej,1);
    for ( int i = 0; i < dist.size(); i++ ){
        for ( int j = 0; j < dist[0].size(); j++)
            if (input[i][j] == 'a' && dist[i][j] < gold)
                gold = dist[i][j];
    }
    cout<<gold<<endl;
}
