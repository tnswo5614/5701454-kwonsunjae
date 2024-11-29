#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 100 
#define MAX_VALUE 999 


int comparisonCount, moveCount, isFirst = 0, totalComparisons = 0, totalMoves = 0, rounds = 0;

// 랜덤 배열 생성 함수
void generateRandomArray(int randomData[]) {
    srand(time(NULL)); // 현재 시간을 기반으로 랜덤 시드 설정
    Sleep(1); // 대기
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1); // 0부터 MAX_VALUE까지의 랜덤 값 생성
    }
}

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // 배열의 각 원소 출력
    }
}

// 병합 정렬에 사용할 임시 배열
int sorted[SIZE];

// 두 부분 배열을 병합하는 함수
void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    // 두 부분 배열을 비교하여 병합
    while (i <= mid && j <= right) {
        comparisonCount++; // 비교 횟수 증가
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++]; // 작은 값을 임시 배열에 넣음
        }
        else {
            sorted[k++] = list[j++]; // 큰 값을 임시 배열에 넣음
        }
        moveCount++; // 이동 횟수 증가
    }

    // 왼쪽 배열에 남은 원소 처리
    while (i <= mid) {
        sorted[k++] = list[i++];
        moveCount++; // 이동 횟수 증가
    }

    // 오른쪽 배열에 남은 원소 처리
    while (j <= right) {
        sorted[k++] = list[j++];
        moveCount++; // 이동 횟수 증가
    }

    // 병합된 배열을 원래 리스트에 복사
    for (int l = left; l <= right; l++) {
        list[l] = sorted[l];
        moveCount++; // 이동 횟수 증가
    }

    rounds++; // 한 라운드 종료

    // 10라운드마다 배열 상태 출력
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++)
            printf("%3d ", list[i]); // 배열의 앞부분 출력
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)
            printf("%3d ", list[i]); // 배열의 중간 부분 출력
        printf("\n\n");
    }
}

// 재귀적 방법
void doMergeSort(int list[], int left, int right) {
    int mid;

    if (left < right) {
        mid = (left + right) / 2; // 중간 인덱스 계산
        doMergeSort(list, left, mid); // 왼쪽 절반 정렬
        doMergeSort(list, mid + 1, right); // 오른쪽 절반 정렬
        merge(list, left, mid, right); // 두 부분 배열 합병
    }
}

// 반복문을 사용한 합병 정렬 함수(bonus)
void iterativeMergeSort(int list[], int n) {
    int curr_size;
    int left_start;

    // 병합 크기를 1부터 시작하여 2배씩 늘려가며 수행
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        // 각 부분 배열을 병합
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ?
                (left_start + 2 * curr_size - 1) : (n - 1);

            if (mid < n - 1)
                merge(list, left_start, mid, right_end); // 병합 함수 호출
        }
    }
}

int main() {
    int array[SIZE];

    // 20번 반복하면서 성능 측정
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); // 새로운 랜덤 배열 생성
        comparisonCount = 0; // 비교 횟수 초기화
        moveCount = 0; // 이동 횟수 초기화

        if (i == 0) {
            printf("Merge Sort Run\n");
            iterativeMergeSort(array, SIZE); // 반복문을 사용한 합병 정렬 실행

            printf("Result\n");
            printArray(array, SIZE); // 정렬된 배열 출력
            isFirst++; // 첫 번째 실행 후 isFirst 값을 1로 변경
        }
        else {
            iterativeMergeSort(array, SIZE); // 반복문을 사용한 병합 정렬 실행
        }

        totalComparisons += comparisonCount; // 전체 비교 횟수에 더하기
        totalMoves += moveCount; // 전체 이동 횟수에 더하기
    }

    // 20번의 평균 비교 횟수와 이동 횟수 출력
    printf("\n\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
