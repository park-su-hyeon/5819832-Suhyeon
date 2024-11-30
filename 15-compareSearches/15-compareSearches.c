#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

// 글로벌 변수 선언
int compareCount = 0;  // 비교 횟수를 추적하는 전역 변수

// 함수 선언
void printArray(int* array);
void generateRandomArray(int* array);
int linearSearch(int* array, int target);
int quickSort(int* array, int low, int high);
int partition(int* array, int low, int high);
int binarySearch(int* array, int low, int high, int target);
double getAverageLinearSearchCompareCount(int* array);
int getQuickSortCompareCount(int* array);
double getAverageBinarySearchCompareCount(int* array);
void swap(int* a, int* b);

// 배열 출력 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    // 처음 20개 출력
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");

    // 마지막 20개 출력
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// 임의의 숫자 배열 생성 함수
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; 
    }
}

// 순차탐색 함수 (비교 횟수를 반환)
int linearSearch(int* array, int target) {
    int compareCount = 0;
    for (int i = 0; i < SIZE; i++) {
        compareCount++;  // 비교 횟수 증가
        if (array[i] == target) {
            return compareCount;  // 값을 찾으면 비교 횟수 반환
        }
    }
    return compareCount;  // 값을 찾지 못한 경우 비교 횟수 반환
}

// 퀵정렬을 위한 분할 함수 (비교 횟수 추적)
int partition(int* array, int low, int high) {
    int pivot = array[high];  
    int i = low - 1;
    for (int j = low; j < high; j++) {
        compareCount++;  // 비교 횟수 증가
        if (array[j] < pivot) {  
            i++;
            swap(&array[i], &array[j]);  // 작은 값은 앞쪽으로 이동
        }
    }
    swap(&array[i + 1], &array[high]);  // 올바른 위치로 이동
    return i + 1;  // 최종 인덱스 반환
}

// 퀵정렬 함수 (비교 횟수를 추적하고 반환)
int quickSort(int* array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);  // 분할 후 피벗 인덱스 얻기
        quickSort(array, low, pivot - 1);  // 왼쪽 부분 재귀적으로 정렬
        quickSort(array, pivot + 1, high);  // 오른쪽 부분 재귀적으로 정렬
    }
    return compareCount;  // 비교 횟수 반환
}

// 이진탐색 함수 (비교 횟수를 반환)
int binarySearch(int* array, int low, int high, int target) {
    int compareCount = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;  // 중간값 인덱스
        compareCount++;  // 비교 횟수 증가
        if (array[mid] == target) {
            return compareCount;  // 값을 찾으면 비교 횟수 반환
        }
        else if (array[mid] < target) {
            low = mid + 1;  // 값이 크다면 오른쪽 절반을 탐색
        }
        else {
            high = mid - 1;  // 값이 작다면 왼쪽 절반을 탐색
        }
    }
    return compareCount;  // 값을 찾지 못한 경우 비교 횟수 반환
}

// 평균 순차탐색 비교 횟수 계산
double getAverageLinearSearchCompareCount(int* array) {
    int totalCompareCount = 0;

    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; 
        totalCompareCount += linearSearch(array, target);  // 순차탐색 수행
    }

    // 평균 계산
    return totalCompareCount / 100.0;  // 100번 수행한 평균 비교 횟수
}

// 퀵정렬 비교 횟수 계산
int getQuickSortCompareCount(int* array) {
    int low = 0;
    int high = SIZE - 1;
    compareCount = 0;  
    quickSort(array, low, high);  // 퀵정렬 수행
    return compareCount;  // 비교 횟수 반환
}

// 평균 이진탐색 비교 횟수 계산
double getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; 
        totalCompareCount += binarySearch(array, 0, SIZE - 1, target);  // 이진탐색 수행
    }
    return totalCompareCount / 100.0;  // 100번 수행한 평균 비교 횟수
}

// 두 수를 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// main 함수
int main(int argc, char* argv[]) {
    srand(time(NULL));  
    int array[SIZE];

    generateRandomArray(array);

    // 평균 순차탐색 비교 횟수 출력
    printf("Average Linear Search Compare Count: %.2f\n", getAverageLinearSearchCompareCount(array));

    // 퀵정렬 수행
    getQuickSortCompareCount(array); 

    // 전역 변수 compareCount 출력
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // 평균 이진탐색 비교 횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n", getAverageBinarySearchCompareCount(array));

    printArray(array);

    return 0;
}
