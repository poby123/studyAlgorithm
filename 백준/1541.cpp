/*
문제
세준이는 양수와 +, -, 그리고 괄호를 가지고 길이가 최대 50인 식을 만들었다. 그리고 나서 세준이는 괄호를 모두 지웠다.

그리고 나서 세준이는 괄호를 적절히 쳐서 이 식의 값을 최소로 만들려고 한다.

괄호를 적절히 쳐서 이 식의 값을 최소로 만드는 프로그램을 작성하시오.

입력
첫째 줄에 식이 주어진다. 식은 ‘0’~‘9’, ‘+’, 그리고 ‘-’만으로 이루어져 있고, 가장 처음과 마지막 문자는 숫자이다. 그리고 연속해서 두 개 이상의 연산자가 나타나지 않고, 5자리보다 많이 연속되는 숫자는 없다. 수는 0으로 시작할 수 있다.

출력
첫째 줄에 정답을 출력한다.

예제 입력 1 
55-50+40
예제 출력 1 
-35
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define SUB -2

int main()
{
    //입력을 빨리 받기 위함.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //변수선언
    string input;
    int result = 0, i = 0, num = 0;
    vector<int> nums;

    //입력받기
    cin >> input;

    //문자열 순회
    while (i < input.length())
    {
        //문자열이 숫자면 정수 형태로 보관.
        if ('0' <= input[i] && input[i] <= '9')
        {
            num *= 10;
            num += input[i] - '0';
        }

        // - 면 보관한 정수와 빼기표시를 벡터에 넣고, 정수를 보관하는 데 사용한 변수는 초기화한다.
        else if (input[i] == '-')
        {
            nums.push_back(num);
            nums.push_back(SUB);
            num = 0;
        }

        // + 면 보관한 정수를 벡터에 넣고, 초기화한다.
        else if (input[i] == '+')
        {
            nums.push_back(num);
            num = 0;
        }
        ++i;
    }

    nums.push_back(num); //연산자 이후에 남은 숫자 털어넣기

    auto it = nums.begin();
    result += *it;

    bool flag = false; // 빼기가 나왔는지 체크하는 flag.
    for (++it; it != nums.end(); it++)
    {
        // 빼기가 나왔으면 flag에 표시한다.
        if (*it == SUB)
        {
            flag = true;
            continue;
        }

        // 값을 최소로 만들어야 되기 때문에, 한번이라도 빼기가 나온 적이 있다면 계속 빼면 된다.(그리디 알고리즘)
        if (flag)
        {
            result -= *it;
        }

        //빼기가 나온적이 없다면 더해야한다.
        else
        {
            result += *it;
        }
    }

    cout << result << "\n";

    return 0;
}