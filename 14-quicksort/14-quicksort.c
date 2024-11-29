#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100          // �迭 ũ�� ����
#define MAX_VALUE 999     // �迭 ����� �ִ� �� ����
#define STACK_SIZE 100    // ���� ũ�� ���� (��� ��� ������ ����Ͽ� �ݺ��� ����)

int comparisonCount = 0;      // �� Ƚ�� ī��Ʈ
int moveCount = 0;           // �̵� Ƚ�� ī��Ʈ
double totalComparisons = 0; // ��ü �� Ƚ���� ��
double totalMoveCount = 0;  // ��ü �̵� Ƚ���� ��
int isFirst = 0;             // ù ��° ���� ���θ� ��Ÿ���� �÷���
int rounds = 0;              // ����� ���� ��

// �� ������ ���� ���� ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    moveCount += 3;  // swap �� 3���� �̵��� �߻��ϹǷ� �̵� Ƚ�� 3 ����
}

// �迭�� �����ϴ� �Լ� (�� ������ ���� �ܰ�)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];      // �ǹ��� �迭�� ������ ���ҷ� ����
    int i = (low - 1);          // i�� low-1�� �ʱ�ȭ

    // �迭�� ��ȸ�ϸ鼭 �ǹ����� ���� ������ ��������, ū ������ �������� �̵�
    for (int j = low; j <= high - 1; j++) {
        comparisonCount++;  // �� Ƚ�� ����
        if (arr[j] < pivot) {
            i++;            // �ǹ����� ���� ���� �߰ߵǸ� i�� ������Ű��
            swap(&arr[i], &arr[j]); // �ش� ���� i��° ���� ��ȯ
        }
    }
    swap(&arr[i + 1], &arr[high]);  // �ǹ��� �ùٸ� ��ġ�� ��ġ
    return (i + 1);  // �ǹ��� �ε����� ��ȯ
}

// �ݺ����� �� ������ �����ϴ� �Լ�
void doQuickSort(int arr[], int low, int high) {
    int stack[STACK_SIZE];    // ���� �迭
    int top = -1;             // ������ ����� ��Ÿ���� ����

    stack[++top] = low;       // ���ÿ� low ���� ����
    stack[++top] = high;      // ���ÿ� high ���� ����

    // ������ ���� ���� ������ �ݺ�
    while (top >= 0) {
        high = stack[top--];   // ���ÿ��� high �� ������
        low = stack[top--];    // ���ÿ��� low �� ������

        int pi = partition(arr, low, high);  // ���� ������ �����ϰ� �ǹ��� ��ġ ã��

        // 10��° ���帶�� �߰� ����� ���
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", arr[i]);  // �迭�� �Ϻθ� ��� (������)
            }
            printf("\n\n");
        }
        rounds++;  // ���� ī��Ʈ ����

        // �ǹ��� ���� ������ ���� ���ÿ� low�� pi-1�� �߰�
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        // �ǹ��� ������ ������ ���� ���ÿ� pi+1�� high�� �߰�
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

// ���� �迭�� �����ϴ� �Լ�
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % (MAX_VALUE + 1);  // 0���� MAX_VALUE������ ���� ����
    }
}

// �迭�� ����ϴ� �Լ�
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);  // �迭�� �� ��Ҹ� ���
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL));  // ���� �õ� ���� (���� �ð��� ��������)
    int array[SIZE];    // ������ �迭 ����

    // 20�� �ݺ��Ͽ� �� ������ ����
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);  // ���ο� ���� �迭 ����
        comparisonCount = 0;          // �� Ƚ�� �ʱ�ȭ
        moveCount = 0;               // �̵� Ƚ�� �ʱ�ȭ

        // ù ��° ���� �� �� ���� ���� �� ��� ���
        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;  // ù ��° ���� �Ϸ�
        }
        else {
            doQuickSort(array, 0, SIZE - 1);  // ������ ���࿡ ���ؼ��� ��� ������� ����
        }

        // �� ���� �� �� Ƚ�� �� �̵� Ƚ�� �ջ�
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // ��� �� Ƚ���� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
