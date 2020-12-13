/*
문제
크기가 N*N인 행렬 A가 주어진다. 이때, A의 B제곱을 구하는 프로그램을 작성하시오. 수가 매우 커질 수 있으니, A^B의 각 원소를 1,000으로 나눈 나머지를 출력한다.

입력
첫째 줄에 행렬의 크기 N과 B가 주어진다. (2 ≤ N ≤  5, 1 ≤ B ≤ 100,000,000,000)

둘째 줄부터 N개의 줄에 행렬의 각 원소가 주어진다. 행렬의 각 원소는 1,000보다 작거나 같은 자연수 또는 0이다.

출력
첫째 줄부터 N개의 줄에 걸쳐 행렬 A를 B제곱한 결과를 출력한다.

예제 입력 1 
2 5
1 2
3 4
예제 출력 1 
69 558
337 406

예제 입력 2 
3 3
1 2 3
4 5 6
7 8 9
예제 출력 2 
468 576 684
62 305 548
656 34 412

예제 입력 3 
5 10
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
예제 출력 3 
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
*/
/*
발생했던 문제들 : 
    문제1. 시간초과 => 메모제이션을 통해 최적화. https://www.acmicpc.net/board/view/56387
    문제2. 1000인 정방행렬의 1제곱일 때의 예외 => 예외처리. https://www.acmicpc.net/board/view/26901
*/
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int n;
long long b;

class Matrix
{
private:
    long long matrix[5][5];

public:
    Matrix(long long (*m)[5])
    {
        memcpy(this->matrix, m, sizeof(matrix));
    }
    Matrix pow(long long k)
    {
        //문제2에 대한 처리
        if (k == 1)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    this->matrix[i][j] %= 1000;
                }
            }
            return Matrix(this->matrix);
        }
        else if (k == 2)
        {
            return Matrix(this->matrix) * Matrix(this->matrix);
        }
        else if (k % 2 != 0)
        {
            return this->pow(k - 1) * this->pow(1);
        }
        else
        {
            //문제1에 대한 처리. 메모제이션
            Matrix memo = this->pow(k / 2);
            return memo * memo;
        }
    }
    Matrix operator*(const Matrix &m)
    {
        long long temp[5][5];
        memcpy(temp, m.matrix, sizeof(temp));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                temp[i][j] = 0;
                for (int k = 0; k < n; ++k)
                {
                    temp[i][j] += this->matrix[i][k] * m.matrix[k][j];
                }
                temp[i][j] %= 1000;
            }
        }
        return Matrix(temp);
    }
    void print()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << this->matrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> b;

    long long matrix[5][5] = {0};

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> matrix[i][j];
        }
    }

    Matrix m(matrix);
    Matrix result = m.pow(b);
    result.print();

    return 0;
}