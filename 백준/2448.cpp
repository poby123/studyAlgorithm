// https://www.acmicpc.net/problem/2448

#include<iostream>
#include<algorithm>
#define MAX (3*(1<<10)+1)

using namespace std;

int N;
char G[MAX][2 * MAX];

void solve(int y, int x, int size){
    if(size == 3){
        G[y][x] = G[y+1][x-1] = G[y+1][x+1] = G[y+2][x-2] = G[y+2][x-1] = G[y+2][x] = G[y+2][x+1] = G[y+2][x+2] = '*';
        return;
    }
   
    const int half = size / 2;
   
    solve(y, x, half);
    solve(y+half, x-half, half);
    solve(y+half, x+half, half);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    fill(&G[0][0], &G[MAX-1][2*MAX-1], ' ');
    cin >> N;
    solve(1, N, N);
   
    for(int i=1;i<=N;i++){
        for(int j=1;j<=2*N-1;j++){
            cout << G[i][j];
        }
        cout << "\n";
    }
   
    return 0;
}