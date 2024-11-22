#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

#define ARRAY_SIZE 100

// 랜덤 숫자를 생성하는 함수
void generateRandomNumbers(int array[]) {
    Sleep(1000); // 1초 대기
    srand(time(NULL)); // 현재 시간을 시드로 랜덤 숫자 초기화
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 사이의 랜덤 값
    }
}

// 쉘 정렬의 특정 gap에 대한 정렬 수행
void doSellSort(int array[], int size, int gap, int* totalComparisonCount, int* totalMoveCount) {
    int temp, i, j;
    int comparisonCount = 0; // 비교 횟수
    int moveCount = 0; // 이동 횟수

    // gap을 기준으로 삽입 정렬 수행
    printf("Sorting with gap = %d:\n", gap);
    for (i = gap; i < size; i++) {
        temp = array[i];
        j = i;

        // 삽입 정렬 (gap 간격을 둔 정렬)
        while (j >= gap && array[j - gap] > temp) {
            array[j] = array[j - gap]; // 이동
            j -= gap;
            comparisonCount++; // 비교 증가
            moveCount++; // 이동 증가
        }

        array[j] = temp; // 값을 삽입
        moveCount++; // 삽입 시 이동 증가
    }

    // gap별 비교 및 이동 횟수를 누적
    *totalComparisonCount += comparisonCount;
    *totalMoveCount += moveCount;

    // gap별 배열 상태 출력 (20개만 출력)
    for (int k = 0; k < size; k++) {
        if (k < 20) {
            printf("%d ", array[k]);
        }
        else {
            printf("...");
            break;
        }
    }
    printf("\n\n"); // gap 단계 출력 사이 줄띄움 추가
}

// 쉘 정렬 수행
void doShellSort(int array[], int divisor, int* totalComparisonCount, int* totalMoveCount) {
    int sortedArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sortedArray[i] = array[i]; // 원본 배열 복사
    }

    int gap = ARRAY_SIZE / divisor;

    // 초기 비교 및 이동 횟수 초기화
    *totalComparisonCount = 0;
    *totalMoveCount = 0;

    // gap이 1 이상일 때까지 정렬 반복
    while (gap >= 1) {
        doSellSort(sortedArray, ARRAY_SIZE, gap, totalComparisonCount, totalMoveCount);
        gap /= divisor; // gap을 divisor로 나누어 줄임
    }

    // 최종 정렬된 배열 출력
    printf("Sorted shellArray (gap = %d):\n", divisor);
    for (int k = 0; k < ARRAY_SIZE; k++) {
        printf("%d ", sortedArray[k]); // 100개 전부 출력
    }
    printf("\n\n");
}

// 삽입 정렬 수행
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int sortedArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sortedArray[i] = array[i]; // 원본 배열 복사
    }

    *comparisonCount = 0;
    *moveCount = 0;

    for (int i = 1; i < ARRAY_SIZE; i++) {
        int key = sortedArray[i];
        int j = i - 1;

        // 정렬 위치를 찾기 위해 이동
        while (j >= 0 && sortedArray[j] > key) {
            sortedArray[j + 1] = sortedArray[j];
            j--;
            (*comparisonCount)++;
            (*moveCount)++;
        }

        sortedArray[j + 1] = key;
        (*moveCount)++;
    }

    // 최종 정렬된 배열 출력
    printf("Sorted insertionArray:\n");
    for (int k = 0; k < ARRAY_SIZE; k++) {
        printf("%d ", sortedArray[k]); // 100개 전부 출력
    }
    printf("\n");
}

int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array);

    // Shell Sort (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Shell Sort (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
