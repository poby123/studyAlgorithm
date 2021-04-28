// https://programmers.co.kr/learn/courses/30/lessons/77485

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <climits>
#define MAX 101
using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries)
{
    int matrix[MAX][MAX] = {0}, temp[MAX][MAX] = {0};
    const int matrix_size = sizeof(int) * (MAX) * (MAX);

    // answer reserve
    vector<int> answer;
    answer.reserve(queries.size());

    // init matrix
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= columns; j++)
        {
            matrix[i][j] = (i - 1) * columns + j;
        }
    }

    // iterate query
    for (auto query : queries)
    {
        int startR = query[0], startC = query[1], endR = query[2], endC = query[3];
        int ans = INT_MAX;

        // copy
        memcpy(temp, matrix, matrix_size);

        // top line (include right top point)
        for (int i = startC + 1; i <= endC; i++)
        {
            temp[startR][i] = matrix[startR][i - 1];
            ans = min(ans, matrix[startR][i - 1]);
        }

        // right line (include right bottom point)
        for (int i = startR + 1; i <= endR; i++)
        {
            temp[i][endC] = matrix[i - 1][endC];
            ans = min(ans, matrix[i - 1][endC]);
        }

        // bottom line (include left bottom point)
        for (int i = startC; i <= endC - 1; i++)
        {
            temp[endR][i] = matrix[endR][i + 1];
            ans = min(ans, matrix[endR][i + 1]);
        }

        // left line (include left top point)
        for (int i = startR; i <= endR - 1; i++)
        {
            temp[i][startC] = matrix[i + 1][startC];
            ans = min(ans, matrix[i + 1][startC]);
        }

        memcpy(matrix, temp, matrix_size);
        answer.push_back(ans);

        // // print
        // for (int i = 1; i <= rows; i++)
        // {
        //     for (int j = 1; j <= columns; j++)
        //     {
        //         cout << matrix[i][j];
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";
    }

    return answer;
}

int main()
{
    vector<vector<int>> queries = {{1, 1, 2, 2}, {1, 2, 2, 3}, {2, 1, 3, 2}, {2, 2, 3, 3}};
    vector<int> ans = solution(3, 3, queries);

    cout << "answer : ";
    for(auto i : ans){
        cout << i << " ";
    }
    return 0;
}