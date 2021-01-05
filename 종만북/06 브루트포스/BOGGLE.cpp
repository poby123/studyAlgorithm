#include <iostream>
#include <string>
using namespace std;

char board[5][5];
int mvy[] = {1, 1, 1, 0, 0, -1, -1, -1};
int mvx[] = {1, 0, -1, 1, -1, -1, 0, 1};

bool isRange(int y, int x)
{
    if (0 <= y && y < 5 && 0 <= x && x < 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool hasWord(int y, int x, const string &word)
{
    // 기저사례1 : 시작위치가 범위 밖인 경우
    if (!isRange(y, x))
    {
        return false;
    }

    // 기저 사례2 : 첫글자가 일치하지 않는 경우
    if(board[y][x] != word[0]){
        return false;
    }

    //기저 사례3 : 글자 길이가 1인 경우
    if(word.size() == 1){
        return true;
    }

    //인접한 여덟칸을 검사한다.
    for(int direction=0;direction<8;direction++){
        int nextY = y + mvy[direction];
        int nextX = x + mvx[direction];

        // 첫 글자를 제외한 나머지 문자열을 가지고 재귀적으로 비교.
        if(hasWord(nextY, nextX, word.substr(1))){
           return true; 
        }
    }
    return false;
}

int main()
{

    return 0;
}