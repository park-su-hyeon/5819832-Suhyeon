#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100  // 배열의 크기 설정

// 전역 변수
int rounds = 0;  // 퀵소트가 몇 번의 재귀적 분할을 했는지 추적하는 변수
int comparisonCount = 0;  // 비교 횟수 추적
int moveCount = 0;  // 이동 횟수 추적
double totalComparisons = 0;  // 모든 실행에서의 비교 횟수 총합
double totalMoveCount = 0;  // 모든 실행에서의 이동 횟수 총합

// 랜덤 배열을 생성하는 함수
void generateRandomArray(int array[]) {
    // SIZE 크기만큼 0에서 999 사이의 랜덤 값으로 배열 초기화
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999 사이의 난수 생성
    }
}

// 배열을 출력하는 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);  // 배열의 각 원소 출력
    }
    printf("\n");  // 출력 후 줄 바꿈
}

// 파티션 함수: 배열을 피벗을 기준으로 두 구간으로 나누는 함수
int partition(int array[], int left, int right) {
    int pivot = array[right];  // 피벗은 배열의 맨 오른쪽 값
    int i = left - 1;  // 'i'는 피벗보다 작은 값들의 끝 인덱스를 나타냄

    // 'j'는 현재 값이 피벗과 비교할 인덱스
    for (int j = left; j < right; j++) {
        comparisonCount++;  // 비교 횟수 증가
        if (array[j] <= pivot) {  // 현재 값이 피벗보다 작거나 같으면
            i++;  // 작은 값들의 구간을 확장

            // 값 교환 과정
            int temp = array[i];
            moveCount++;  // temp에 값을 저장하는 것도 이동으로 간주

            array[i] = array[j];
            moveCount++;  // array[i]에 값을 넣을 때 이동 횟수 증가

            array[j] = temp;
            moveCount++;  // array[j]에 값을 넣을 때 이동 횟수 증가
        }
    }

    // 피벗을 자신의 위치로 이동
    int temp = array[i + 1];
    moveCount++;  // temp에 값을 저장하는 것도 이동으로 간주

    array[i + 1] = array[right];
    moveCount++;  // array[i+1]에 값을 넣을 때 이동 횟수 증가

    array[right] = temp;
    moveCount++;  // array[right]에 값을 넣을 때 이동 횟수 증가

    return i + 1;  // 피벗의 최종 위치를 반환
}

// 퀵소트 함수: 재귀적으로 배열을 정렬하는 함수
void doQuickSort(int array[], int left, int right) {
    if (left < right) {  // 배열이 두 개 이상의 요소를 가진 경우
        int pivotIndex = partition(array, left, right);  // 배열을 파티션하고 피벗의 인덱스 반환

        // rounds가 10의 배수일 때, 40~60번 인덱스의 배열 상태를 출력 (단 한 번만 출력)
        if (rounds % 10 == 0 && rounds != 0) {  // rounds가 10의 배수일 때
            for (int i = 40; i < 60; i++)  // 40~59번 인덱스의 원소 출력
                printf("%d ", array[i]);
            printf("\n\n");
        }

        rounds++;  // rounds를 증가시켜 몇 번째 재귀 호출인지 추적

        // 피벗을 기준으로 왼쪽과 오른쪽 구간을 재귀적으로 정렬
        doQuickSort(array, left, pivotIndex - 1);  // 피벗 왼쪽 부분 정렬
        doQuickSort(array, pivotIndex + 1, right);  // 피벗 오른쪽 부분 정렬
    }
}

// main 함수: 프로그램의 시작점
int main(int argc, char* argv[]) {
    srand(time(NULL));  // 랜덤 시드 설정
    int array[SIZE];  // 크기가 SIZE인 배열 선언

    // 첫 번째 실행에서만 "Quick Sort Run" 출력
    printf("Quick Sort Run\n");

    // 20번 반복하여 퀵소트를 수행
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);  // 새로운 랜덤 배열 생성
        comparisonCount = 0;  // 비교 횟수 초기화
        moveCount = 0;  // 이동 횟수 초기화

        // 퀵소트 실행
        doQuickSort(array, 0, SIZE - 1);

        totalComparisons += comparisonCount;  // 각 실행의 비교 횟수를 누적
        totalMoveCount += moveCount;  // 각 실행의 이동 횟수를 누적
    }

    // 모든 실행이 끝난 후에 "Result" 한 번만 출력
    printf("Result\n");
    printArray(array, SIZE);  // 최종 정렬된 배열 출력

    // 20번 실행의 평균 비교 횟수와 평균 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;  // 프로그램 종료
}
