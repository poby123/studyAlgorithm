// https://www.acmicpc.net/problem/1025
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int N, M, ans=-1;
char map[10][11];

bool checkInMap(int y, int x){
    return 0 <= y && y < N && 0 <= x && x < M;
}

// https://teus.me/9
bool isSquare(int num) {
  int temp;
  switch (num & 0x0f) {
  case 0:
  case 1:
  case 4:
  case 9:
    temp = (int)(sqrt((double)num)+0.5);
    return temp*temp == num;
     
  default:
    return false;
  }
}

void solve(int y, int x, int dy, int dx){
    int result = 0;

    while(checkInMap(y, x)){
        int cur = map[y][x] - '0';
        result = result * 10 + cur;
        
        if(isSquare(result)){
            ans = max(ans, result);
        }

        y += dy;
        x += dx;
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;

    for(int i=0;i<N;i++){
        cin >> map[i];
    }

    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            for(int dy=-N;dy<=N;++dy){
                for(int dx=-M;dx<=M;++dx){
                    if(!dy && !dx) continue;
                    solve(i, j, dy, dx);
                }
            }       
        }
    }
    cout << ans << "\n";
    
    return 0;
}