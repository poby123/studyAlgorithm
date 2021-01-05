/*
    분할정복 알고리즘은 크게 3가지 요소로 이루어져 있다.
    1. divide: 문제를 더 작은 문제로 분할하는 과정
    2. merge : 각 문제에 대해 구한 답은 원래 문제에 대한 답으로 병합하는 과정
    3. base case: 더 이상 답을 분할하지 않고 곧장 풀 수 있는 매우 작은 문제 

    n이 짝수일 때
    fastSum(n) 
    = 1 + 2 + ... + (n/2) + (n/2+1) + ... + n
    = {1 + 2 + (n/2)} + {(n/2+1) + ... + n}
    = fastSum(n/2) + {(n/2+1) + (n/2+2) + ... + (n/2+n/2)}
    = fastSum(n/2) + { n/2*n/2 + (1 + 2 + ... n/2 )}
    = fastSum(n/2) + n^2/4 + fastSum(n/2)
    = 2*fastSum(n/2) + n^2/4
*/

#include <iostream>
using namespace std;

//시간 복잡도 : 호출할 때마다 최소한 2번의 한번꼴로 n이 절반으로 줄어들기 때문에, O(n)보다 빠른 O(lg n) 이 된다.
int fastSum(const int &n)
{
    //기저 사례
    if (n == 1)
        return 1;
    if (n % 2 == 1)
        return fastSum(n - 1) + n;
    return 2 * fastSum(n / 2) + (n / 2) * (n / 2);
}

int main()
{
    int n = 0;
    cout << "input: ";
    cin >> n;

    cout << fastSum(n) << "\n";
    return 0;
}