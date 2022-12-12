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
int bfs( vector<string>& in, int si, int sj, int ei, int ej) {
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
                if ( in[ni][nj] <= c + 1 ) {
                    dist[ni][nj] = ndist;
                    q.push({ni,nj});
                }
            }
        }

    }
    return dist[ei][ej];
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
    
    vector<vector<int>> dist;
    for ( int i = 0; i < input.size(); i++ ) {
        vector<int> x;
        for ( int j = 0; j < input[i].size(); j++ )
            x.push_back(INT_MAX);
        dist.push_back(x);
    }
    queue<pair<int,int>> q;
    q.push({si,sj});
    dist[si][sj] = 0;
    while (!q.empty()){
        pair<int,int> p = q.front();
        q.pop();
        char c = input[p.first][p.second];
        int ndist = dist[p.first][p.second] + 1;

        for ( int i=0; i<4; i++) {
            int ni = p.first + di[i];
            int nj = p.second + dj[i];
            if ( 0 <= ni && ni < input.size() &&
                 0 <= nj && nj < input[0].size() &&   
                 ndist < dist[ni][nj] ) {
                if ( input[ni][nj] <= c + 1 ) {
                    dist[ni][nj] = ndist;
                    q.push({ni,nj});
                }
            }
        }

    }
    int gold = INT_MAX, bfs_res;
    for ( int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++ ){
            if (input[i][j] == 'a') {
                bfs_res = bfs(input,i,j,ei,ej);
                if (bfs_res < gold) 
                    gold = bfs_res;
            }
        }
    }
    cout<<bfs(input,si,sj,ei,ej)<<endl;
    cout<<gold<<endl;
}
