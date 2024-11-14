#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100
#define NUM_TESTS 20

// 배열의 값을 출력하는 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 랜덤한 배열 생성 함수
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 쉘 정렬 수행 및 비교/이동 횟수 계산
void doShellSort(int array[], int gap, int* comparisonCount, int* moveCount) {
    int temp, i, j;

    // 쉘 정렬 알고리즘
    for (int gapSize = ARRAY_SIZE / gap; gapSize > 0; gapSize /= gap) {
        for (i = gapSize; i < ARRAY_SIZE; i++) {
            temp = array[i];
            j = i;

            while (j >= gapSize && array[j - gapSize] > temp) {
                (*comparisonCount)++;
                array[j] = array[j - gapSize];
                (*moveCount)++;
                j -= gapSize;
            }

            if (j >= gapSize) {
                (*comparisonCount)++;
            }

            array[j] = temp;
            (*moveCount)++;
        }

        // 정렬 과정 출력
        printf("Sorting with gap = %d:\n", gapSize);
        printArray(array, 20);
    }printArray(array, ARRAY_SIZE);
}

// 삽입 정렬 (보너스)
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int i, j, temp;

    for (i = 1; i < ARRAY_SIZE; i++) {
        temp = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > temp) {
            (*comparisonCount)++;
            array[j + 1] = array[j];
            (*moveCount)++;
            j--;
        }

        if (j >= 0) {
            (*comparisonCount)++;
        }

        array[j + 1] = temp;
        (*moveCount)++;
    }
}

// 평균 계산 함수
void calculateAverage(int(*comparisonCountArray)[NUM_TESTS], int(*moveCountArray)[NUM_TESTS]) {
    int totalComparison = 0, totalMove = 0;
    for (int i = 0; i < NUM_TESTS; i++) {
        totalComparison += comparisonCountArray[0][i];
        totalMove += moveCountArray[0][i];
    }
    printf("Average Comparisons: %d\n", totalComparison / NUM_TESTS);
    printf("Average Moves: %d\n", totalMove / NUM_TESTS);
}

int main() {
    srand(time(NULL));  // 랜덤 시드 설정

    int comparisonCount, moveCount;
    int comparisonCountArray[3][NUM_TESTS];
    int moveCountArray[3][NUM_TESTS];

    for (int i = 0; i < NUM_TESTS; i++) {
        int array[ARRAY_SIZE];
        generateRandomNumbers(array); // 랜덤 배열 생성

        // 쉘 정렬 (n/2)
        comparisonCount = moveCount = 0;
        printf("Shell Sort (n/2):");
        doShellSort(array, 2, &comparisonCount, &moveCount);
        comparisonCountArray[0][i] = comparisonCount;
        moveCountArray[0][i] = moveCount;
        printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);


    }

    // 평균 계산
    printf("Average Results:\n");
    calculateAverage(comparisonCountArray, moveCountArray);

    return 0;
}
