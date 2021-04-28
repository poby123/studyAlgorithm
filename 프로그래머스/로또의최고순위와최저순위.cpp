// https://programmers.co.kr/learn/courses/30/lessons/77484

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums)
{
    vector<int> answer;
    set<int> win_set, lotto_set;

    int correct = 0, num_zero = 0, score_list[] = {6, 6, 5, 4, 3, 2, 1};

    // vector to set
    for (size_t i = 0; i < 6; i++)
    {
        if (!lottos[i])
        {
            ++num_zero;
        }
        else
        {
            lotto_set.insert(lottos[i]);
        }
        win_set.insert(win_nums[i]);
    }

    // find same items
    for (auto item : win_set)
    {
        if (lotto_set.find(item) != lotto_set.end())
        {
            ++correct;
        }
    }

    answer.push_back(score_list[correct + num_zero]);
    answer.push_back(score_list[correct]);

    return answer;
}

int main()
{
    vector<int> lottos = {0, 0, 0, 0, 0, 0}, win_nums = {38, 19, 20, 40, 15, 25};
    vector<int> ans = solution(lottos, win_nums);

    for (auto i : ans)
    {
        cout << i << " ";
    }

    return 0;
}