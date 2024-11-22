#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100 // 배열 크기를 정의
#define MAX_VALUE 999 // 난수 최대값 정의

// 배열에 랜덤 숫자를 생성하는 함수
// 목적: 배열에 0부터 MAX_VALUE 사이의 랜덤 숫자를 채워넣기
void generateRandomNumbers(int randomData[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1);
    }
}

// 배열의 요소를 출력하는 함수
// 목적: 배열의 요소를 size만큼 출력
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

unsigned int seed; // 난수 생성기의 시드 값

// 셸 정렬 함수
// 목적: 주어진 배열을 셸 정렬 알고리즘을 사용해 정렬하고, 비교 및 이동 횟수를 계산
void doShellSort(int arr[], int n, int* comparisonCount, int* moveCount) {
    int totalComparisons = 0, totalMoves = 0;
    int result[ARRAY_SIZE];
    srand(seed); // 동일한 시드값을 기반으로 난수 생성

    // 정렬 작업을 위한 배열 복사
    for (int i = 0; i < ARRAY_SIZE; i++) {
        result[i] = arr[i];
    }

    // 갭에 기반한 셸 정렬
    for (int gap = ARRAY_SIZE / n; gap > 0; gap /= n) {
        for (int i = gap; i < ARRAY_SIZE; i++) {
            int temp = result[i];
            int j;
            for (j = i; j >= gap && result[j - gap] > temp; j -= gap) {
                result[j] = result[j - gap];
            }
            result[j] = temp;
        }
        // 중간 결과 출력
        printf("Sorting With Gap = %d: \n", gap);
        printArray(result, 20);
        printf("...\n\n");
    }

    // 정렬 결과 출력
    printf("Sorted shellArray (gap = %d)\n", n);
    printArray(result, ARRAY_SIZE);
    printf("\n\n");

    srand(time(NULL)); // 난수 시드 초기화

    // 평균 비교 및 이동 횟수를 계산하기 위한 추가 테스트
    for (int k = 0; k < 20; k++) {
        int tempArr[ARRAY_SIZE];
        generateRandomNumbers(tempArr); // 새로운 랜덤 데이터 생성
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

    *comparisonCount = totalComparisons / 20; // 평균 비교 횟수
    *moveCount = totalMoves / 20; // 평균 이동 횟수
}

// 삽입 정렬 함수
// 목적: 주어진 배열을 삽입 정렬 알고리즘을 사용해 정렬하고, 비교 및 이동 횟수를 계산
void doInsertionSort(int arr[], int* comparisonCount, int* moveCount) {
    int totalComparisons = 0, totalMoves = 0;
    int sortedArr[ARRAY_SIZE];

    // 정렬 작업을 위한 배열 복사
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sortedArr[i] = arr[i];
    }

    // 삽입 정렬 알고리즘
    for (int i = 1; i < ARRAY_SIZE; i++) {
        int temp = sortedArr[i];
        int j = i - 1;

        while (j >= 0 && sortedArr[j] > temp) {
            sortedArr[j + 1] = sortedArr[j];
            j--;
        }
        sortedArr[j + 1] = temp;
    }

    // 정렬 결과 출력
    printArray(sortedArr, ARRAY_SIZE);
    printf("\n\n");

    // 평균 비교 및 이동 횟수를 계산하기 위한 추가 테스트
    for (int k = 0; k < 20; k++) {
        int tempArr[ARRAY_SIZE];
        generateRandomNumbers(tempArr); // 새로운 랜덤 데이터 생성
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

    *comparisonCount = totalComparisons / 20; // 평균 비교 횟수
    *moveCount = totalMoves / 20; // 평균 이동 횟수
}

// 메인 함수
// 목적: 셸 정렬과 삽입 정렬의 성능 비교
int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array); // 랜덤 데이터 생성

    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount); // n/2 기준 셸 정렬
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount); // n/3 기준 셸 정렬
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount); // 삽입 정렬
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
