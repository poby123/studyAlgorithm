#include <iostream>
#include <cstring>
using namespace std;
int *sorted;

void merge(int *arr, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
        {
            sorted[k] = arr[i];
            ++i;
        }
        else
        {
            sorted[k] = arr[j];
            ++j;
        }
        ++k;
    }
    while (i <= mid)
    {
        sorted[k] = arr[i];
        ++i;
        ++k;
    }
    while (j <= right)
    {
        sorted[k] = arr[j];
        ++j;
        ++k;
    }

    /* 
        !! 놓친 부분
        arr의 값은 merge가 끝날 때마다, 정렬된 배열의 값으로 업데이트 해줘야한다. 
        merge는 재귀적으로 호출되는 mergeSort 함수안에서 계속 호출되는데, 업데이트하지 않으면 정렬되지 않은 값으로 
        분할정복이 일어나기 때문에, 결과적으로 정렬이 되지 않기 때문이다.
    */
    for (int t = left; t <= right; t++)
    {
        arr[t] = sorted[t];
    }
}

void mergeSort(int *arr, int left, int right)
{
    // 기저사례 : left == right : 크기가 1인 경우 : 더 분할하거나 합칠 필요가 없다.
    if (left >= right)
        return;

    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main()
{
    int arr[] = {5, 8, 2, 9, 1, 10, 41, 56, 78, 99, 21};
    int n = sizeof(arr) / sizeof(int);
    sorted = new int[n];
    memset(sorted, 0, sizeof(sorted));

    mergeSort(arr, 0, n - 1);
    print(arr, n);
    print(sorted, n);

    delete[] sorted;
    sorted = nullptr;
    return 0;
}