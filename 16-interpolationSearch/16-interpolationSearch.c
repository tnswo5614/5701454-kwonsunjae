#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000       // �迭 ũ��
#define MAX_VALUE 10000 // �迭�� ���ԵǴ� ���� ���� �ִ밪

int compareCount = 0;   // �� Ƚ���� �����ϴ� ���� ����

// ���� �迭 ���� �Լ�: �迭�� 0���� MAX_VALUE ������ ���� ���� ä���.
void generateRandomArray(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE);
    }
}

// �� ���� ��ȯ�ϴ� �Լ�: �迭 �� �� ����� ��ġ�� �����Ѵ�.
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �� ���� ��Ƽ�� �Լ�: �ǹ��� �������� ���� ���� ����, ū ���� ���������� �и��Ѵ�.
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // �ǹ��� �迭�� ������ ��ҷ� ����
    int i = (low - 1);      // ���� ���� �ε��� �ʱ�ȭ

    for (int j = low; j <= high - 1; j++) {
        compareCount++;     // �� Ƚ�� ����
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);  // ���� ���� ���� �������� �̵�
        }
    }
    swap(&arr[i + 1], &arr[high]);  // �ǹ��� �ùٸ� ��ġ�� �̵�
    return (i + 1);  // �ǹ��� ��ġ ��ȯ
}

// �� ���� �Լ�: ��������� �迭�� ����
void QuickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);  // ��Ƽ���� �����ϰ� �ǹ� ��ġ ��ȯ
        QuickSort(array, low, pi - 1);  // �ǹ� ���� ����
        QuickSort(array, pi + 1, high);  // �ǹ� ������ ����
    }
}

// �� ������ �����ϰ� �� Ƚ���� �ʱ�ȭ�ϴ� �Լ�
void getQuickSortCompareCount(int array[]) {
    compareCount = 0;  // �� Ƚ�� �ʱ�ȭ
    QuickSort(array, 0, SIZE - 1);  // �� ���� ����
}

// ���� Ž�� �Լ�: �迭���� ��ǥ ���� ã�� �� Ƚ���� ��ȯ
int binarySearch(int array[], int target) {
    int left = 0, right = SIZE - 1, comparisons = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;  // �߰� �ε��� ���
        comparisons++;  // �� Ƚ�� ����
        if (array[mid] == target) return comparisons;  // �� ã��
        if (array[mid] < target) left = mid + 1;  // ������ Ž��
        else right = mid - 1;  // ���� Ž��
    }
    return comparisons;  // ���� ã�� ���� ��� �� Ƚ�� ��ȯ
}

// ���� Ž�� ��� �� Ƚ�� ��� �Լ�: ���� ���� Ÿ�� ���� Ž��
double getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // ���� Ÿ�� ����
        totalComparisons += binarySearch(array, target);  // �� Ƚ�� ����
    }
    return (double)totalComparisons / SIZE;  // ��� �� Ƚ�� ��ȯ
}


int InterpolationSearch(int array[], int target) {
    int low, high, j, comparisons = 0;

    low = 0;
    high = SIZE - 1;
    while ((array[high] >= target) && (target > array[low])) {
        j = ((float)(target - array[low]) / (array[high] - array[low])
            * (high - low)) + low;  // ���� ��ġ ���

        comparisons++;  // �� Ƚ�� ����
        if (target == array[j]) return comparisons;  // �� ã��
        else if (target > array[j]) low = j + 1;  // ������ Ž��
        else high = j - 1;  // ���� Ž��
        comparisons++;
    }

    return comparisons;  // ���� ã�� ���� ��� �� Ƚ�� ��ȯ
}


double getAverageInterpolationSearchComparecount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // ���� Ÿ�� ����
        totalComparisons += InterpolationSearch(array, target);  // �� Ƚ�� ����
    }
    return (double)totalComparisons / SIZE;  // ��� �� Ƚ�� ��ȯ
}

// �迭�� �Ϻ� ��Ҹ� ����ϴ� �Լ�: ���� ���� Ȯ��
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)  // �迭�� ù 20�� ��� ���
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)  // �迭�� ������ 20�� ��� ���
        printf("%4d ", array[i]);
    printf("\n\n");
}

// ���� �Լ�: �迭 ����, ����, Ž��, ��� ���
int main(int argc, char* argv[]) {
    srand(time(NULL));  // ���� �õ� �ʱ�ȭ
    int array[SIZE];
    generateRandomArray(array);  // ���� �迭 ����

    QuickSort(array, 0, SIZE - 1);  // �� ���� ����
    printArray(array);  // ���� ��� ���

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));  

    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));  

    return 0;
}
