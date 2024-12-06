#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000       // �迭 ũ��
#define MAX_VALUE 999   // �迭 �� ���� ���� �ִ밪

int compareCount = 0;    // �� Ƚ���� �����ϴ� ����

// ���� �迭 ���� �Լ�
// �迭�� 0���� MAX_VALUE ������ ���� ���� SIZE��ŭ ä��ϴ�.
void generateRandomArray(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1);
    }
}

// �� ���� ��ȯ�ϴ� �Լ�
// �迭 ����� ��ġ�� ��ȯ�մϴ�.
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �� ������ ���� �Լ�
// �ǹ��� �������� ���� ���� ����, ū ���� ���������� ��ġ�մϴ�.
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // �ǹ��� �迭�� ������ ���
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        compareCount++; // �� Ƚ�� ����
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// �� ���� �Լ�
// ���� ���� ����� ����Ͽ� �迭�� �����մϴ�.
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high); // ���� ���� ã��
        quickSort(array, low, pi - 1);       // ���� �κ� �迭 ����
        quickSort(array, pi + 1, high);      // ������ �κ� �迭 ����
    }
}

// �� ���� ���� �� �� Ƚ�� ���
void getQuickSortCompareCount(int array[]) {
    compareCount = 0;
    quickSort(array, 0, SIZE - 1);
}

// ���� Ž�� �Լ�
// ���ĵ� �迭���� Ÿ�� ���� ã�� �� Ƚ���� ��ȯ�մϴ�.
int binarySearch(int array[], int target) {
    int left = 0, right = SIZE - 1, comparisons = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++; // �� Ƚ�� ����
        if (array[mid] == target) return comparisons;
        if (array[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return comparisons;
}

// ���� Ž���� ��� �� Ƚ�� ���
double getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int target = rand() % (MAX_VALUE + 1);
        totalComparisons += binarySearch(array, target);
    }
    return (double)totalComparisons / SIZE;
}

// ���� Ž�� �Լ�
// �迭���� Ÿ�� ���� ã�� �� Ƚ���� ��ȯ�մϴ�.
int linearSearch(int array[], int target) {
    int comparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        comparisons++; // �� Ƚ�� ����
        if (array[i] == target) return comparisons;
    }
    return comparisons;
}

// ���� Ž���� ��� �� Ƚ�� ���
double getAverageLinearSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int key = rand() % (MAX_VALUE + 1); // ������ Ű ����
        int target = array[key];           // Ÿ�� �� ����
        totalComparisons += linearSearch(array, target);
    }
    return (double)totalComparisons / SIZE;
}

// �迭 ��� �Լ�
// ���ĵ� �迭�� ó���� �� 20���� ��Ҹ� ����մϴ�.
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]); // �迭 ó�� 20�� ���
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]); // �迭 ������ 20�� ���
    printf("\n");
}

// ���� �Լ�
// ���α׷��� ����������, �Լ� ȣ�� �� ��� ���
int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� �ʱ�ȭ
    int array[SIZE];   // �迭 ����

    generateRandomArray(array); // ���� �迭 ����

    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array)); // ���� Ž�� ��� �� Ƚ�� ���

    getQuickSortCompareCount(array); // �� ���� �� �� Ƚ�� ���
    printf("Quick Sort Compare Count: %d\n", compareCount);

    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array)); // ���� Ž�� ��� �� Ƚ�� ���

    printArray(array); // �迭 ���

    return 0;
}