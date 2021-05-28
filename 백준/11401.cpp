/*
문제
자연수 N과 정수 K가 주어졌을 때 이항 계수 nCk 를 1,000,000,007로 나눈 나머지를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ N ≤ 4,000,000, 0 ≤ K ≤ N)

출력
nCk 를 1,000,000,007로 나눈 나머지를 출력한다.
*/

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 4000000
#define P 1000000007

using ll = long long;

int N, K;
ll ans, fact[MAX + 1] = {1, 1}; // fact[i]에는 i! % P를 저장.

//분할 정복을 이용하여 x^y 구하기
ll power(ll x, ll y)
{
    ll ret = 1;
    while (y > 0)
    {
        if (y % 2)
        {
            ret *= x;
            ret %= P;
        }
        x *= x;
        x %= P;
        y /= 2;
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 2; i <= N; i++)
    {
        fact[i] = (i * fact[i - 1]) % P;
    }

    // 이항계수 정의 = nCk = n! / (k!(n-k)!)
    // 구해야하는 것은 nCk % p.
    // nCk % p = (n! / (k!(n-k)!)) % p
    // 여기서 한 가지 알아둬야하는 것은 (a * b) % p == (a % p) * (b % p)는 성립하지만, (a / b) % p == (a % p) / (b % p)는 성립하지 않는다는 것이다.

    // 따라서 nCk % p != (n! % p) / (k!(n-k)! % p)이기 때문에, 분모를 분자로 올려서 나누기를 곱하기로 바꿔야하는데, 이때 페르마의 소정리를 사용할 수 있다.
    // 페르마의 소정리에 따르면 p가 소수일 때, n^(-1) % p == n^(p-2) 이므로,
    // 분모 부분 ((k!(n-k)!)^(-1) % p을 (k!(n-k)!)^(p-2)로 바꿀 수 있다.
    // 따라서 nCk % p == (n! % p) * (k!(n-k)!)^(p-2)가 성립한다.

    // 실제 프로그램에서는 오버플로우를 막기 위해 나머지 연산을 한 번 더 써줬다.
    ans = (fact[N] * power((fact[K] * fact[N - K]) % P, P - 2)) % P;

    cout << ans;
    return 0;
}