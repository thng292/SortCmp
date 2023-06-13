#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void MergeSort_(int* arr, int start, int end, int* tmpArr)
{
    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    MergeSort_(arr, start, mid, tmpArr);
    MergeSort_(arr, mid + 1, end, tmpArr);

    int i = start;
    int j = mid + 1;
    int tail = 0;
    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) {
            tmpArr[tail++] = arr[i];
            i++;
        } else {
            tmpArr[tail++] = arr[j];
            j++;
        }
    }
    for (; i <= mid; i++) {
        tmpArr[tail++] = arr[i];
    }
    for (; j <= end; j++) {
        tmpArr[tail++] = arr[j];
    }
    memcpy(arr + start, tmpArr, (end - start + 1) * sizeof(int));
}

void MergeSort(int* arr, int length)
{
    int* tmpArr = malloc(length * sizeof(int));
    MergeSort_(arr, 0, length - 1, tmpArr);
    free(tmpArr);
}

int main(int args, char** argv)
{
    FILE* file = fopen(argv[1], "r");
    // FILE* file = fopen("tmp.txt", "r");
    int n;
    fscanf(file, "%d", &n);
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    clock_t begin = clock();
    MergeSort(arr, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%lf", time_spent);

    /*
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    */

    free(arr);
    return 0;
}
