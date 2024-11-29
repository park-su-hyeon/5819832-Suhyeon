#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

#define SIZE 100
#define RUNS 20

int comparisonCount = 0;
int moveCount = 0;
int sorted[SIZE];
int totalComparisons = 0;
int totalMoves = 0;
int isFirst = 0;

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

void printPartialArray(int array[], int size) {
    if (rounds % 10 == 0 && isFirst == 0) { //10번에 한번만 출력
        for (int i = 0; i < 10; i++) //0 ~ 9값
            printf("%3d ", array[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) //중앙-1 ~ 중앙+10
            printf("%3d ", array[i]);
        printf("\n\n");
    }

void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    
    while (i <= mid && j <= right) {
        comparisonCount++; // 비교 횟수 증가
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++]; // 값 복사 후 이동
            moveCount++; // 이동 횟수 증가
        }
        else {
            sorted[k++] = list[j++]; // 값 복사 후 이동
            moveCount++; // 이동 횟수 증가
        }
    }

    
    while (i <= mid) {
        sorted[k++] = list[i++]; // 값 복사 후 이동
        moveCount++; // 이동 횟수 증가
    }


    while (j <= right) {
        sorted[k++] = list[j++]; // 값 복사 후 이동
        moveCount++; // 이동 횟수 증가
    }

    
    for (int l = left; l <= right; l++) {
        list[l] = sorted[l]; // 값을 리스트로 복사
        moveCount++; // 이동 횟수 증가
    }
}


void doMergeSort(int list[], int left, int right) {
    static int round = 0;  // for tracking rounds
    if (left < right) {
        int mid = (left + right) / 2;
        doMergeSort(list, left, mid);
        doMergeSort(list, mid + 1, right);
        merge(list, left, mid, right);

        round++;

        // 10번에 한번씩 배열 출력
        if (round % 10 == 0 && isFirst == 0) {
            printPartialArray(list, SIZE);
        }
    }
}

void generateRandomNumbers(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 사이의 랜덤 값
    }
}

int main() {
    int array[SIZE];

    srand(time(NULL));  // 프로그램 시작 시 한 번만 시드를 설정

    // 20회 동안 랜덤 배열을 생성하고 정렬하며 비교횟수 및 이동횟수를 계산
    for (int i = 0; i < 20; i++) {
        generateRandomNumbers(array); // 랜덤 배열 생성
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doMergeSort(array, 0, SIZE - 1);
        }

        // 각 회차에서의 비교횟수와 이동횟수를 누적
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // 20번의 평균 계산 후 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}

