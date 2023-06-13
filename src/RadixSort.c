#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int ArrayMax(int* arr, int length)
{
    int max = *arr;
    for (int i = 1; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void RadixSort(int* arr, int length, int base)
{
    int** bucket = malloc(base * sizeof(int*));
    for (int i = 0; i < base; i++) {
        bucket[i] = malloc(length * sizeof(int));
    }

    int max = ArrayMax(arr, length);
    // printf("max: %d\n", max);
    int modd = 1;
    while (max) {
        max /= base;
        modd *= base;
        for (int i = 0; i < base; i++) {
            bucket[i][0] = 1;
        }
        for (int i = 0; i < length; i++) {
            int tmp = arr[i] % modd;
            tmp /= (modd / base);
            // printf("tmp: %d\n", tmp);
            bucket[tmp][bucket[tmp][0]++] = arr[i];
        }
    }

    int tail = 0;
    for (int i = 0; i < base; i++) {
        for (int j = 1; j < bucket[i][0]; j++) {
            arr[tail++] = bucket[i][j];
        }
    }

    for (int i = 0; i < base; i++) {
        free(bucket[i]);
    }
    free(bucket);
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
    RadixSort(arr, n, 10);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%lf", time_spent);

    // printf("\n");
    // for (int i = 0; i < n; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    free(arr);
    return 0;
}
