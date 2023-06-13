#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void InsertionSort(int* arr, int length)
{
    for (int i = 0; i < length; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
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
    InsertionSort(arr, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%lf", time_spent);

    free(arr);
    return 0;
}
