#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

// QuickSort 함수
void QuickSort(int* array, int low, int high) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (array[j] < pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;

        int pi = i + 1;

        QuickSort(array, low, pi - 1);
        QuickSort(array, pi + 1, high);
    }
}

// 배열에 랜덤 값 생성
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000; // 0부터 9999 사이의 랜덤 숫자
    }
}

// 배열 출력
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// Binary Search 함수 (비교 횟수 포함)
int binarySearch(int* array, int low, int high, int target, int* comparisons) {
    while (low <= high) {
        (*comparisons)++;
        int mid = low + (high - low) / 2;

        if (array[mid] == target) {
            (*comparisons)++;
            return mid; // 타겟을 찾음
            
        }
        else if (array[mid] < target) {
            low = mid + 1;
            
        }
        else {
            high = mid - 1;
        }
    }
    return -1; // 타겟을 찾지 못함
}

// 평균 비교 횟수 구하기 (Binary Search)
double getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 1000; i++) { // 1000번 반복
        int target = array[rand() % SIZE]; // 배열에서 랜덤하게 타겟 선택
        int comparisons = 0;
        binarySearch(array, 0, SIZE - 1, target, &comparisons); // 이진 탐색 수행
        totalComparisons += comparisons;
    }
    return (double)totalComparisons / 1000; // 평균 비교 횟수 반환
}

// Interpolation Search 함수 (비교 횟수 포함)
int interpolationSearch(int* array, int low, int high, int target, int* comparisons) {
    while (low <= high && target >= array[low] && target <= array[high]) {
        (*comparisons)++;
        if (low == high) {
            if (array[low] == target) return low;
            return -1;
        }

        // 타겟 위치를 추정하여 탐색
        int pos = low + ((double)(high - low) / (array[high] - array[low])) * (target - array[low]);

        if (array[pos] == target) {
            (*comparisons)++;
            return pos;
            
        }
        else if (array[pos] < target) {
            low = pos + 1;
            
        }
        else {
            high = pos - 1;
        }
    }
    return -1; // 타겟을 찾지 못함
}

// 평균 비교 횟수 구하기 (Interpolation Search)
double getAverageInterpolationSearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 1000; i++) { // 1000번 반복
        int target = array[rand() % SIZE]; // 배열에서 랜덤하게 타겟 선택
        int comparisons = 0;
        interpolationSearch(array, 0, SIZE - 1, target, &comparisons); // 보간 탐색 수행
        totalComparisons += comparisons;
    }
    return (double)totalComparisons / 1000; // 평균 비교 횟수 반환
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    int array[SIZE];
    generateRandomArray(array); // 배열에 랜덤 숫자 생성
    QuickSort(array, 0, SIZE - 1); // 배열을 QuickSort로 정렬
    printArray(array); // 정렬된 배열의 처음 20개와 마지막 20개 출력

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array)); // Binary Search 평균 비교 횟수 출력

    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array)); // Interpolation Search 평균 비교 횟수 출력

    return 0;
}
