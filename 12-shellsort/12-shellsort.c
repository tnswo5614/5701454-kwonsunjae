#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100 // �迭 ũ�⸦ ����
#define MAX_VALUE 999 // ���� �ִ밪 ����

// �迭�� ���� ���ڸ� �����ϴ� �Լ�
// ����: �迭�� 0���� MAX_VALUE ������ ���� ���ڸ� ä���ֱ�
void generateRandomNumbers(int randomData[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1);
    }
}

// �迭�� ��Ҹ� ����ϴ� �Լ�
// ����: �迭�� ��Ҹ� size��ŭ ���
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

unsigned int seed; // ���� �������� �õ� ��

// �� ���� �Լ�
// ����: �־��� �迭�� �� ���� �˰����� ����� �����ϰ�, �� �� �̵� Ƚ���� ���
void doShellSort(int arr[], int n, int* comparisonCount, int* moveCount) {
    int totalComparisons = 0, totalMoves = 0;
    int result[ARRAY_SIZE];
    srand(seed); // ������ �õ尪�� ������� ���� ����

    // ���� �۾��� ���� �迭 ����
    for (int i = 0; i < ARRAY_SIZE; i++) {
        result[i] = arr[i];
    }

    // ���� ����� �� ����
    for (int gap = ARRAY_SIZE / n; gap > 0; gap /= n) {
        for (int i = gap; i < ARRAY_SIZE; i++) {
            int temp = result[i];
            int j;
            for (j = i; j >= gap && result[j - gap] > temp; j -= gap) {
                result[j] = result[j - gap];
            }
            result[j] = temp;
        }
        // �߰� ��� ���
        printf("Sorting With Gap = %d: \n", gap);
        printArray(result, 20);
        printf("...\n\n");
    }

    // ���� ��� ���
    printf("Sorted shellArray (gap = %d)\n", n);
    printArray(result, ARRAY_SIZE);
    printf("\n\n");

    srand(time(NULL)); // ���� �õ� �ʱ�ȭ

    // ��� �� �� �̵� Ƚ���� ����ϱ� ���� �߰� �׽�Ʈ
    for (int k = 0; k < 20; k++) {
        int tempArr[ARRAY_SIZE];
        generateRandomNumbers(tempArr); // ���ο� ���� ������ ����
        int localComparisons = 0, localMoves = 0;

        for (int gap = ARRAY_SIZE / n; gap > 0; gap /= n) {
            for (int i = gap; i < ARRAY_SIZE; i++) {
                int temp = tempArr[i];
                localMoves++;
                int j;
                for (j = i; j >= gap && tempArr[j - gap] > temp; j -= gap) {
                    localComparisons++;
                    tempArr[j] = tempArr[j - gap];
                    localMoves++;
                }
                if (j >= gap) {
                    localComparisons++;
                }
                if (j != i) {
                    tempArr[j] = temp;
                    localMoves++;
                }
            }
        }
        totalComparisons += localComparisons;
        totalMoves += localMoves;
    }

    *comparisonCount = totalComparisons / 20; // ��� �� Ƚ��
    *moveCount = totalMoves / 20; // ��� �̵� Ƚ��
}

// ���� ���� �Լ�
// ����: �־��� �迭�� ���� ���� �˰����� ����� �����ϰ�, �� �� �̵� Ƚ���� ���
void doInsertionSort(int arr[], int* comparisonCount, int* moveCount) {
    int totalComparisons = 0, totalMoves = 0;
    int sortedArr[ARRAY_SIZE];

    // ���� �۾��� ���� �迭 ����
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sortedArr[i] = arr[i];
    }

    // ���� ���� �˰���
    for (int i = 1; i < ARRAY_SIZE; i++) {
        int temp = sortedArr[i];
        int j = i - 1;

        while (j >= 0 && sortedArr[j] > temp) {
            sortedArr[j + 1] = sortedArr[j];
            j--;
        }
        sortedArr[j + 1] = temp;
    }

    // ���� ��� ���
    printArray(sortedArr, ARRAY_SIZE);
    printf("\n\n");

    // ��� �� �� �̵� Ƚ���� ����ϱ� ���� �߰� �׽�Ʈ
    for (int k = 0; k < 20; k++) {
        int tempArr[ARRAY_SIZE];
        generateRandomNumbers(tempArr); // ���ο� ���� ������ ����
        int localComparisons = 0, localMoves = 0;

        for (int i = 1; i < ARRAY_SIZE; i++) {
            int temp = tempArr[i];
            localMoves++;
            int j = i - 1;

            while (j >= 0 && tempArr[j] > temp) {
                localComparisons++;
                tempArr[j + 1] = tempArr[j];
                localMoves++;
                j--;
            }
            if (j >= 0) {
                localComparisons++;
            }

            if (j + 1 != i) {
                tempArr[j + 1] = temp;
                localMoves++;
            }
        }
        totalComparisons += localComparisons;
        totalMoves += localMoves;
    }

    *comparisonCount = totalComparisons / 20; // ��� �� Ƚ��
    *moveCount = totalMoves / 20; // ��� �̵� Ƚ��
}

// ���� �Լ�
// ����: �� ���İ� ���� ������ ���� ��
int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array); // ���� ������ ����

    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount); // n/2 ���� �� ����
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount); // n/3 ���� �� ����
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount); // ���� ����
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
