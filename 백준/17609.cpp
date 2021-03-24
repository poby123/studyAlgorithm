/*
문제
회문(回文) 또는 팰린드롬(palindrome)은 앞 뒤 방향으로 볼 때 같은 순서의 문자로 구성된 문자열을 말한다. 
예를 들어 ‘abba’ ‘kayak’, ‘reviver’, ‘madam’은 모두 회문이다. 
만일 그 자체는 회문이 아니지만 한 문자를 삭제하여 회문으로 만들 수 있는 문자열이라면 우리는 이런 문자열을 “유사회문”(pseudo palindrome)이라고 부른다. 
예를 들어 ‘summuus’는 5번째나 혹은 6번째 문자 ‘u’를 제거하여 ‘summus’인 회문이 되므로 유사회문이다.

여러분은 제시된 문자열을 분석하여 그것이 그 자체로 회문인지, 또는 한 문자를 삭제하면 회문이 되는 “유사회문”인지, 아니면 회문이나 유사회문도 아닌 일반 문자열인지를 판단해야 한다. 
만일 문자열 그 자체로 회문이면 0, 유사회문이면 1, 그 외는 2를 출력해야 한다. 

입력
입력의 첫 줄에는 주어지는 문자열의 개수를 나타내는 정수 T(1 ≤ T ≤ 30)가 주어진다. 다음 줄부터 T개의 줄에 걸쳐 한 줄에 하나의 문자열이 입력으로 주어진다. 
주어지는 문자열의 길이는 3 이상 100,000 이하이고, 영문 알파벳 소문자로만 이루어져 있다.

출력
각 문자열이 회문인지, 유사 회문인지, 둘 모두 해당되지 않는지를 판단하여 회문이면 0, 유사 회문이면 1, 둘 모두 아니면 2를 순서대로 한 줄에 하나씩 출력한다.

*/

#include <iostream>
using namespace std;

int N;
int check(const string &s, const int l, const int r, const int chance)
{
    int cand = -1;
    if (l >= r)
    {
        return !chance;
    }
    if (s[l] == s[r])
    {
        return check(s, l + 1, r - 1, chance);
    }

    if (l + 1 < r && chance > 0 && s[l + 1] == s[r])
    {
        cand = check(s, l + 2, r - 1, chance - 1);
        if (cand == 0 || cand == 1)
        {
            return cand;
        }
    }
    if (l < r - 1 && chance > 0 && s[l] == s[r - 1])
    {
        cand = check(s, l + 1, r - 2, chance - 1);
        if (cand == 0 || cand == 1)
        {
            return cand;
        }
    }

    return 2;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string temp;
        cin >> temp;
        cout << check(temp, 0, temp.size() - 1, 1) << "\n";
    }

    return 0;
}


// int check(const string& s){
//     int l = 0;
//     int r = s.size()-1;
//     int skipNum = 0;

//     while(l < r){
//         if(s[l] == s[r]){
//             ++l;
//             --r;
//         }
//         else if(!skipNum && l+1 < r && s[l+1] == s[r]){
//             ++skipNum;
//             l+=2;
//             --r;
//         }
//         else if(!skipNum && l < r-1 && s[l] == s[r-1]){
//             ++skipNum;
//             r-=2;
//             ++l;
//         }
//         else{
//             return 2;
//         }
//     }
//     return skipNum;
// }
// 
// 반례 ↓
// 입력 :
// 1
// baaba

// 정답 :
// 1

// 출력 :
// 2