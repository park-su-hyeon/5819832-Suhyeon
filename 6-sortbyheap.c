#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 최대 힙을 구성하는 함수
void heapify(int arr[], int n, int i) {
    int largest = i; // 루트
    int left = 2 * i + 1; // 왼쪽 자식
    int right = 2 * i + 2; // 오른쪽 자식

    // 왼쪽 자식이 루트보다 큰 경우
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 오른쪽 자식이 현재 최대보다 큰 경우
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 최대가 루트가 아닌 경우
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        // 힙을 재귀적으로 정렬
        heapify(arr, n, largest);
    }
}

// 최대 힙을 생성하는 함수
void BuildMaxHeap(int arr[], int n) {
    // 마지막 비어있는 노드의 부모 노드부터 힙을 구성
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

// 힙 정렬 및 상태 출력을 위한 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    BuildMaxHeap(inputData, n);

    // 힙 상태 출력
    for (int i = 0; i < n; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    // 하나씩 힙에서 루트(최대값)를 제거하고 정렬
    for (int i = n - 1; i > 0; i--) {
        // 루트와 마지막 요소 교환
        swap(&inputData[0], &inputData[i]);
        // 힙 크기를 줄이고 재정렬
        heapify(inputData, i, 0);

        // 힙 재정렬 후 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
