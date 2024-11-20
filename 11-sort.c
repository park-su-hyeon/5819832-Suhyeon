#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )


void generateRandomData(int list[]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 난수 발생 범위 0~999
    }

}
// 선택 정렬
void doSelectionSort(int list[]) {
    int temp, i, j, least;
    for (i = 0; i < SIZE - 1; i++) {
        least = i;
        for (j = i + 1; j < SIZE; j++) {
            if (list[j] < list[least]) {
                least = j;
            }
        }
        SWAP(list[i], list[least], temp);

        // 10부터 시작, 20씩 증가
        if (i + 1 >= 10 && (i + 1) % 20 == 10) {  
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", list[k]);
            }
            printf("\n\n");  
        }


        if (i == 89) {
            printf("Step 99: ");
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", list[k]);
            }
            printf("\n\n");  
        }
    }
}


// 삽입 정렬
void doInsertionSort(int list[]) {
    int compare_count, total_compare = 0;
    // 20번 평균 비교 횟수를 출력
    for (int trial = 0; trial < 20; trial++) {

        generateRandomData(list);

        int i, j, key;
        compare_count = 0;
        for (i = 1; i < SIZE; i++) {
            key = list[i];
            j = i - 1;
            while (j >= 0 && list[j] > key) {
                list[j + 1] = list[j];  
                j--;
                compare_count++;
            }
            list[j + 1] = key;
        }
        total_compare += compare_count;
    }


    printf("Insertion Sort Compare Average: %d\n", total_compare / 20);


    printf("Insertion Sort Result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");  

    printf("\n");  
}

// 버블 정렬
void doBubbleSort(int list[]) {
    int move_count, total_move = 0;
    // 20번 평균 비교 횟수를 출력
    for (int trial = 0; trial < 20; trial++) {

        generateRandomData(list);

        int i, j, temp;
        move_count = 0;
        for (i = SIZE - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (list[j] > list[j + 1]) {
                    SWAP(list[j], list[j + 1], temp);
                    move_count += 3;  // swap마다 3번의 값 이동
                }
            }
        }
        total_move += move_count;
    }


    printf("Bubble Sort Move Average: %d\n", total_move / 20);


    printf("Bubble Sort Result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");  
}

// 메인 함수
int main() {
    int randomData[SIZE];
    generateRandomData(randomData);

    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
