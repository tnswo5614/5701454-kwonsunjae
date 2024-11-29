#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100          // 배열 크기 정의
#define MAX_VALUE 999     // 배열 요소의 최대 값 정의
#define STACK_SIZE 100    // 스택 크기 정의 (재귀 대신 스택을 사용하여 반복문 구현)

int comparisonCount = 0;      // 비교 횟수 카운트
int moveCount = 0;           // 이동 횟수 카운트
double totalComparisons = 0; // 전체 비교 횟수의 합
double totalMoveCount = 0;  // 전체 이동 횟수의 합
int isFirst = 0;             // 첫 번째 실행 여부를 나타내는 플래그
int rounds = 0;              // 실행된 라운드 수

// 두 변수의 값을 서로 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    moveCount += 3;  // swap 시 3번의 이동이 발생하므로 이동 횟수 3 증가
}

// 배열을 분할하는 함수 (퀵 정렬의 분할 단계)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];      // 피벗을 배열의 마지막 원소로 설정
    int i = (low - 1);          // i는 low-1로 초기화

    // 배열을 순회하면서 피벗보다 작은 값들은 앞쪽으로, 큰 값들은 뒤쪽으로 이동
    for (int j = low; j <= high - 1; j++) {
        comparisonCount++;  // 비교 횟수 증가
        if (arr[j] < pivot) {
            i++;            // 피벗보다 작은 값이 발견되면 i를 증가시키고
            swap(&arr[i], &arr[j]); // 해당 값과 i번째 값을 교환
        }
    }
    swap(&arr[i + 1], &arr[high]);  // 피벗을 올바른 위치에 배치
    return (i + 1);  // 피벗의 인덱스를 반환
}

// 반복적인 퀵 정렬을 구현하는 함수
void doQuickSort(int arr[], int low, int high) {
    int stack[STACK_SIZE];    // 스택 배열
    int top = -1;             // 스택의 상단을 나타내는 변수

    stack[++top] = low;       // 스택에 low 값을 넣음
    stack[++top] = high;      // 스택에 high 값을 넣음

    // 스택이 비지 않을 때까지 반복
    while (top >= 0) {
        high = stack[top--];   // 스택에서 high 값 꺼내기
        low = stack[top--];    // 스택에서 low 값 꺼내기

        int pi = partition(arr, low, high);  // 현재 구간을 분할하고 피벗의 위치 찾기

        // 10번째 라운드마다 중간 결과를 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", arr[i]);  // 배열의 일부를 출력 (디버깅용)
            }
            printf("\n\n");
        }
        rounds++;  // 라운드 카운트 증가

        // 피벗의 왼쪽 구간에 대해 스택에 low와 pi-1을 추가
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        // 피벗의 오른쪽 구간에 대해 스택에 pi+1과 high를 추가
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

// 랜덤 배열을 생성하는 함수
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % (MAX_VALUE + 1);  // 0에서 MAX_VALUE까지의 난수 생성
    }
}

// 배열을 출력하는 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);  // 배열의 각 요소를 출력
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL));  // 랜덤 시드 설정 (현재 시간을 기준으로)
    int array[SIZE];    // 정렬할 배열 선언

    // 20번 반복하여 퀵 정렬을 수행
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);  // 새로운 랜덤 배열 생성
        comparisonCount = 0;          // 비교 횟수 초기화
        moveCount = 0;               // 이동 횟수 초기화

        // 첫 번째 실행 시 퀵 정렬 수행 및 결과 출력
        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;  // 첫 번째 실행 완료
        }
        else {
            doQuickSort(array, 0, SIZE - 1);  // 나머지 실행에 대해서는 결과 출력하지 않음
        }

        // 각 실행 후 비교 횟수 및 이동 횟수 합산
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // 평균 비교 횟수와 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
