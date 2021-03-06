// https://programmers.co.kr/learn/courses/30/lessons/77486

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define PRICE 100

unordered_map<string, string> parent;
unordered_map<string, int> people;

void calcIncome(string name, int curIncome)
{
    // 기저사례
    if (name == "-")
    {
        return;
    }

    int parentPrice = curIncome * 0.1;

    // 10% 계산 금액이 1원 미만인 경우
    if (parentPrice < 1)
    {
        people[name] += curIncome;
        return;
    }

    // 나머지 경우
    people[name] += (curIncome - parentPrice);
    calcIncome(parent[name], parentPrice);
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount)
{
    vector<int> answer;

    // make map
    for (int i = 0; i < enroll.size(); i++)
    {
        string curName = enroll[i];
        string parentName = referral[i];

        parent[curName] = parentName; // parent.insert({curName, parentName});
        people[curName] = 0;          // people.insert({curName, 0});
    }

    // calc
    for (int i = 0; i < seller.size(); i++)
    {
        calcIncome(seller[i], amount[i] * PRICE);
    }

    // get answer
    for (auto i : enroll)
    {
        answer.push_back(people[i]);
    }

    return answer;
}

int main()
{
    vector<string> enroll = {"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"};
    vector<string> referral = {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"};
    vector<string> seller = {"young", "john", "tod", "emily", "mary"};
    vector<int> amount = {12, 4, 2, 5, 10};

    vector<int> result = solution(enroll, referral, seller, amount);

    cout << "result ===>";
    for (int i : result)
    {
        cout << i << " ";
    }

    return 0;
}