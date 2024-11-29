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

    // 병합을 시작하는 부분
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

    // 왼쪽 배열에 남아있는 값을 복사
    while (i <= mid) {
        sorted[k++] = list[i++]; // 값 복사 후 이동
        moveCount++; // 이동 횟수 증가
    }

    // 오른쪽 배열에 남아있는 값을 복사
    while (j <= right) {
        sorted[k++] = list[j++]; // 값 복사 후 이동
        moveCount++; // 이동 횟수 증가
    }

    // sorted 배열을 원래 배열로 복사
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

// 수정된 부분: 랜덤 값을 생성하는 함수에서 시드 초기화는 main에서 한 번만 설정
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 사이의 랜덤 값
    }
}

int main() {
    int array[SIZE];

    // 랜덤 시드를 한 번만 설정합니다.
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









/*
###합병 정렬 알고리즘
merge_sort(list, left, right):

if lesft < right
    mid = (left+right)/2;
    merge_sort(list, left, mid);
    merge_sort(list, mid+1, right);
    merge(list, left, mid, right);
    

###합병 알고리즘
merge(list, left, mid, last):

i<-left;
j<-mid+1;
k<-left;
sorted 배열을 생성;
while i<=mid and j<= right do
    if(list[i]<list[j])
        then
            sorted[k]<-list[i];
            k++;
            i++;
        else
            sorted[k]<-list[j];
            k++;
            j++;
 
 위의 합병 정렬 알고리즘과 합병 알고리즘을 학습한 뒤 다음 조건에 만족하는 코드를 작성한다.
 */

/*
### 주어진 조건
0-999 사이의 랜덤 데이터 100개로 아래 조건을 만족하며 합병정렬을 수행한다(재귀적 방법)
1. 정렬하는 과정을 출력한다.
- 이는 한번만 출력한다
- 분할과 결합의 모든 과정에서 10번에 한번씩 출력한다
- 배열 처음부터 10번째까지, 중앙 -1위치부터 중앙 +10 위치까지 출력한다.

2. 비교 횟수를 출력(20회 평균)
3. 이동 횟수를 출력(20회 평균)
- 비교 횟수와 이동 횟수의 20회 평균은 각 회 새로운 랜덤기반 데이터를 생성한다.
- 이동 횟수에서 이동은 값을 temp에 넣거나 temp로부터 값을 가져오는 모든 행위를 포함한다.
*/

/*
예상 출력 결과(랜덤의 값을 정렬하기 때문에 실제 출력 값과는 차이가 있을 수 있음)

Merge Sort Run // 실제와 다를 수 있음
95 622 632 999 918  55 977 385 419  63 | 301 610 590 422 922 652 989 911 461 119 993
55  63  95 130 297 385 419 492 622 632 | 301 610 590 422 922 652 989 911 461 119 993
55  62  63  95 130 297 312 354 363 385 | 301 610 590 422 922 652 989 911 461 119 993
55  62  63  95 130 297 312 354 363 385 | 301 610 590 422 922 652 989 911 461 119 993
55  62  63  95 130 297 312 354 363 385 | 301 610 590 422 922 652 989 911 461 119 993
 4  54  55  62  63  80  81  95  96 130 | 999 422 590 610 652 911 922 989 461 119 993
 4  54  55  62  63  80  81  95  96 130 | 999  65  73 119 422 461 590 610 652 704 911
 4  54  55  62  63  80  81  95  96 130 | 999  14  65  73  87 117 119 272 304 422 461
 4  54  55  62  63  80  81  95  96 130 | 999  14  65  73  87 117 119 272 304 422 461

 Result
 4 14 36 36 40 54 55 62 63 65 73 80 81 87 95 96 117 119 130 146 207 216 232 236 252 272 290 297 301 304 312 316 338 354 355 363 383 385 395 418 419 422 442 446 457 461 461 475 480 492 494 501 520 525 545 566 590 590 601 610 622 623 632 638 643 652 666 699 700 704 706 739 752 769 778 794 798 798 798 811 854 858 863 894 896 905 911 918 919 920 922 958 967 970 977 981 989 993 999

 Average Comparisons: 543.20 // 실제와 다를 수 있음
 Average Moves: 1344.00 // 실제와 다를 수 있음
*/

/*
###main 함수(main함수는 절대 수정 또는 변경하지 않는다.)

int main() {
    int array[SIZE];

    for(inti = 0 ; i < 20 ; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if(i==0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE-1);

            printf("Result\n");
            printArrat(array, SIZE);
            isFirst++;
        } else {
            doMergeSort(array, 0 ,SIZE-1);
        }

        totalComparisons += comparisonsCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    retuen 0;
}
*/

/*
###사용할 출력 코드

if(round % 10 == 0 && isFirst == 0) { //10번에 한 번만 출력
    for(int i = 0 ; 9 < 10 ; i++) //0~9값
        printf(%3d ", array[i]);
    printf("| ");
    for(int i = SIZE/2 - 1 ; i < SIZE/2 + 10 ; i++) //중앙 -1 ~ 중앙 +10
        printf("%3d ", arrat[i]);
    printf("\n\n");
}
*/