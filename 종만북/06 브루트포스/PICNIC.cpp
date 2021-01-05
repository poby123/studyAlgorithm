#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int C, N, M, check[10];
bool areFriends[10][10];

int makePair()
{
    int firstFree = -1;

    // 남은 학생들중에서 가장 빠른 번호를 찾는다.
    for (int i = 0; i < N; i++)
    {
        if (!check[i])
        {
            firstFree = i;
            break;
        }
    }

    //기저 사례1 : 남은 학생이 없는 경우
    if (firstFree == -1)
    {
        return 1;
    }

    int ret = 0;
    for (int pairWith = firstFree + 1; pairWith < N; pairWith++)
    {
        if (!check[pairWith] && areFriends[firstFree][pairWith])
        {
            check[firstFree] = check[pairWith] = true;
            ret += makePair();
            check[firstFree] = check[pairWith] = false;
        }
    }

    return ret;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> C;
    for (int t = 0; t < C; t++)
    {
        cin >> N >> M;

        memset(areFriends, 0, sizeof(areFriends));
        memset(check, 0, sizeof(check));

        for (int m = 0; m < M; m++)
        {
            int f1, f2;
            cin >> f1 >> f2;
            areFriends[f1][f2] = true;
            areFriends[f2][f1] = true;
        }

        cout << makePair() << "\n";
    }

    return 0;
}