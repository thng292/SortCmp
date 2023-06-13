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

void SelectionSort(int* arr, int start, int end)
{
    for (int i = start; i < end; i++) {
        int min = i;
        for (int j = i + 1; j < end; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        Swap(&arr[i], &arr[min]);
    }
}

void Merge(int* arr, int start, int mid, int end, int* tmpArr)
{
    int i = start;
    int j = mid;
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

int min(int a, int b) { return a > b ? b : a; }

void TimSort(int* arr, int length)
{
    int runSize = 64;
    int currPos = 0;
    int* tmpArr = malloc(length * sizeof(int));
    while (currPos + runSize <= length) {
        SelectionSort(arr, currPos, currPos + runSize);
        currPos += runSize;
    }
    SelectionSort(arr, currPos, length);

    while (runSize <= length) {
        for (int i = 0; i + runSize < length; i += runSize * 2) {
            Merge(arr, i, i + runSize, min(i + runSize * 2, length), tmpArr);
        }
        runSize *= 2;
    }
    free(tmpArr);
}

int main(int args, char** argv)
{
    FILE* file = fopen(argv[1], "r");
    int n;
    fscanf(file, "%d", &n);
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    clock_t begin = clock();
    TimSort(arr, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%lf", time_spent);
    free(arr);
    return 0;
}
