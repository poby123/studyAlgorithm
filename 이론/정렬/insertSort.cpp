#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertSort(int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(&arr[j], &arr[j - 1]);
            }
            else
            {
                break;
            }
        }
    }
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

    insertSort(arr, n);
    print(arr, n);
    return 0;
}