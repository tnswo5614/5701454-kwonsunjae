#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define MAX_VALUE 999

// 두 정수를 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 배열에 랜덤 데이터를 생성하는 함수
void generateRandomData(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1); // MAX_VALUE 범위의 랜덤 숫자 생성
    }
}

// 배열 내용을 출력하는 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // 배열 원소 출력
    }
    printf("\n\n");
}

// 선택 정렬을 수행하는 함수
void doSelectionSort(int randomData[]) {
    int comparisons = 0, swaps = 0; // 비교 횟수와 교환 횟수 초기화
    int tempData[SIZE];
    for (int i = 0; i < SIZE; i++) {
        tempData[i] = randomData[i]; // 원본 데이터를 복사
    }

    printf("Selection Sort:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        int min_idx = i; // 현재 최소값 인덱스
        for (int j = i + 1; j < SIZE; j++) {
            comparisons++; // 비교 횟수 증가
            if (tempData[j] < tempData[min_idx]) {
                min_idx = j; // 더 작은 값의 인덱스 저장
            }
        }
        if (min_idx != i) {
            swap(&tempData[i], &tempData[min_idx]); // 값 교환
            swaps++; // 교환 횟수 증가
        }
        if ((i + 1) % 20 == 10 || i == SIZE - 2) { // 특정 단계에서 배열 출력
            printf("Step %d: ", i + 1);
            printArray(tempData, SIZE);
        }
    }
}

// 삽입 정렬을 수행하는 함수
void doInsertionSort(int randomData[]) {
    int totalComparisons = 0; // 총 비교 횟수 초기화
    int insert_sortedData[SIZE];
    srand(time(NULL)); // 랜덤 시드 초기화

    // 비교 횟수 평균 계산을 위해 20회 수행
    for (int k = 0; k < 20; k++) {
        int tempData[SIZE];
        generateRandomData(tempData); // 새로운 랜덤 데이터 생성
        int comparisons = 0;
        for (int i = 1; i < SIZE; i++) {
            int key = tempData[i];
            int j = i - 1;
            while (j >= 0 && tempData[j] > key) {
                tempData[j + 1] = tempData[j];
                j--;
                comparisons++; // 비교 횟수 증가
            }
            tempData[j + 1] = key;
            comparisons++; // 삽입 시 비교 횟수 증가
        }
        totalComparisons += comparisons;
    }

    // 원본 데이터를 복사하여 삽입 정렬
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
        insert_sortedData[j + 1] = key; // 키 값을 올바른 위치에 삽입
    }

    printf("Insertion Sort Compare Average: %d\n", totalComparisons / 20); // 평균 비교 횟수 출력
    printf("Insertion Sort Result:\n");
    printArray(insert_sortedData, SIZE); // 정렬 결과 출력
}

// 버블 정렬을 수행하는 함수
void doBubbleSort(int randomData[]) {
    int totalSwaps = 0; // 총 교환 횟수 초기화
    int bubble_sortedData[SIZE];
    srand(time(NULL)); // 랜덤 시드 초기화

    // 교환 횟수 평균 계산을 위해 20회 수행
    for (int k = 0; k < 20; k++) {
        int tempData[SIZE];
        generateRandomData(tempData); // 새로운 랜덤 데이터 생성
        int swaps = 0;
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempData[j] > tempData[j + 1]) {
                    swap(&tempData[j], &tempData[j + 1]); // 값 교환
                    swaps += 3; // 교환 동작 횟수 증가
                }
            }
        }
        totalSwaps += swaps; // 교환 횟수 누적
    }

    // 원본 데이터를 복사하여 버블 정렬
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

    printf("Bubble Sort Swap Average: %d\n", totalSwaps / 20); // 평균 교환 횟수 출력
    printf("Bubble Sort Result:\n");
    printArray(bubble_sortedData, SIZE); // 정렬 결과 출력
}

// 메인 함수
int main() {
    int randomData[SIZE];
    generateRandomData(randomData); // 랜덤 데이터 생성
    
    doSelectionSort(randomData); // 선택 정렬 수행
    doInsertionSort(randomData); // 삽입 정렬 수행
    doBubbleSort(randomData); // 버블 정렬 수행

    return 0;
}
