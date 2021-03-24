/*
문제
성공한 벤쳐회사 "봉씨"의 데이터 분석원 이석원은 매일매일 전세계 사용자에 대한 정보를 받은뒤 이를 시각화한다. 이석원은 자신이 만든 시각화 툴을 이용한다.

아래 그림은 이석원의 시각화 툴을 이용해서 만든 히스토그램이다.



위의 예에서 구간 0-9는 5번 발생했고, 10-19는 3번, 20-29와 30-39는 한 번씩 발생한 것이다.

이석원의 히스토그램 생성 프로그램은 매우 간단하다. 먼저, 히스토그램의 높이는 고정되어 있다. 
즉, 가장 높은 막대의 높이는 항상 일정하고, 나머지 막대의 높이는 그 막대와의 비율에 의해 정해진다. 
또, 막대의 너비도 고정되어있다. 그렇기 때문에 구간의 크기는 항상 정해져 있다. (위의 그림에선 10이다) 

마지막으로, 각각의 막대는 가장 왼쪽이 검정색 (밝기: 1), 오른쪽이 흰색 (밝기: 0)이고, 그 사이 막대는 왼쪽에서 오른쪽으로 갈 수록 일정한 비율에 따라서 밝기가 감소한다. 
예를 들어, 위의 그림에서 막대의 검은 정도는 1, 2/3, 1/3, 0이다.

히스토그램을 출력하는데 필요한 잉크의 양을 구하는 프로그램을 작성하시오. 각 막대를 그리는데 필요한 잉크의 양은 면적과 검은 정도에 비례한다.

입력
입력은 여러 개의 테스트 케이스로 이루어져 있다. 각 테스트 케이스의 첫째 줄에는 히스토그램의 값의 개수 n과 구간의 크기 w가 주어진다. 
다음 줄에는 자료의 값이 주어진다. 첫 막대의 구간은 0 ≤ v < w, 두 번째 막대의 구간은 w ≤ v < 2w이고, 나머지 막대의 구간도 이와 같이 정할 수 있다. 
어떤 막대에 포함되는 값의 개수가 0개이더라도 그 막대를 그리지 않으면 안 된다. (1 ≤ n ≤ 100, 10 ≤ w ≤ 50, 0 ≤ 값 ≤ 100)

값의 최댓값은 w보다 작지 않다. 따라서, 히스토그램은 한 개보다 많은 구간을 가지고 있다.

입력의 마지막 줄에는 0이 두 개 주어진다.

출력
각 테스트 케이스에 대해서 히스토그램을 그리는데 필요한 잉크의 양을 출력한다.

가장 높은 막대를 검정색으로 드는데 잉크가 1만큼 필요하다. 
또, 히스토그램에서 축과 글자를 그리는데 필요한 잉크의 양은 0.01이다. 
예를 들어, 위에서 주어진 히스토그을 그리는데 필요한 잉크의 양은 다음과 같다.


정답과의 오차가 10-5보다 작은 경우에 정답이다.
*/
/*
    count[Val / W] 에서 Val / W의 최댓값은?
    Val/W <= 100/10 = 10
    따라서 count 배열의 크기는 11로 잡는다.
*/
#include<iostream>
#include<algorithm>
#include<climits>
#include<cstring>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(1){
        int N, W, count[11], val, maxX = INT_MIN, maxY = INT_MIN;
        double ans = 0.01;
        memset(count, 0, sizeof(count));

        // input
        cin >> N >> W;

        // break condition
        if(!N && !W){
            break;
        }

        for(int i=0;i<N;i++){
            cin >> val;
            ++count[val / W];
            maxX = max(maxX, val / W);
        }

        // get max y-axis
        for(int i=0;i<=maxX;i++){
            maxY = max(maxY, count[i]);
        }

        // get ans
        for(int i=0;i<=maxX;i++){
            // 밝기 * 높이
            ans += ((maxX-i) / (double)(maxX)) * (count[i] / (double)maxY);
        }

        cout << ans << "\n";
    }

    return 0;
}