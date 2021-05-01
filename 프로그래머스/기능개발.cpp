// https://programmers.co.kr/learn/courses/30/lessons/42586

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds)
{
    vector<int> answer;
    int end = -1;

    // iterate days
    for (int t = 0; end != progresses.size() - 1; t++)
    {
        // iterate progresses
        for (int i = 0; i < progresses.size(); i++)
        {
            progresses[i] += speeds[i];
        }

        // check end
        int ans = 0;
        for (int i = end + 1; i < progresses.size(); i++)
        {
            if (progresses[i] < 100)
            {
                break;
            }
            end = i;
            ++ans;
        }

        // make answer
        if (ans > 0)
        {
            answer.push_back(ans);
        }
    }

    return answer;
}

int main()
{

    vector<int> progresses = {93, 30, 55}, speed = {1, 30, 5};
    vector<int> answer = solution(progresses, speed);

    for (auto item : answer)
    {
        cout << item << " ";
    }
    cout << "\n";

    return 0;
}