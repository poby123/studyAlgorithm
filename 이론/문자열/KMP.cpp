#include <iostream>
#include <vector>
using namespace std;

vector<int> makeTable(string pattern)
{
    int patternSize = pattern.size();
    vector<int> table(patternSize, 0); // 최대 일치 테이블

    int j = 0;
    for (int i = 1; i < patternSize; i++)
    {
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = table[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            table[i] = ++j;
        }
    }
    return table;
}

void KMP(const string &text, const string &pattern)
{
    vector<int> table = makeTable(pattern);

    int textSize = text.size();
    int patternSize = pattern.size();

    int i = 0; //index for text
    int j = 0; //index for pattern

    while(i < textSize){
        // 일치
        if(pattern[j] == text[i]){
            // 다음 비교를 위해 i, j 인덱스를 모두 증가시킴.
            ++j;
            ++i;
        }

        // 일치했는데, 패턴의 인덱스가 마지막이었다면, 맞는 문자열을 발견한 것.
        if(j == patternSize){
            cout << "Found pattern at index " << i - j << "\n";
            j = table[j - 1]; // 이어서 찾기 위해, j 값을 한 칸 이전 테이블의 값으로 업데이트
        }

        // 불일치 발생.
        else if(i < textSize && pattern[j] != text[i]){
            if (j == 0)
            {
                // j가 0이면 i만 1증가.
                ++i;
            }
            else{
                // 한 칸 이전 테이블의 값으로 j를 업데이트.
                j = table[j - 1];
            }
        }
    }

}

int main()
{
    string text = "ababacabacaabacaaba";
    string pattern = "abacaaba";

    KMP(text, pattern);
    return 0;
}