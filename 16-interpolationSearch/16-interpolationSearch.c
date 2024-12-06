#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000       // 배열 크기
#define MAX_VALUE 10000 // 배열에 삽입되는 랜덤 값의 최대값

int compareCount = 0;   // 비교 횟수를 저장하는 전역 변수

// 랜덤 배열 생성 함수: 배열에 0부터 MAX_VALUE 사이의 랜덤 값을 채운다.
void generateRandomArray(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE);
    }
}

// 두 값을 교환하는 함수: 배열 내 두 요소의 위치를 변경한다.
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 퀵 정렬 파티션 함수: 피벗을 기준으로 작은 값은 왼쪽, 큰 값은 오른쪽으로 분리한다.
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // 피벗은 배열의 마지막 요소로 설정
    int i = (low - 1);      // 작은 값의 인덱스 초기화

    for (int j = low; j <= high - 1; j++) {
        compareCount++;     // 비교 횟수 증가
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);  // 작은 값을 왼쪽 영역으로 이동
        }
    }
    swap(&arr[i + 1], &arr[high]);  // 피벗을 올바른 위치로 이동
    return (i + 1);  // 피벗의 위치 반환
}

// 퀵 정렬 함수: 재귀적으로 배열을 정렬
void QuickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);  // 파티션을 수행하고 피벗 위치 반환
        QuickSort(array, low, pi - 1);  // 피벗 왼쪽 정렬
        QuickSort(array, pi + 1, high);  // 피벗 오른쪽 정렬
    }
}

// 퀵 정렬을 수행하고 비교 횟수를 초기화하는 함수
void getQuickSortCompareCount(int array[]) {
    compareCount = 0;  // 비교 횟수 초기화
    QuickSort(array, 0, SIZE - 1);  // 퀵 정렬 수행
}

// 이진 탐색 함수: 배열에서 목표 값을 찾고 비교 횟수를 반환
int binarySearch(int array[], int target) {
    int left = 0, right = SIZE - 1, comparisons = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;  // 중간 인덱스 계산
        comparisons++;  // 비교 횟수 증가
        if (array[mid] == target) return comparisons;  // 값 찾음
        if (array[mid] < target) left = mid + 1;  // 오른쪽 탐색
        else right = mid - 1;  // 왼쪽 탐색
    }
    return comparisons;  // 값을 찾지 못한 경우 비교 횟수 반환
}

// 이진 탐색 평균 비교 횟수 계산 함수: 여러 랜덤 타겟 값을 탐색
double getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // 랜덤 타겟 생성
        totalComparisons += binarySearch(array, target);  // 비교 횟수 누적
    }
    return (double)totalComparisons / SIZE;  // 평균 비교 횟수 반환
}


int InterpolationSearch(int array[], int target) {
    int low, high, j, comparisons = 0;

    low = 0;
    high = SIZE - 1;
    while ((array[high] >= target) && (target > array[low])) {
        j = ((float)(target - array[low]) / (array[high] - array[low])
            * (high - low)) + low;  // 예상 위치 계산

        comparisons++;  // 비교 횟수 증가
        if (target == array[j]) return comparisons;  // 값 찾음
        else if (target > array[j]) low = j + 1;  // 오른쪽 탐색
        else high = j - 1;  // 왼쪽 탐색
        comparisons++;
    }

    return comparisons;  // 값을 찾지 못한 경우 비교 횟수 반환
}


double getAverageInterpolationSearchComparecount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // 랜덤 타겟 생성
        totalComparisons += InterpolationSearch(array, target);  // 비교 횟수 누적
    }
    return (double)totalComparisons / SIZE;  // 평균 비교 횟수 반환
}

// 배열의 일부 요소를 출력하는 함수: 정렬 상태 확인
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)  // 배열의 첫 20개 요소 출력
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)  // 배열의 마지막 20개 요소 출력
        printf("%4d ", array[i]);
    printf("\n\n");
}

// 메인 함수: 배열 생성, 정렬, 탐색, 결과 출력
int main(int argc, char* argv[]) {
    srand(time(NULL));  // 랜덤 시드 초기화
    int array[SIZE];
    generateRandomArray(array);  // 랜덤 배열 생성

    QuickSort(array, 0, SIZE - 1);  // 퀵 정렬 수행
    printArray(array);  // 정렬 결과 출력

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));  

    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));  

    return 0;
}
