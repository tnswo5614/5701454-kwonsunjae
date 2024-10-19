#include <stdio.h>
#include <stdlib.h>

// �� ������ ���� ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �ִ� ���� �Ӽ��� �����ϱ� ���� �������ϴ� �Լ�
void resortHeap(int inputData[], int n, int i) {
    int largest = i; // ���� �θ� ���
    int left = 2 * i + 1; // ���� �ڽ� ���
    int right = 2 * i + 2; // ������ �ڽ� ���

    // ���� �ڽ��� �θ𺸴� ũ�ٸ�
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // ������ �ڽ��� ������� ���� ū ��庸�� ũ�ٸ�
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // ���� ū ���� �θ� ��尡 �ƴ϶�� ��ȯ �� ��������� ȣ��
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// �迭�� �ִ� ������ ����� �Լ�
void BuildMaxHeap(int inputData[], int n) {
    // �迭�� �߰����� �����ؼ� �������� ���� ������
    for (int i = n / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, n, i);
    }
}

// �� ������ �����ϰ� �� �ܰ��� �� ���¸� ����ϴ� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
    // ���� �� �� ���� ���
    for (int i = 1; i <= n; i++) {
        BuildMaxHeap(inputData, i);

        // ���� �� ���� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

    // ���� ���� ����
    for (int i = n - 1; i > 0; i--) {
        // ù ��° ���(�ִ밪)�� ������ ��Ҹ� ��ȯ
        swap(&inputData[0], &inputData[i]);
        // ��ȯ �� ���� ������
        resortHeap(inputData, i, 0);

        // ���ĵ� �� ���� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    // ������ ������
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);  // �� ���� ����

    // ���� ��� ���
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
