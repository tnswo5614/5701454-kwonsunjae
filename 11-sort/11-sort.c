#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define MAX_VALUE 999

// �� ������ ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �迭�� ���� �����͸� �����ϴ� �Լ�
void generateRandomData(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1); // MAX_VALUE ������ ���� ���� ����
    }
}

// �迭 ������ ����ϴ� �Լ�
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // �迭 ���� ���
    }
    printf("\n\n");
}

// ���� ������ �����ϴ� �Լ�
void doSelectionSort(int randomData[]) {
    int comparisons = 0, swaps = 0; // �� Ƚ���� ��ȯ Ƚ�� �ʱ�ȭ
    int tempData[SIZE];
    for (int i = 0; i < SIZE; i++) {
        tempData[i] = randomData[i]; // ���� �����͸� ����
    }

    printf("Selection Sort:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        int min_idx = i; // ���� �ּҰ� �ε���
        for (int j = i + 1; j < SIZE; j++) {
            comparisons++; // �� Ƚ�� ����
            if (tempData[j] < tempData[min_idx]) {
                min_idx = j; // �� ���� ���� �ε��� ����
            }
        }
        if (min_idx != i) {
            swap(&tempData[i], &tempData[min_idx]); // �� ��ȯ
            swaps++; // ��ȯ Ƚ�� ����
        }
        if ((i + 1) % 20 == 10 || i == SIZE - 2) { // Ư�� �ܰ迡�� �迭 ���
            printf("Step %d: ", i + 1);
            printArray(tempData, SIZE);
        }
    }
}

// ���� ������ �����ϴ� �Լ�
void doInsertionSort(int randomData[]) {
    int totalComparisons = 0; // �� �� Ƚ�� �ʱ�ȭ
    int insert_sortedData[SIZE];
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ

    // �� Ƚ�� ��� ����� ���� 20ȸ ����
    for (int k = 0; k < 20; k++) {
        int tempData[SIZE];
        generateRandomData(tempData); // ���ο� ���� ������ ����
        int comparisons = 0;
        for (int i = 1; i < SIZE; i++) {
            int key = tempData[i];
            int j = i - 1;
            while (j >= 0 && tempData[j] > key) {
                tempData[j + 1] = tempData[j];
                j--;
                comparisons++; // �� Ƚ�� ����
            }
            tempData[j + 1] = key;
            comparisons++; // ���� �� �� Ƚ�� ����
        }
        totalComparisons += comparisons;
    }

    // ���� �����͸� �����Ͽ� ���� ����
    for (int i = 0; i < SIZE; i++) {
        insert_sortedData[i] = randomData[i];
    }
    for (int i = 1; i < SIZE; i++) {
        int key = insert_sortedData[i];
        int j = i - 1;
        while (j >= 0 && insert_sortedData[j] > key) {
            insert_sortedData[j + 1] = insert_sortedData[j];
            j--;
        }
        insert_sortedData[j + 1] = key; // Ű ���� �ùٸ� ��ġ�� ����
    }

    printf("Insertion Sort Compare Average: %d\n", totalComparisons / 20); // ��� �� Ƚ�� ���
    printf("Insertion Sort Result:\n");
    printArray(insert_sortedData, SIZE); // ���� ��� ���
}

// ���� ������ �����ϴ� �Լ�
void doBubbleSort(int randomData[]) {
    int totalSwaps = 0; // �� ��ȯ Ƚ�� �ʱ�ȭ
    int bubble_sortedData[SIZE];
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ

    // ��ȯ Ƚ�� ��� ����� ���� 20ȸ ����
    for (int k = 0; k < 20; k++) {
        int tempData[SIZE];
        generateRandomData(tempData); // ���ο� ���� ������ ����
        int swaps = 0;
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempData[j] > tempData[j + 1]) {
                    swap(&tempData[j], &tempData[j + 1]); // �� ��ȯ
                    swaps += 3; // ��ȯ ���� Ƚ�� ����
                }
            }
        }
        totalSwaps += swaps; // ��ȯ Ƚ�� ����
    }

    // ���� �����͸� �����Ͽ� ���� ����
    for (int i = 0; i < SIZE; i++) {
        bubble_sortedData[i] = randomData[i];
    }
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (bubble_sortedData[j] > bubble_sortedData[j + 1]) {
                swap(&bubble_sortedData[j], &bubble_sortedData[j + 1]);
            }
        }
    }

    printf("Bubble Sort Swap Average: %d\n", totalSwaps / 20); // ��� ��ȯ Ƚ�� ���
    printf("Bubble Sort Result:\n");
    printArray(bubble_sortedData, SIZE); // ���� ��� ���
}

// ���� �Լ�
int main() {
    int randomData[SIZE];
    generateRandomData(randomData); // ���� ������ ����
    
    doSelectionSort(randomData); // ���� ���� ����
    doInsertionSort(randomData); // ���� ���� ����
    doBubbleSort(randomData); // ���� ���� ����

    return 0;
}
