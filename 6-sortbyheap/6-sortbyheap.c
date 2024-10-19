#include <stdio.h>
#include <stdlib.h>

// 두 원소의 값을 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 최대 힙의 속성을 유지하기 위해 재정렬하는 함수
void resortHeap(int inputData[], int n, int i) {
    int largest = i; // 현재 부모 노드
    int left = 2 * i + 1; // 왼쪽 자식 노드
    int right = 2 * i + 2; // 오른쪽 자식 노드

    // 왼쪽 자식이 부모보다 크다면
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // 오른쪽 자식이 현재까지 가장 큰 노드보다 크다면
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // 가장 큰 값이 부모 노드가 아니라면 교환 후 재귀적으로 호출
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// 배열을 최대 힙으로 만드는 함수
void BuildMaxHeap(int inputData[], int n) {
    // 배열의 중간부터 시작해서 역순으로 힙을 재정렬
    for (int i = n / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, n, i);
    }
}

// 힙 정렬을 수행하고 각 단계의 힙 상태를 출력하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    // 정렬 전 힙 상태 출력
    for (int i = 1; i <= n; i++) {
        BuildMaxHeap(inputData, i);

        // 현재 힙 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

    // 실제 정렬 과정
    for (int i = n - 1; i > 0; i--) {
        // 첫 번째 요소(최대값)와 마지막 요소를 교환
        swap(&inputData[0], &inputData[i]);
        // 교환 후 힙을 재정렬
        resortHeap(inputData, i, 0);

        // 정렬된 힙 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    // 정렬할 데이터
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);  // 힙 정렬 수행

    // 정렬 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
