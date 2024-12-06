#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000       // 배열 크기
#define MAX_VALUE 999   // 배열 내 랜덤 값의 최대값

int compareCount = 0;    // 비교 횟수를 저장하는 변수

// 랜덤 배열 생성 함수
// 배열에 0부터 MAX_VALUE 사이의 랜덤 값을 SIZE만큼 채웁니다.
void generateRandomArray(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1);
    }
}

// 두 값을 교환하는 함수
// 배열 요소의 위치를 교환합니다.
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 퀵 정렬의 분할 함수
// 피벗을 기준으로 작은 값은 왼쪽, 큰 값은 오른쪽으로 배치합니다.
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 피벗은 배열의 마지막 요소
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        compareCount++; // 비교 횟수 증가
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// 퀵 정렬 함수
// 분할 정복 기법을 사용하여 배열을 정렬합니다.
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high); // 분할 지점 찾기
        quickSort(array, low, pi - 1);       // 왼쪽 부분 배열 정렬
        quickSort(array, pi + 1, high);      // 오른쪽 부분 배열 정렬
    }
}

// 퀵 정렬 실행 및 비교 횟수 계산
void getQuickSortCompareCount(int array[]) {
    compareCount = 0;
    quickSort(array, 0, SIZE - 1);
}

// 이진 탐색 함수
// 정렬된 배열에서 타겟 값을 찾고 비교 횟수를 반환합니다.
int binarySearch(int array[], int target) {
    int left = 0, right = SIZE - 1, comparisons = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++; // 비교 횟수 증가
        if (array[mid] == target) return comparisons;
        if (array[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return comparisons;
}

// 이진 탐색의 평균 비교 횟수 계산
double getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int target = rand() % (MAX_VALUE + 1);
        totalComparisons += binarySearch(array, target);
    }
    return (double)totalComparisons / SIZE;
}

// 선형 탐색 함수
// 배열에서 타겟 값을 찾고 비교 횟수를 반환합니다.
int linearSearch(int array[], int target) {
    int comparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        comparisons++; // 비교 횟수 증가
        if (array[i] == target) return comparisons;
    }
    return comparisons;
}

// 선형 탐색의 평균 비교 횟수 계산
double getAverageLinearSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int key = rand() % (MAX_VALUE + 1); // 임의의 키 생성
        int target = array[key];           // 타겟 값 설정
        totalComparisons += linearSearch(array, target);
    }
    return (double)totalComparisons / SIZE;
}

// 배열 출력 함수
// 정렬된 배열의 처음과 끝 20개의 요소를 출력합니다.
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]); // 배열 처음 20개 출력
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]); // 배열 마지막 20개 출력
    printf("\n");
}

// 메인 함수
// 프로그램의 시작점으로, 함수 호출 및 결과 출력
int main(int argc, char* argv[]) {
    srand(time(NULL)); // 난수 초기화
    int array[SIZE];   // 배열 선언

    generateRandomArray(array); // 랜덤 배열 생성

    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array)); // 선형 탐색 평균 비교 횟수 출력

    getQuickSortCompareCount(array); // 퀵 정렬 및 비교 횟수 계산
    printf("Quick Sort Compare Count: %d\n", compareCount);

    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array)); // 이진 탐색 평균 비교 횟수 출력

    printArray(array); // 배열 출력

    return 0;
}